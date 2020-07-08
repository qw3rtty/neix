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

#ifndef CRSS_APPLICATION_H
#define CRSS_APPLICATION_H

#include <ncurses.h>
#include "feed/Feeds.h"

namespace crss
{
    class Application
    {
    public:
        Application();
        ~Application();

        void show();
        void printPads();
        void printWindows();
        void resize();
        void printArticleDetailPad();

        int increaseChoice(int new_choice, int count);
        int decreaseChoice(int new_choice, int count);
        int increasePadOffset(int offset, int choice);
        int decreasePadOffset(int offset, int choice, int count);

    private:
        WINDOW *feedWindow;
        WINDOW *feedPad;
        int feedPadOffsetTop;

        WINDOW *articleWindow;
        WINDOW *articlePad;
        int articlePadOffsetTop;
        int articlePadOffsetTopDetail;

        bool reading;
        int lineSpacer;
        int choice;
        int articleChoice;
        int quit;
        int c;

        int windowHeight;
        int windowInnerHeight;
        int feedWindowWidth;
        int articleWindowWidth;

        void initChoices();
        void printVersion();
        void printControlHints();
        void createFeedWindow();
        void createArticleWindow();

        void printFeedsInWindow();
        void printArticlesInWindow();
        void refreshFeedPad();
        void refreshArticlePad();

        void printLineInWindow(WINDOW *window, int y, int x, char *line);
        void printLineHighlightedInWindow(WINDOW *window, int y, int x, char *line);
        void printArticleInWindow(WINDOW *window, int y, int x, struct rssItem *entry);
        void printArticleHighlightedInWindow(WINDOW *window, int y, int x, struct rssItem *entry);

        void openArticle();
        void openArticleLink();
    };
}

#endif //CRSS_APPLICATION_H
