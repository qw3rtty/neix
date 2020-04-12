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

#ifndef CRSS_CR_UI_H
#define CRSS_CR_UI_H

#include <ncurses.h>

class CR_UI
{
public:
    CR_UI();
    ~CR_UI();

    void showUI();
    void printWindows();
    int increaseChoice(int new_choice);
    int decreaseChoice(int new_choice);

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

#endif //CRSS_CR_UI_H
