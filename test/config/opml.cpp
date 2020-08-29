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

/**
 * Get line count of given file path.
 *
 * @return  count
 */
unsigned int getConfigLineCount(const string& path)
{
    unsigned int count = 0;
    ifstream file;
    file.open(path);
    if (!file.is_open())
    {
        return count; 
    }

    string line;
    while (!file.eof())
    {
        getline(file, line); 

        if (!line.empty())
        {
            count++;
        }
    }
    file.close();

    return count;
}

namespace {
	TEST(OPML, import)
	{
        cleanupTestImportConfig(IMPORT_CONFIG_PATH_TEST);
		
        bool imported = opml::import(TEST_ASSET_OPML, IMPORT_CONFIG_PATH_TEST);
		EXPECT_TRUE(imported);

        unsigned int importCount = getConfigLineCount(IMPORT_CONFIG_PATH_TEST);
        EXPECT_EQ(importCount, 13);
	}
}
