/**
 * TEST Config reader.
 *
 * @package     neix
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
using namespace neix;
namespace {
    TEST(ConfigReader, read)
    {
        ConfigReader reader(FEED_CONFIG_PATH_TEST);

        vector<pair<string, string>> feedList;
        feedList = reader.read();

        EXPECT_EQ(feedList.size(), 4);
    }

    TEST(ConfigReader, getConfigByPath)
    {
        vector<pair<string, string>> config = ConfigReader::getByPath(FEED_CONFIG_PATH_TEST);
        EXPECT_EQ(config.size(), 4);
    }
}
