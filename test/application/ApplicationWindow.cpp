/**
 * TEST application window.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <gtest/gtest.h>
#include <ncurses.h>

#include "application/ApplicationWindow.h"

using namespace std;
using namespace crss;

class TestApplicationWindow : public ApplicationWindow
{
public:
    int getHeight()
    {
        return this->height;
    }

    int getWidth()
    {
        return this->width;
    }

    int getY()
    {
        return this->y;
    }

    int getX()
    {
        return this->x;
    }

    int getOffsetTop()
    {
        return this->offsetTop;
    }

    int getHighlight()
    {
        return this->highlight;
    }

    int getContentSize()
    {
        return this->content.size();
    }

    void scrollDownX(int x)
    {
        for (int i = 0; i < x; i++)
        {
            this->increaseHighlight();
            this->scrollDown();
        }
    }

    void scrollUpX(int x)
    {
        for (int i = 0; i < x; i++)
        {
            this->decreaseHighlight();
            this->scrollUp();
        }
    }

    void pushXContentLines(int x)
    {
        string line = "Testing line";
        for (int i = 0; i < x; i++)
        {
            this->pushContent(line);
        }
    }
};

namespace {
    TEST(ApplicationWindow, base)
    {
        TestApplicationWindow aw;
        aw.setDimensions(10, 15);
        ASSERT_EQ(aw.getHeight(), 10);
        ASSERT_EQ(aw.getWidth(), 15);

        aw.setPosition(5, 15);
        ASSERT_EQ(aw.getY(), 5);
        ASSERT_EQ(aw.getX(), 15);

        WINDOW *win = aw.getWindow();
        ASSERT_EQ(win, nullptr);

        aw.reset();
        ASSERT_EQ(aw.getOffsetTop(), 0);
        ASSERT_EQ(aw.getContentSize(), 0);
    }

    TEST(ApplicationWindow, content)
    {
        TestApplicationWindow aw;

        string line = "Just a line here";
        aw.pushContent(line);
        ASSERT_EQ(aw.getContentSize(), 1);

        line = "Another line here";
        aw.pushContent(line);
        ASSERT_EQ(aw.getContentSize(), 2);

        aw.pushXContentLines(14);
        ASSERT_EQ(aw.getContentSize(), 16);

        aw.resetContent();
        ASSERT_EQ(aw.getContentSize(), 0);
    }

    TEST(ApplicationWindow, scroll_always)
    {
        TestApplicationWindow aw;
        aw.scrollAlways = true;
        ASSERT_EQ(aw.getOffsetTop(), 0);

        aw.scrollDown();
        ASSERT_EQ(aw.getOffsetTop(), 1);

        aw.scrollUp();
        ASSERT_EQ(aw.getOffsetTop(), 0);

        aw.scrollDownX(34);
        ASSERT_EQ(aw.getOffsetTop(), 34);

        aw.scrollDownX( 16);
        ASSERT_EQ(aw.getOffsetTop(), 50);

        aw.scrollUpX(15);
        ASSERT_EQ(aw.getOffsetTop(), 35);

        aw.scrollUpX(238);
        ASSERT_EQ(aw.getOffsetTop(), 0);
    }

    TEST(ApplicationWindow, scroll_content)
    {
        TestApplicationWindow aw;
        aw.setDimensions(5, 20);
        aw.pushXContentLines(20);

        aw.scrollDownX(1);
        ASSERT_EQ(aw.getOffsetTop(), 0);
        ASSERT_EQ(aw.getHighlight(), 1);

        aw.scrollUpX(1);
        ASSERT_EQ(aw.getOffsetTop(), 0);
        ASSERT_EQ(aw.getHighlight(), 0);

        aw.scrollDownX(13);
        ASSERT_EQ(aw.getOffsetTop(), 11);
        ASSERT_EQ(aw.getHighlight(), 13);

        aw.scrollUpX(11);
        ASSERT_EQ(aw.getOffsetTop(), 0);
        ASSERT_EQ(aw.getHighlight(), 2);

        aw.scrollDownX(37);
        ASSERT_EQ(aw.getOffsetTop(), 17);
        ASSERT_EQ(aw.getHighlight(), 19);
    }
}
