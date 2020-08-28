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
	TEST(ConfigReader, create)
    {
        ConfigReader cr = ConfigReader::create(MAIN_CONFIG_PATH_TEST);
        EXPECT_EQ(cr.count(), 4);

		vector<pair<string, string>> list = cr.getList();
		EXPECT_EQ(list.size(), 4);
    }

    TEST(ConfigReader, hasEntry)
    {
        ConfigReader reader = ConfigReader::create(MAIN_CONFIG_PATH_TEST);

        EXPECT_TRUE(reader.hasEntry("locale"));
		EXPECT_FALSE(reader.hasEntry("test"));
    }

    TEST(ConfigReader, getEntryByName)
    {
        ConfigReader reader = ConfigReader::create(MAIN_CONFIG_PATH_TEST);

		string configValue = reader.getEntryByName("openCommand");
        EXPECT_TRUE(strcmp(configValue.c_str(), "xdg-open") == 0);

		configValue = reader.getEntryByName("test");
		EXPECT_TRUE(configValue.empty());
    }
}
