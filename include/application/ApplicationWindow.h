/**
 * Application Window class
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <string>
#include <vector>
#include <ncurses.h>

#ifndef CRSS_APPLICATIONWINDOW_H
#define CRSS_APPLICATIONWINDOW_H

using namespace std;
namespace crss
{
    class ApplicationWindow
    {
    public:
        ApplicationWindow();
        ~ApplicationWindow();

        bool enableHighlight;
        bool scrollAlways;

        void show();
        void update();
        void clear();
        void resetHighlight();
        void scrollDown();
        void scrollUp();

        void setPosition(int y, int x);
        void setDimensions(int height, int width);
        void pushContent(string c);

        void increaseHighlight();
        void decreaseHighlight();

        WINDOW *getWindow();

    protected:
        bool created;
        int y, x;
        int height, width;
        int offsetTop;
        int highlight;
        vector<string> content;
        WINDOW *win, *pad;

        bool _create();
        void _increaseOffsetTop();
        void _decreaseOffsetTop();
        void _scrollUpDependingOnContentSize();
        void _scrollDownDependingOnContentSize();
        void _printWindow();
        void _printPad();
        void _printContent();
    };
}

#endif //CCRSS_APPLICATIONWINDOW_H