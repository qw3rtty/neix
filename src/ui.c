/**
 * Terminal UI.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <stdio.h>
#include <ncurses.h>

#include "config.h"

void print_feeds(WINDOW *window_feeds, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(window_feeds, 0, 0);

    for (i = 0; i < feeds_count; ++i)
    {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(window_feeds, A_REVERSE);
            mvwprintw(window_feeds, y, x, "%s", feeds[i]);
            wattroff(window_feeds, A_REVERSE);
        }
        else
        {
            mvwprintw(window_feeds, y, x, "%s", feeds[i]);
        }
        ++y;
    }

    wrefresh(window_feeds);
}