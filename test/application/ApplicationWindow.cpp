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

#include "application/ApplicationWindow.h"

using namespace std;
using namespace crss;
namespace {
    TEST(ApplicationWindow, all)
    {
        ApplicationWindow aw;
        aw.setDimensions(10, 15);
        aw.setPosition(5, 5);
        aw.show();
        aw.scrollDown();
        aw.scrollUp();
    }
}
