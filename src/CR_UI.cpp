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
#include <ncurses.h>

#include "CR_UI.h"
#include "feed/CR_FeedLoader.h"

/**
 * Constructor
 */
CR_UI::CR_UI() = default;


/**
 * Destructor
 */
CR_UI::~CR_UI() = default;


/**
 * Print UI window
 *
 * @param window_feeds
 * @param rss_choice
 * @param rss_article_choice
 */
void CR_UI::printUI(WINDOW *window_feeds, int rss_choice, int rss_article_choice)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(window_feeds, 0, 0);

    for (i = 0; i < FEEDS_MAX; ++i)
    {
        if (rss_choice == i + 1)
        {
            wattron(window_feeds, A_REVERSE);
            mvwprintw(window_feeds, y, x, "%s", feeds[i]->title);
            wattroff(window_feeds, A_REVERSE);
        }
        else
        {
            mvwprintw(window_feeds, y, x, "%s", feeds[i]->title);
        }
        ++y;

        x += 2;
        for (int j = 0; j < FEEDS_MAX; j++)
        {
            if (rss_choice == i + 1 && rss_article_choice == j + 1)
            {
                wattron(window_feeds, A_REVERSE);
                mvwprintw(window_feeds, y, x, "%s", feeds[i]->items[j]->title);
                wattroff(window_feeds, A_REVERSE);
            }
            else
            {
                mvwprintw(window_feeds, y, x, "%s", feeds[i]->items[j]->title);
            }
            ++y;
        }
        x -= 2;
    }

    wrefresh(window_feeds);
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
