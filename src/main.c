#include <stdio.h>
#include <ncurses.h>

#include "config.h"
#include "ui.h"

char *choices[] = {
    "RSS 1",
    "RSS 2",
    "RSS 3",
    "RSS 4",
    "Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

int main()
{
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();    /* Line buffering disabled. pass on everything */

    int width = COLS;
    int height = LINES - 2;

    menu_win = newwin(height, width, 2, 0);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow/vim keys to go up and down, Press enter to select a choice, Press 'q' to quit.");
    refresh();

    print_menu(menu_win, highlight);

    while (1)
    {
        c = wgetch(menu_win);
        switch (c)
        {
            case KEY_UP:
            case KEY_K:
                if (highlight == 1)
                {
                    highlight = n_choices;
                }
                else
                {
                    --highlight;
                }
                break;

            case KEY_DOWN:
            case KEY_J:
                if (highlight == n_choices)
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

        print_menu(menu_win, highlight);
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
