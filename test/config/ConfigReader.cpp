/**
 * TEST Config reader.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <string>
#include <gtest/gtest.h>

#include "config/ConfigReader.h"

using namespace std;
using namespace crss;
namespace {
    TEST(ConfigReader, read)
    {
        ConfigReader reader(FEED_CONFIG_PATH_TEST);

        map<string, string> feedMap;
        feedMap = reader.read();

        EXPECT_EQ(feedMap.size(), 4);
    }
}
