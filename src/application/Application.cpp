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
    this->lineSpacer = 4;
    this->windowHeight = LINES - 4;
    this->windowInnerHeight = this->windowHeight - 2;
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
    this->feedWindow = newwin(this->windowHeight, this->feedWindowWidth, 2, 0);
    keypad(this->feedWindow, TRUE);

    this->feedPadOffsetTop = 0;
    this->feedPad = newpad(200, this->feedWindowWidth-4);
    keypad(this->feedPad, TRUE);
}


/**
 * Create's article window
 */
void Application::createArticleWindow()
{
    this->articleWindowWidth = (int) (COLS / 3) * 2;
    this->articleWindow = newwin(this->windowHeight, this->articleWindowWidth, 2, this->feedWindowWidth);
    keypad(this->articleWindow, TRUE);

    this->articlePadOffsetTop = 0;
    this->articlePadOffsetTopDetail = 0;
    this->articlePad = newpad(200, this->articleWindowWidth-4);
    keypad(this->articlePad, TRUE);
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
    this->printPads();

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
    this->printWindows();
    this->printPads();

    while (true)
    {
        this->c = wgetch(this->feedWindow);
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
                    this->articlePadOffsetTopDetail--;
                    this->printArticleDetailPad();
                }
                else
                {
                    this->articleChoice = this->decreaseChoice(this->articleChoice, articleCount);
                    this->articlePadOffsetTop = this->decreasePadOffset(this->articlePadOffsetTop, this->articleChoice, articleCount);
                }
                break;

            case KEY_DOWN:
            case KEY_J:
                if (this->reading)
                {
                    this->articlePadOffsetTopDetail++;
                    this->printArticleDetailPad();
                }
                else
                {
                    this->articleChoice = this->increaseChoice(this->articleChoice, articleCount);
                    this->articlePadOffsetTop = this->increasePadOffset(this->articlePadOffsetTop, this->articleChoice);
                }
                break;

            case KEY_UPPER_K:
                wclear(this->articlePad);
                this->articleChoice = 0;
                this->articlePadOffsetTop = 0;
                this->choice = this->decreaseChoice(this->choice, feedCount);
                this->feedPadOffsetTop = this->decreasePadOffset(this->feedPadOffsetTop, this->choice, feedCount);
                break;

            case KEY_UPPER_J:
                wclear(this->articlePad);
                this->articleChoice = 0;
                this->articlePadOffsetTop = 0;
                this->choice = this->increaseChoice(this->choice, feedCount);
                this->feedPadOffsetTop = this->increasePadOffset(this->feedPadOffsetTop, this->choice);
                break;

            case KEY_O:
                this->openArticleLink();
                break;

            case ENTER:
                this->articlePadOffsetTopDetail = 0;
                this->openArticle();
                break;

            case KEY_Q:
                if (this->reading)
                {
                    this->reading = false;
                    this->printWindows();
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

        if (!this->reading)
        {
            this->printPads();
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
    wclear(this->feedWindow);
    box(this->feedWindow, 0, 0);
    wrefresh(this->feedWindow);

    wclear(this->articlePad);
    wclear(this->articleWindow);
    box(this->articleWindow, 0, 0);
    wrefresh(this->articleWindow);
}


/**
 * Print's all pad's to the screen
 */
void Application::printPads()
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
    int x = 0, y = 0, i;
    for (i = 0; i < feeds->getCount(); ++i)
    {
        char *line = feeds->getFeedLineTitle(i);
        if (this->choice == i)
        {
            this->printLineHighlightedInWindow(this->feedPad, y, x, line);
        }
        else
        {
            this->printLineInWindow(this->feedPad, y, x, line);
        }
        ++y;
    }

    this->refreshFeedPad();
}


/**
 * Refresh's the feed pad
 */
void Application::refreshFeedPad()
{
    prefresh(this->feedPad, this->feedPadOffsetTop, 0, 3, 2, this->windowHeight, COLS);
}


/**
 * Print's articles in window
 */
void Application::printArticlesInWindow()
{
    Feeds *feeds = Feeds::getInstance();
    int x = 0, y = 0, i;
    int currentChoice = this->choice;
    for (i = 0; i < feeds->getFeed(currentChoice)->articleCount; i++)
    {
        if (this->articleChoice == i)
        {
            this->printArticleHighlightedInWindow(this->articlePad, y, x, feeds->getArticle(currentChoice, i));
        }
        else
        {
            this->printArticleInWindow(this->articlePad, y, x, feeds->getArticle(currentChoice, i));
        }
        ++y;
    }

    this->refreshArticlePad();
}


/**
 * Refresh's the article pad
 */
void Application::refreshArticlePad()
{
    prefresh(this->articlePad, this->articlePadOffsetTop, 0, 3, this->feedWindowWidth+2, this->windowHeight, COLS);
}


/**
 * Print standard line
 *
 * @param   window      - The window to print
 * @param   y           - Y coordinate
 * @param   x           - X coordinate
 * @param   line        - Line to print
 */
void Application::printLineInWindow(WINDOW *window, int y, int x, char *line)
{
    mvwprintw(window, y, x, "%s", line);
}


/**
 * Print highlighted line
 *
 * @param   window      - The window to print
 * @param   y           - Y coordinate
 * @param   x           - X coordinate
 * @param   line        - Line to print
 */
void Application::printLineHighlightedInWindow(WINDOW *window, int y, int x, char *line)
{
    wattron(window, A_REVERSE);
    this->printLineInWindow(window, y, x, line);
    wattroff(window, A_REVERSE);
}


/**
 * Print standard feed article
 *
 * @param   window      - The window to print
 * @param   y           - Y coordinate
 * @param   x           - X coordinate
 * @param   entry       - RSS item to print
 */
void Application::printArticleInWindow(WINDOW *window, int y, int x, struct rssItem *entry)
{
    int xPos = x;
    char *readIcon = (char*)"[*]";
    if (entry->read)
    {
        readIcon = (char*)"[ ]";
    }
    mvwprintw(window, y, xPos, "%s", readIcon);

    xPos += strlen(readIcon) + this->lineSpacer;
    mvwprintw(window, y, xPos, "%s", entry->date);

    xPos += strlen(entry->date) + this->lineSpacer;
    int titleWidth = this->articleWindowWidth - (this->lineSpacer * 3) - xPos;

    string fullTitle(entry->title);
    string title = fullTitle.substr(0, titleWidth);
    if ((int)fullTitle.length() > titleWidth)
    {
        title += "...";
    }
    mvwprintw(window, y, xPos, "%s", title.c_str());
}


/**
 * Print highlighted feed article
 *
 * @param   window      - The window to print
 * @param   y           - Y coordinate
 * @param   x           - X coordinate
 * @param   entry       - RSS item to print
 */
void Application::printArticleHighlightedInWindow(WINDOW *window, int y, int x, struct rssItem *entry)
{
    wattron(window, A_REVERSE);
    this->printArticleInWindow(window, y, x, entry);
    wattroff(window, A_REVERSE);
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
 * Increase pad offset
 *
 * @param   offset      - Current feed/article offset
 * @param   choice      - Current feed/article choice
 * @return  New calculated offset
 */
int Application::increasePadOffset(int offset, int choice)
{
    if (choice == 0)
    {
        offset = 0;
    }
    else if (choice >= this->windowInnerHeight)
    {
        offset++;
    }

    return offset;
}


/**
 * Increase pad offset
 *
 * @param   offset      - Current feed/article offset
 * @param   choice      - Current feed/article choice
 * @param   count       - Current feed/article count
 * @return  New calculated offset
 */
int Application::decreasePadOffset(int offset, int choice, int count)
{
    if (choice == count-1)
    {
        offset = count - this->windowInnerHeight;
    }
    else if (offset > 0)
    {
        offset--;
    }

    return offset;
}


/**
 * Print article detail pad with scrolled top offset
 */
void Application::printArticleDetailPad()
{
    prefresh(this->articlePad, this->articlePadOffsetTopDetail, 0, 3, this->feedWindowWidth+2, this->windowHeight, COLS);
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

    wclear(this->articleWindow);
    box(this->articleWindow, 0, 0);
    wrefresh(this->articleWindow);

    wclear(this->articlePad);
    mvwprintw(this->articlePad, 0, 0, "Feed:     %s", feed->title);
    mvwprintw(this->articlePad, 1, 0, "Article:  %s", entry->title);
    mvwprintw(this->articlePad, 2, 0, "Date:     %s", entry->date);
    mvwprintw(this->articlePad, 3, 0, "--------");

    if (strlen(entry->description) > 0)
    {
        mvwprintw(this->articlePad, 5, 0, "%s", entry->description);
    }

    this->printArticleDetailPad();
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
