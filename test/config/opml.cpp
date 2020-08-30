/**
 * TEST OPML import/export.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     GPL-3.0
 * @since       Version 0.1.2
 * @filesource
 */
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "config/opml.h"

using namespace std;
using namespace neix;

/**
 * Clear the file of given path.
 */
void cleanupTestImportConfig(const string& path)
{
    string cleanupCommand = "> " + path;
    system(cleanupCommand.c_str());
}

namespace {
	TEST(OPML, import)
	{
        cleanupTestImportConfig(IMPORT_CONFIG_PATH_TEST);
		
        unsigned int imported = opml::import(TEST_ASSET_OPML, 
                IMPORT_CONFIG_PATH_TEST);
		EXPECT_TRUE(imported != 0);
        EXPECT_EQ(imported, 13);
        
        cleanupTestImportConfig(IMPORT_CONFIG_PATH_TEST);
	}
}
