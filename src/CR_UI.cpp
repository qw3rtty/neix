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

#include "config.h"
#include "CR_UI.h"
#include "feed/CR_FeedLoader.h"

/**
 * Constructor
 */
CR_UI::CR_UI()
{
    this->choice = 1;
    this->articleChoice = 0;
    this->quit = 0;

    initscr();
    clear();
    noecho();
    cbreak();

    this->windowFeedsWidth = (int) (COLS / 3);
    this->windowFeedsHeight = LINES - 4;

    this->windowArticlesWidth = (int) (COLS / 3) * 2;
    this->windowArticlesHeight = LINES - 4;
}


/**
 * Destructor
 */
CR_UI::~CR_UI()
{
    clrtoeol();
    refresh();
    endwin();
}


/**
 * Show's complete UI
 */
void CR_UI::showUI()
{
    this->windowFeeds = newwin(this->windowFeedsHeight, this->windowFeedsWidth, 2, 0);
    this->windowArticles = newwin(this->windowArticlesHeight, this->windowArticlesWidth, 2, this->windowFeedsWidth);
    keypad(this->windowFeeds, TRUE);
    mvprintw(0, 0, "Use arrow/vim keys to go up and down, Press enter to select a choice, Press 'q' to quit.");
    refresh();

    this->printWindows();

    while (1)
    {
        c = wgetch(this->windowFeeds);
        switch (c)
        {
            case KEY_UP:
            case KEY_K:
                this->articleChoice = 0;
                this->choice = this->decreaseChoice(this->choice);
                break;

            case KEY_DOWN:
            case KEY_J:
                this->articleChoice = 0;
                this->choice = this->increaseChoice(this->choice);
                break;

            case KEY_UPPER_K:
                this->articleChoice = this->decreaseChoice(this->articleChoice);
                break;

            case KEY_UPPER_J:
                this->articleChoice = this->increaseChoice(this->articleChoice);
                break;

            case ENTER:
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
void CR_UI::printWindows()
{
    int x, y, i;

    x = 2;
    y = 1;
    box(this->windowFeeds, 0, 0);
    box(this->windowArticles, 0, 0);

    for (i = 0; i < FEEDS_MAX; ++i)
    {
        if (this->choice == i + 1)
        {
            wattron(this->windowFeeds, A_REVERSE);
            mvwprintw(this->windowFeeds, y, x, "%s", feeds[i]->title);
            wattroff(this->windowFeeds, A_REVERSE);
        }
        else
        {
            mvwprintw(this->windowFeeds, y, x, "%s", feeds[i]->title);
        }
        ++y;
    }

    // TODO: Cleanup here!!

    x = 2;
    y = 1;
    for (int j = 0; j < FEEDS_MAX; j++)
    {
        if (this->articleChoice == j + 1)
        {
            wattron(this->windowArticles, A_REVERSE);
            mvwprintw(this->windowArticles, y, x, "%s", feeds[this->choice-1]->items[j]->title);
            wattroff(this->windowArticles, A_REVERSE);
        }
        else
        {
            mvwprintw(this->windowArticles, y, x, "%s", feeds[this->choice-1]->items[j]->title);
        }
        ++y;
    }

    wrefresh(this->windowFeeds);
    wrefresh(this->windowArticles);
}


/**
 * Increase choice
 *
 * @param new_choice
 * @return
 */
int CR_UI::increaseChoice(int new_choice)
{
    if (new_choice == feeds_count)
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
 * @param new_choice
 * @return
 */
int CR_UI::decreaseChoice(int new_choice)
{
    if (new_choice == 1)
    {
        new_choice = feeds_count;
    }
    else
    {
        --new_choice;
    }

    return new_choice;
}
