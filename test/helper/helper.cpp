/**
 * TEST Helper function.
 *
 * @package     neix
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

    TEST(helper, getConfigHomePath)
    {
        string configHomePath = getConfigHomePath();
        string expectedPath = getenv("HOME"); 
        expectedPath += "/.config/neix/";

        EXPECT_TRUE(strcmp(configHomePath.c_str(), expectedPath.c_str()) == 0);
    }

    TEST(helper, getConfigPathByName)
    {
        string path = getConfigPathByName("test.conf");
        string expectedPath = getenv("HOME");
        expectedPath += "/.config/neix/test.conf";

        EXPECT_TRUE(strcmp(path.c_str(), expectedPath.c_str()) == 0);
    }


    TEST(helper, getMainConfigPath)
    {
        string path = getMainConfigPath();
        string expectedPath = getenv("HOME");
        expectedPath += "/.config/neix/neix.conf";

        EXPECT_TRUE(strcmp(path.c_str(), expectedPath.c_str()) == 0);
    }

    TEST(helper, getFeedConfigPath)
    {
        string path = getFeedConfigPath();
        string expectedPath = getenv("HOME");
        expectedPath += "/.config/neix/feeds.conf";

        EXPECT_TRUE(strcmp(path.c_str(), expectedPath.c_str()) == 0);
    }

    TEST(helper, configFilesExists)
    {
        bool exists = configFilesExists();
        EXPECT_TRUE(exists);
    }
}
