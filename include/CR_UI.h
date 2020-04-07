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

    void printUI(WINDOW *window_feeds, int rss_choice, int rss_article_choice);
    int increaseChoice(int new_choice);
    int decreaseChoice(int new_choice);
};

#endif //CRSS_CR_UI_H
