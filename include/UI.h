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

#ifndef CRSS_UI_H
#define CRSS_UI_H

#include <ncurses.h>

namespace crss
{
    class UI
    {
    public:
        UI();
        ~UI();

        void show();
        void printWindows();
        int increaseChoice(int new_choice, int count);
        int decreaseChoice(int new_choice, int count);

    private:
        WINDOW *feedWindow;
        WINDOW *articleWindow;

        int choice;
        int articleChoice;
        int quit;
        int c;

        int windowHeight;
        int feedWindowWidth;
        int articleWindowWidth;

        void initChoices();
        void createFeedWindow();
        void createArticleWindow();

        void printFeedsInWindow();
        void printArticlesInWindow();
        void printLineInWindow(WINDOW *window, int y, int x, char *line);
        void printLineHighlightedInWindow(WINDOW *window, int y, int x, char *line);

        void openArticle();
    };
}

#endif //CRSS_UI_H
