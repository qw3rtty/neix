#include <stdio.h>
#include <ncurses.h>

#include "config.h"
#include "ui.h"
#include "feeds.h"

int main()
{
    if (feeds_load() == 0)
    {
        printf("Could not load feeds...\n");
        return 0;
    }

    WINDOW *window_feeds;
    int rss_choice = 1;
    int rss_article_choice = 0;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();

    int width = COLS;
    int height = LINES - 2;

    window_feeds = newwin(height, width, 2, 0);
    keypad(window_feeds, TRUE);
    mvprintw(0, 0, "Use arrow/vim keys to go up and down, Press enter to select a choice, Press 'q' to quit.");
    refresh();

    ui_print_feeds(window_feeds, rss_choice, rss_article_choice);

    while (1)
    {
        c = wgetch(window_feeds);
        switch (c)
        {
            case KEY_UP:
            case KEY_K:
                rss_article_choice = 0;
                rss_choice = decrease_choice(rss_choice);
                break;

            case KEY_DOWN:
            case KEY_J:
                rss_article_choice = 0;
                rss_choice = increase_choice(rss_choice);
                break;

            case KEY_UPPER_K:
                rss_article_choice = decrease_choice(rss_article_choice);
                break;

            case KEY_UPPER_J:
                rss_article_choice = increase_choice(rss_article_choice);
                break;

            case ENTER:
            case KEY_Q:
                choice = rss_choice;
                break;
                
            default:
                mvprintw(1, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }

        ui_print_feeds(window_feeds, rss_choice, rss_article_choice);
        if (choice != 0)
        {
            break;
        }
    }

    clrtoeol();
    refresh();
    endwin();

    return 0;
}
