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

#include <ncurses.h>
#include "application/ApplicationWindow.h"

using namespace crss;


/**
 * Constructor
 */
ApplicationWindow::ApplicationWindow()
{
    this->created = false;
    this->y = 0;
    this->x = 0;
    this->height = 0;
    this->width = 0;
    this->offsetTop = 0;
    this->highlight = 0;
    this->win = nullptr;
    this->pad = nullptr;
}


/**
 * Destructor
 */
ApplicationWindow::~ApplicationWindow() = default;


/**
 * Print main window
 */
void ApplicationWindow::_printWindow()
{
    refresh();
    wclear(this->pad);
    wclear(this->win);

    box(this->win, 0, 0);
    wrefresh(this->win);
}


/**
 * Print pad
 */
void ApplicationWindow::_printPad()
{
    prefresh(this->pad, this->offsetTop, 0, this->y+1, this->x+2, this->height, COLS);
}

/**
 * Print content of window
 */
void ApplicationWindow::_printContent()
{
    wclear(this->pad);
    int x = 0, y = 0, counter = 0;
    for (auto & line: this->content)
    {
        if (this->highlight == counter)
        {
            wattron(this->pad, A_REVERSE);
            mvwprintw(this->pad, y, x, "%s", line.c_str());
            wattroff(this->pad, A_REVERSE);
        }
        else
        {
            mvwprintw(this->pad, y, x, "%s", line.c_str());
        }
        y++;
        counter++;
    }

    this->_printPad();
}

/**
 * Create application window
 *
 * @return  true on success, false else
 */
bool ApplicationWindow::_create()
{
    this->win = newwin(this->height, this->width, this->y, this->x);
    keypad(this->win, TRUE);

    this->pad = newpad(200, this->width-4);
    keypad(this->pad, TRUE);

    return this->win != nullptr && this->pad != nullptr;
}

/**
 * Show application window
 */
void ApplicationWindow::show()
{
    if (!this->created)
    {
        this->created = this->_create();
    }

    this->_printWindow();
    this->_printContent();
    this->_printPad();
}


/**
 * Update window
 */
void ApplicationWindow::update()
{
    this->_printContent();
    this->_printPad();
}


/**
 * Clear window
 */
void ApplicationWindow::clear()
{
    this->highlight = 0;
    this->offsetTop = 0;
    this->content.clear();
    wclear(this->pad);
}

/**
 * Scroll window down
 */
void ApplicationWindow::scrollDown()
{
    if (this->highlight == 0)
    {
        this->offsetTop = 0;
    }
    else if (this->highlight >= this->height-2)
    {
        this->offsetTop++;
    }

    this->_printPad();
}


/**
 * Scroll window up
 */
void ApplicationWindow::scrollUp()
{
    int count = this->content.size();
    if (this->highlight == count-1)
    {
        this->offsetTop = count - (this->height - 2);
    }
    else if (this->offsetTop > 0)
    {
        this->offsetTop--;
    }

    this->_printPad();
}


/**
 * Set position of window
 *
 * @param y
 * @param x
 */
void ApplicationWindow::setPosition(int y, int x)
{
    this->y = y;
    this->x = x;
}


/**
 * Set dimensions of window
 *
 * @param height
 * @param width
 */
void ApplicationWindow::setDimensions(int height, int width)
{
    this->height = height;
    this->width = width;
}


/**
 * Push new content
 *
 * @param c
 */
void ApplicationWindow::pushContent(string c)
{
    this->content.push_back(c);
}


/**
 * Increase choice
 *
 * @param   new_choice      - The new choice index
 * @param   count           - Count of feeds/article
 */
void ApplicationWindow::increaseHighlight(int choice, int count)
{
    if (choice == count-1)
    {
        choice = 0;
    }
    else
    {
        choice++;
    }

    this->highlight = choice;
}


/**
 * Decrease choice
 *
 * @param   new_choice      - The new choice index
 * @param   count           - Count of feeds/article
 */
void ApplicationWindow::decreaseHighlight(int choice, int count)
{
    if (choice == 0)
    {
        choice = count-1;
    }
    else
    {
        choice--;
    }

    this->highlight = choice;
}


/**
 * Get ncurses window
 */
WINDOW *ApplicationWindow::getWindow()
{
    return this->win;
}
