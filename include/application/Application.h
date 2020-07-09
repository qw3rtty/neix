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

#include <string>
#include <ncurses.h>
#include "application/ApplicationWindow.h"
#include "feed/Feeds.h"

using namespace std;
namespace crss
{
    class Application
    {
    public:
        Application();
        ~Application();

        void show();
        void fillWindowsWithContent();
        void printWindows();
        void resize();

        int increaseChoice(int new_choice, int count);
        int decreaseChoice(int new_choice, int count);

    private:
        ApplicationWindow fw;
        ApplicationWindow aw;

        bool reading;
        int choice;
        int articleChoice;
        int quit;
        int c;

        int windowHeight;
        int feedWindowWidth;
        int articleWindowWidth;

        void initChoices();
        void printVersion();
        void printControlHints();
        void createFeedWindow();
        void createArticleWindow();

        void printFeedsInWindow();
        void printArticlesInWindow();
        string printArticleInWindow(struct rssItem *entry);

        void openArticle();
        void openArticleLink();
    };
}

#endif //CRSS_APPLICATION_H
