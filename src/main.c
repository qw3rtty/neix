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
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();    /* Line buffering disabled. pass on everything */

    int width = COLS;
    int height = LINES - 2;

    window_feeds = newwin(height, width, 2, 0);
    keypad(window_feeds, TRUE);
    mvprintw(0, 0, "Use arrow/vim keys to go up and down, Press enter to select a choice, Press 'q' to quit.");
    refresh();

    ui_print_feeds(window_feeds, highlight);

    while (1)
    {
        c = wgetch(window_feeds);
        switch (c)
        {
            case KEY_UP:
            case KEY_K:
                if (highlight == 1)
                {
                    highlight = feeds_count;
                }
                else
                {
                    --highlight;
                }
                break;

            case KEY_DOWN:
            case KEY_J:
                if (highlight == feeds_count)
                {
                    highlight = 1;
                }
                else
                {
                    ++highlight;
                }
                break;

            case ENTER:
            case KEY_Q:
                choice = highlight;
                break;
                
            default:
                mvprintw(1, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }

        ui_print_feeds(window_feeds, highlight);
        if (choice != 0)
        {    /* User did a choice come out of the infinite loop */
            break;
        }
    }

    clrtoeol();
    refresh();
    endwin();

    return 0;
}
