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
#include <stdlib.h>
#include <ncurses.h>

#include "config.h"
#include "feeds.h"

void ui_print_feeds(WINDOW *window_feeds, int highlight)
{
    feeds_count = FEEDS_MAX;
    struct rss rss_feeds[FEEDS_MAX];
    for (int i = 0; i < 5; i++)
    {
        rss_feeds[i].title = "RSS Feed";
        rss_feeds[i].url = "https://www.heise.de/developer/rss/news-atom.xml";

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            struct rss_item *item_temp = malloc(sizeof(struct rss_item));
            item_temp->title = "RSS Article";

            rss_feeds[i].items[j] = malloc(FEEDS_MAX * sizeof(struct rss_item));
            rss_feeds[i].items[j] = item_temp;
        }
    }

    int x, y, i;

    x = 2;
    y = 2;
    box(window_feeds, 0, 0);

    for (i = 0; i < FEEDS_MAX; ++i)
    {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(window_feeds, A_REVERSE);
            mvwprintw(window_feeds, y, x, "%s", rss_feeds[i].title);
            wattroff(window_feeds, A_REVERSE);
        }
        else
        {
            mvwprintw(window_feeds, y, x, "%s", rss_feeds[i].title);
        }
        ++y;

        x += 2;
        for (int j = 0; j < FEEDS_MAX; j++)
        {
            mvwprintw(window_feeds, y, x, "%s", rss_feeds[i].items[j]->title);
            ++y;
        }
        x -= 2;
    }

    wrefresh(window_feeds);
}