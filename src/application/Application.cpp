/**
 * Terminal UI class.
 *
 * @package     neix
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
#include "helper/helper.h"
#include "helper/TextConverter.h"
#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "feed/Feeds.h"

using namespace std;
using namespace neix;

/**
 * Constructor
 */
Application::Application()
{
    this->initChoices();

    initscr();
	keypad(stdscr, TRUE);
    erase();
    noecho();
    cbreak();
    curs_set(0);

    this->openCommand = "";
    this->reading = false;
    this->windowHeight = LINES - 4;
    this->createFeedWindow();
    this->createArticleWindow();
    this->createReadWindow();
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
 * Create's read window
 */
void Application::createReadWindow()
{
    this->rw.setDimensions(this->windowHeight, this->articleWindowWidth);
    this->rw.setPosition(2, this->feedWindowWidth);

    this->rw.enableHighlight = false;
    this->rw.scrollAlways = true;
}


/**
 * Resize complete application
 */
void Application::resize()
{
    endwin();
    refresh();
    erase();

    this->printVersion();
    this->printControlHints();

    this->windowHeight = LINES - 4;
    this->createFeedWindow();
    this->createArticleWindow();
    this->createReadWindow();
    this->fillWindowsWithContent();
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
    mvprintw(1, 0, " neix %s ", VERSION);
    attroff(A_REVERSE);
}


/**
 * Print control hints
 */
void Application::printControlHints()
{
    attron(A_REVERSE);
    if (COLS >= 85)
        mvprintw(LINES - 2, 0, " q/<- : Close | ENTER/-> : Open | o : Open Browser | j/J/PGDN : Down | k/K/PGUP : Up ");
    else
        mvprintw(LINES - 2, 0, "q/←|↵/→|o|j/J/PGDN/↑|k/K/PGUP/↓");

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
        this->c = getch();
        int feedCount = feeds->getCount();
        int articleCount = feeds->getFeed(this->choice)->articleCount;
        switch (this->c)
        {
            case KEY_R:
            case KEY_RESIZE:
                this->resize();
                break;

            case KEY_UP:
            case KEY_K:
                if (this->reading)
                {
                    this->rw.scrollUp();
                    this->rw.update();
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
                    this->rw.scrollDown();
                    this->rw.update();
                }
                else
                {
                    this->aw.increaseHighlight();
                    this->aw.update();
                    this->aw.scrollDown();
                    this->articleChoice = this->increaseChoice(this->articleChoice, articleCount);
                }
                break;

            case KEY_PPAGE:
            case KEY_UPPER_K:
				if (this->reading)
				{
					break;	
				}

                this->articleChoice = 0;
                this->fw.decreaseHighlight();
                this->fw.scrollUp();
                this->fw.update();
                this->choice = this->decreaseChoice(this->choice, feedCount);

                this->aw.reset();
                this->aw.resetHighlight();
                this->printArticlesInWindow();
                this->aw.update();
                break;

            case KEY_NPAGE:
            case KEY_UPPER_J:
				if (this->reading)
				{
					break;	
				}

                this->articleChoice = 0;
                this->fw.increaseHighlight();
                this->fw.scrollDown();
                this->fw.update();
                this->choice = this->increaseChoice(this->choice, feedCount);

                this->aw.reset();
                this->aw.resetHighlight();
                this->printArticlesInWindow();
                this->aw.update();
                break;

            case KEY_O:
                this->openArticleLink();
                break;

            case KEY_RIGHT:
            case ENTER:
                this->aw.hide();
                this->openArticle();

                this->fw.reset();
                this->printFeedsInWindow();
                this->fw.update();
                break;

            case KEY_LEFT:
            case KEY_Q:
                if (this->reading)
                {
                    this->reading = false;
                    this->rw.reset();
                    this->rw.hide();

                    this->aw.resetContent();
                    this->printArticlesInWindow();
                    this->aw.show();
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
    if (!this->reading)
    {
        this->aw.show();
    }
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
    this->fw.resetContent();
    Feeds *feeds = Feeds::getInstance();
    for (int i = 0; i < feeds->getCount(); ++i)
    {
        char *line = feeds->getFeedLineTitle(i, this->feedWindowWidth-12);
        this->fw.pushContent(line);
    }
}


/**
 * Print's articles in window
 */
void Application::printArticlesInWindow()
{
    if (this->reading)
    {
        return; 
    }

    this->aw.resetContent();
    Feeds *feeds = Feeds::getInstance();
    struct rss* feed = feeds->getFeed(this->choice);
  
    if (feed->loading && feed->articleCount == 0) 
    {
        this->aw.pushContent(" Feeds loading ... ");
        return; 
    }
    else if (feed->loading && feed->articleCount > 0)
    {
        feed->loading = false;
    }
    
    if (feed->error)
    {
        this->aw.pushContent(" Could not parse feed! ");
        return; 
    }

    for (int i = 0; i < feed->articleCount; i++)
    {
        string line = this->printArticleInWindow(
            feeds->getArticle(this->choice, i));
        this->aw.pushContent(
            subStrWithEndingDots(line, this->articleWindowWidth-4));
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

    return subStrWithEndingDots(line, this->articleWindowWidth-4);
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
    int length = this->articleWindowWidth-4;
    this->reading = true;

    struct rss *feed = feeds->getFeed(this->choice);
    if (feed->unreadCount > 0)
    {
        feed->unreadCount--;
    }

    struct rssItem *entry = feeds->getArticle(this->choice, this->articleChoice);
    entry->read = 1;

    this->rw.reset();

    string line = "Feed:      ";
    line += feed->title;
    this->rw.pushContent(subStrWithEndingDots(line, length));

    line = "Article:   ";
    line += entry->title;
    this->rw.pushContent(subStrWithEndingDots(line, length));

    line = "Date:      ";
    line += entry->date;
    this->rw.pushContent(subStrWithEndingDots(line, length));
    this->rw.pushContent("--------");

    if (strlen(entry->description) > 0)
    {
        TextConverter tc(entry->description, this->renderCommand);
        this->rw.pushContent(tc.execCmd());
    }

    this->rw.show();
}


/**
 * Open current article link in browser
 */
void Application::openArticleLink()
{
	if (this->openCommand.empty())
	{
		return;	
	}

    Feeds *feeds = Feeds::getInstance();
    struct rssItem *article = feeds->getArticle(this->choice, this->articleChoice);
    article->read = 1;

    string openCmd = this->openCommand;
    openCmd += " ";
    openCmd += trim(article->url);

    system(openCmd.c_str());
}
