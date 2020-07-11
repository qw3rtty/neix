/**
 * Terminal UI class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <cstdlib>
#include <string>
#include <cstring>

#include "config.h"
#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "feed/Feeds.h"

using namespace std;
using namespace crss;

/**
 * Constructor
 */
Application::Application()
{
    this->initChoices();

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    this->reading = false;
    this->windowHeight = LINES - 4;
    this->createFeedWindow();
    this->createArticleWindow();
}


/**
 * Destructor
 */
Application::~Application()
{
    clrtoeol();
    refresh();
    endwin();
}


/**
 * Initialize choices
 */
void Application::initChoices()
{
    this->choice = 0;
    this->articleChoice = 0;
    this->quit = -1;
}


/**
 * Create's feed window
 */
void Application::createFeedWindow()
{
    this->feedWindowWidth = (int) (COLS / 3);

    this->fw.setDimensions(this->windowHeight, this->feedWindowWidth);
    this->fw.setPosition(2, 0);
}


/**
 * Create's article window
 */
void Application::createArticleWindow()
{
    this->articleWindowWidth = (int) (COLS / 3) * 2;

    this->aw.setDimensions(this->windowHeight, this->articleWindowWidth);
    this->aw.setPosition(2, this->feedWindowWidth);
}


/**
 * Resize complete application
 */
void Application::resize()
{
    endwin();
    refresh();
    clear();

    this->printVersion();
    this->printControlHints();

    this->createFeedWindow();
    this->createArticleWindow();
    this->printWindows();

    if (this->reading)
    {
        this->openArticle();
    }
}


/**
 * Print current version line
 */
void Application::printVersion()
{
    attron(A_REVERSE);
    mvprintw(1, 0, " crss %s ", VERSION);
    attroff(A_REVERSE);
}


/**
 * Print control hints
 */
void Application::printControlHints()
{
    attron(A_REVERSE);
    mvprintw(LINES - 2, 0, " q:Quit/Close | ENTER:Open | o:Open Browser | j:Down | k:Up | J:Next Feed | K:Prev Feed ");
    attroff(A_REVERSE);
}


/**
 * Show's complete UI
 */
