/**
 * Terminal UI class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_APPLICATION_H
#define neix_APPLICATION_H

#include <string>
#include <ncurses.h>
#include "application/ApplicationWindow.h"
#include "feed/Feeds.h"

using namespace std;
namespace neix
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

        string openCommand;
        string renderCommand;

    private:
        ApplicationWindow fw;
        ApplicationWindow aw;
        ApplicationWindow rw;

        bool reading;
        int choice;
        int articleChoice;
        int quit;
        int c;

        int feedWindowWidth;
        int feedWindowHeight;
        int articleWindowWidth;
        int articleWindowHeight;

        void initChoices();
        void printVersion();
        void printControlHints();
        void createFeedWindow();
        void createArticleWindow();
        void createReadWindow();

        void printFeedsInWindow();
        void printArticlesInWindow();
        string printArticleInWindow(struct rssItem *entry);

        void openArticle();
        void openArticleLink();
    };
}

#endif //neix_APPLICATION_H
