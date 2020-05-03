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
#include "Application.h"
#include "feed/Feeds.h"

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

    this->reading = false;
    this->lineSpacer = 4;
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
    this->choice = 1;
    this->articleChoice = 1;
    this->quit = 0;
}


/**
 * Create's feed window
 */
void Application::createFeedWindow()
{
    this->feedWindowWidth = (int) (COLS / 3);
    this->feedWindow = newwin(this->windowHeight, this->feedWindowWidth, 2, 0);
    keypad(this->feedWindow, TRUE);
}


/**
 * Create's article window
 */
void Application::createArticleWindow()
{
    this->articleWindowWidth = (int) (COLS / 3) * 2;
    this->articleWindow = newwin(this->windowHeight, this->articleWindowWidth, 2, this->feedWindowWidth);
    keypad(this->articleWindow, TRUE);
}


/**
 * Show's complete UI
 */
void Application::show()
{
    Feeds *feeds = Feeds::getInstance();
    mvprintw(0, 0, "Use vim keys to navigate through articles, Press enter to select a choice or press 'q' to quit.");
    refresh();

    this->printWindows();

    while (true)
    {
        this->c = wgetch(this->feedWindow);
        switch (this->c)
        {
            case KEY_UP:
            case KEY_K:
                this->articleChoice = this->decreaseChoice(this->articleChoice, FEEDS_MAX);
                break;

            case KEY_DOWN:
            case KEY_J:
                this->articleChoice = this->increaseChoice(this->articleChoice, FEEDS_MAX);
                break;

            case KEY_UPPER_K:
                wclear(this->articleWindow);
                this->articleChoice = 1;
                this->choice = this->decreaseChoice(this->choice, feeds->getCount());
                break;

            case KEY_UPPER_J:
                wclear(this->articleWindow);
                this->articleChoice = 1;
                this->choice = this->increaseChoice(this->choice, feeds->getCount());
                break;

            case KEY_O:
                this->openArticleLink();
                break;

            case ENTER:
                this->openArticle();
                break;

            case KEY_Q:
                if (this->reading)
                {
                    this->reading = false;
                    wclear(this->feedWindow);
                    wclear(this->articleWindow);
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
            this->printWindows();
        }

        if (this->quit != 0)
        {
            break;
        }
    }
}


/**
 * Print UI windows
 */
void Application::printWindows()
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
    int x = 2, y = 1, i;
    for (i = 0; i < feeds->getCount(); ++i)
    {
        char *line = feeds->getFeedLineTitle(i);
        if (this->choice == i + 1)
        {
            this->printLineHighlightedInWindow(this->feedWindow, y, x, line);
        }
        else
        {
            this->printLineInWindow(this->feedWindow, y, x, line);
        }

        wclrtoeol(this->feedWindow);
        ++y;
    }

    box(this->feedWindow, 0, 0);
    wrefresh(this->feedWindow);
}


/**
 * Print's articles in window
 */
void Application::printArticlesInWindow()
{
    Feeds *feeds = Feeds::getInstance();
    int x = 2, y = 1, i;
    int currentChoice = this->choice - 1;
    for (i = 0; i < FEEDS_MAX; i++)
    {
        if (this->articleChoice == i + 1)
        {
            this->printArticleHighlightedInWindow(this->articleWindow, y, x, feeds->getArticle(currentChoice, i));
        }
        else
        {
            this->printArticleInWindow(this->articleWindow, y, x, feeds->getArticle(currentChoice, i));
        }

        wclrtoeol(this->articleWindow);
        ++y;
    }

    box(this->articleWindow, 0, 0);
    wrefresh(this->articleWindow);
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

    std::string fullTitle(entry->title);
    std::string title = fullTitle.substr(0, titleWidth);
    if (fullTitle.length() > titleWidth)
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
    if (new_choice == count)
    {
        new_choice = 1;
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
    if (new_choice == 1)
    {
        new_choice = count;
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

    struct rss *feed = feeds->get(this->choice - 1);
    feed->unreadCount--;

    struct rssItem *entry = feeds->getArticle(this->choice - 1, this->articleChoice - 1);
    entry->read = 1;

    wclear(this->articleWindow);
    box(this->articleWindow, 0, 0);
    wrefresh(this->articleWindow);
    mvwprintw(this->articleWindow, 1, 2, "Feed:     %s", feed->title);
    mvwprintw(this->articleWindow, 2, 2, "Article:  %s", entry->title);
    mvwprintw(this->articleWindow, 3, 2, "Date:     %s", entry->date);
    mvwprintw(this->articleWindow, 4, 2, "--------");

    if (strlen(entry->description) > 0)
    {
        mvwprintw(this->articleWindow, 6, 2, "%s", entry->description);
    }

    wrefresh(this->articleWindow);

}


/**
 * Open current article link in browser
 */
void Application::openArticleLink()
{
    if (!this->reading)
    {
        return;
    }

    Feeds *feeds = Feeds::getInstance();
    struct rssItem *article = feeds->getArticle(this->choice - 1, this->articleChoice - 1);
    std::string openCmd("open ");
    openCmd += article->url;

    system(openCmd.c_str());
}
