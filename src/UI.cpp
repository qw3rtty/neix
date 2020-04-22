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
#include "UI.h"
#include "feed/Feeds.h"

using namespace crss;

/**
 * Constructor
 */
UI::UI()
{
    this->initChoices();

    initscr();
    clear();
    noecho();
    cbreak();

    this->lineSpacer = 4;
    this->windowHeight = LINES - 4;
    this->createFeedWindow();
    this->createArticleWindow();
}


/**
 * Destructor
 */
UI::~UI()
{
    clrtoeol();
    refresh();
    endwin();
}


/**
 * Initialize choices
 */
void UI::initChoices()
{
    this->choice = 1;
    this->articleChoice = 1;
    this->quit = 0;
}


/**
 * Create's feed window
 */
void UI::createFeedWindow()
{
    this->feedWindowWidth = (int) (COLS / 3);
    this->feedWindow = newwin(this->windowHeight, this->feedWindowWidth, 2, 0);
    keypad(this->feedWindow, TRUE);
}


/**
 * Create's article window
 */
void UI::createArticleWindow()
{
    this->articleWindowWidth = (int) (COLS / 3) * 2;
    this->articleWindow = newwin(this->windowHeight, this->articleWindowWidth, 2, this->feedWindowWidth);
    keypad(this->articleWindow, TRUE);
}


/**
 * Show's complete UI
 */
void UI::show()
{
    Feeds *feeds = Feeds::getInstance();
    mvprintw(0, 0, "Use vim keys to navigate through articles, Press enter to select a choice or press 'q' to quit.");
    refresh();

    this->printWindows();

    while (1)
    {
        c = wgetch(this->feedWindow);
        switch (c)
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
                this->articleChoice = 1;
                this->choice = this->decreaseChoice(this->choice, feeds->getCount());
                break;

            case KEY_UPPER_J:
                this->articleChoice = 1;
                this->choice = this->increaseChoice(this->choice, feeds->getCount());
                break;

            case ENTER:
                this->openArticle();
                break;

            case KEY_Q:
                this->quit = this->choice;
                break;

            default:
                mvprintw(LINES - 1, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }

        this->printWindows();
        if (this->quit != 0)
        {
            break;
        }
    }
}


/**
 * Print UI windows
 */
void UI::printWindows()
{
    this->printFeedsInWindow();
    this->printArticlesInWindow();
}


/**
 * Print's feeds in window
 */
void UI::printFeedsInWindow()
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
void UI::printArticlesInWindow()
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
void UI::printLineInWindow(WINDOW *window, int y, int x, char *line)
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
void UI::printLineHighlightedInWindow(WINDOW *window, int y, int x, char *line)
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
void UI::printArticleInWindow(WINDOW *window, int y, int x, struct rssItem *entry)
{
    int xPos = x;
    char *readIcon = (char*)"[*]";
    if (entry->read)
    {
        readIcon = (char*)"[ ]";
    }
    mvwprintw(window, y, xPos, "%s", readIcon);

    xPos += strlen(readIcon) + this->lineSpacer;
    mvwprintw(window, y, xPos, "%s", entry->date); // TODO: Format date

    xPos += strlen(entry->date) + this->lineSpacer;
    std::string fullTitle(entry->title);
    std::string title = fullTitle.substr(0, 60);
    if (fullTitle.length() > 60)
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
void UI::printArticleHighlightedInWindow(WINDOW *window, int y, int x, struct rssItem *entry)
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
int UI::increaseChoice(int new_choice, int count)
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
int UI::decreaseChoice(int new_choice, int count)
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
 * Open selected article in default browser
 */
void UI::openArticle()
{
    Feeds *feeds = Feeds::getInstance();

    struct rss *feed = feeds->get(this->choice - 1);
    feed->unreadCount--;

    struct rssItem *entry = feeds->getArticle(this->choice - 1, this->articleChoice - 1);
    entry->read = 1;


//    wclear(this->articleWindow);
//    box(this->articleWindow, 0, 0);
//    wrefresh(this->articleWindow);
//    mvwprintw(this->articleWindow, 2, 1, "%s", entry->description);
//    wrefresh(this->articleWindow);

    std::string call = "open ";
    std::string url = call + entry->url;

    system(url.c_str());
}
