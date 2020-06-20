/**
 * TEST Helper function.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <string>
#include <algorithm>
#include <gtest/gtest.h>

#include "helper/helper.h"

using namespace std;
namespace {
    TEST(helper, ltrim)
    {
        string text = "   \t\tHello World";
        EXPECT_EQ(ltrim(text), "Hello World");
    }

    TEST(helper, rtrim)
    {
        string text = "Hello World\t\t\n    \t\n";
        EXPECT_EQ(rtrim(text), "Hello World");
    }

    TEST(helper, trim)
    {
        string text = "   \t Hello World \t\v   ";
        EXPECT_EQ(trim(text), "Hello World");
    }
}