void Application::show()
{
    Feeds *feeds = Feeds::getInstance();
    this->printVersion();
    this->printControlHints();

    refresh();
    this->fillWindowsWithContent();
    this->printWindows();

    while (true)
    {
        this->c = wgetch(this->fw.getWindow());
        int feedCount = feeds->getCount();
        int articleCount = feeds->getFeed(this->choice)->articleCount;
        switch (this->c)
        {
            case KEY_RESIZE:
                this->resize();
                break;

            case KEY_UP:
            case KEY_K:
                if (this->reading)
                {
                    this->aw.scrollUp();
                    this->aw.update();
                }
                else
                {
                    this->aw.decreaseHighlight();
                    this->aw.update();
                    this->aw.scrollUp();
                    this->articleChoice = this->decreaseChoice(this->articleChoice, articleCount);
                }
                break;

            case KEY_DOWN:
            case KEY_J:
                if (this->reading)
                {
                    this->aw.scrollDown();
                    this->aw.update();
                }
                else
                {
                    this->aw.increaseHighlight();
                    this->aw.update();
                    this->aw.scrollDown();
                    this->articleChoice = this->increaseChoice(this->articleChoice, articleCount);
                }
                break;

            case KEY_UPPER_K:
                this->articleChoice = 0;
                this->fw.decreaseHighlight();
                this->fw.update();
                this->choice = this->decreaseChoice(this->choice, feedCount);

                this->aw.clear();
                this->aw.resetHighlight();
                this->printArticlesInWindow();
                this->aw.update();
                break;

            case KEY_UPPER_J:
                this->articleChoice = 0;
                this->fw.increaseHighlight();
                this->fw.update();
                this->choice = this->increaseChoice(this->choice, feedCount);

                this->aw.clear();
                this->aw.resetHighlight();
                this->printArticlesInWindow();
                this->aw.update();
                break;

            case KEY_O:
                this->openArticleLink();
                break;

            case ENTER:
                this->aw.enableHighlight = false;
                this->aw.scrollAlways = true;
                this->openArticle();

                this->fw.clear();
                this->printFeedsInWindow();
                this->fw.update();
                break;

            case KEY_Q:
                if (this->reading)
                {
                    this->reading = false;
                    this->aw.enableHighlight = true;
                    this->aw.scrollAlways = false;
                    this->aw.clear();
                    this->printArticlesInWindow();
                    this->aw.update();

                    this->fw.clear();
                    this->printFeedsInWindow();
                    this->fw.update();
                }
                else
                {
                    this->quit = this->choice;
                }
                break;

            default:
                mvprintw(LINES - 1, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }

        if (this->quit != -1)
        {
            break;
        }
    }
}


/**
 * Print all main window's to the screen
 */
void Application::printWindows()
{
    this->fw.show();
    this->aw.show();
}


/**
 * Print's all pad's to the screen
 */
void Application::fillWindowsWithContent()
{
    this->printFeedsInWindow();
    this->printArticlesInWindow();
}


/**
 * Print's feeds in window
 */
void Application::printFeedsInWindow()
{
    Feeds *feeds = Feeds::getInstance();
    for (int i = 0; i < feeds->getCount(); ++i)
    {
        char *line = feeds->getFeedLineTitle(i);
        this->fw.pushContent(line);
    }
}


/**
 * Print's articles in window
 */
void Application::printArticlesInWindow()
{
    Feeds *feeds = Feeds::getInstance();
    int currentChoice = this->choice;
    for (int i = 0; i < feeds->getFeed(currentChoice)->articleCount; i++)
    {
        string line = this->printArticleInWindow(feeds->getArticle(currentChoice, i));
        this->aw.pushContent(line);
    }
}


/**
 * Print standard feed article
 *
 * @param   window      - The window to print
 * @param   y           - Y coordinate
 * @param   x           - X coordinate
 * @param   entry       - RSS item to print
 */
string Application::printArticleInWindow(struct rssItem *entry)
{
    string line;
    char *readIcon = (char*)"[*]";
    if (entry->read)
    {
        readIcon = (char*)"[ ]";
    }
    line = readIcon;

    line += "    ";
    line += entry->date;

    string title(entry->title);
    line += "    ";
    line += title;

    return line;
}



/**
 * Increase choice
 *
 * @param   new_choice      - The new choice index
 * @param   count           - Count of feeds/article
 * @return  New choice index
 */
int Application::increaseChoice(int new_choice, int count)
{
    if (new_choice == count-1)
    {
        new_choice = 0;
    }
    else
    {
        ++new_choice;
    }

    return new_choice;
}


/**
 * Decrease choice
 *
 * @param   new_choice      - The new choice index
 * @param   count           - Count of feeds/article
 * @return  New choice index
 */
int Application::decreaseChoice(int new_choice, int count)
{
    if (new_choice == 0)
    {
        new_choice = count-1;
    }
    else
    {
        --new_choice;
    }

    return new_choice;
}


/**
 * Open selected article in terminal view
 */
void Application::openArticle()
{
    Feeds *feeds = Feeds::getInstance();
    this->reading = true;

    struct rss *feed = feeds->getFeed(this->choice);
    if (feed->unreadCount > 0)
    {
        feed->unreadCount--;
    }

    struct rssItem *entry = feeds->getArticle(this->choice, this->articleChoice);
    entry->read = 1;

    this->aw.clear();

    string line = "Feed:      ";
    line += feed->title;
    this->aw.pushContent(line);

    line = "Article:   ";
    line += entry->title;
    this->aw.pushContent(line);

    line = "Date:      ";
    line += entry->date;
    this->aw.pushContent(line);
    this->aw.pushContent("--------");

    if (strlen(entry->description) > 0)
    {
        this->aw.pushContent(entry->description);
    }

    this->aw.update();
}


/**
 * Open current article link in browser
 */
void Application::openArticleLink()
{
    Feeds *feeds = Feeds::getInstance();
    struct rssItem *article = feeds->getArticle(this->choice, this->articleChoice);
    article->read = 1;

    string openCmd("open ");
    openCmd += article->url;

    system(openCmd.c_str());
}
