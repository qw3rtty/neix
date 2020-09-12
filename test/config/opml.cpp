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
#include <vector>
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
    TEST(OPML, instance)
    {
        opml o;
        
        vector<pair<string, string>> list = o.getList();
        EXPECT_EQ(list.size(), 0);

        list.clear();
        list.push_back(make_pair("name", "link"));
        list.push_back(make_pair("name", "link"));
        
        o.setList(list);
        list = o.getList();
        EXPECT_EQ(list.size(), 2);
    }

    TEST(OPML, create)
    {
        vector<pair<string, string>> list;
        list.push_back(make_pair("name", "link"));
        list.push_back(make_pair("name", "link"));
    
        opml o;
        o.setList(list);
        o.create();

        string expected = R"(<?xml version="1.0" encoding="utf-8"?><opml version="2.0"><head><title>neix - news reader for your terminal</title></head><body><outline text="name" title="name" xmlUrl="link" type="rss"/><outline text="name" title="name" xmlUrl="link" type="rss"/></body></opml>)";
        string content = o.getContent();

        EXPECT_TRUE(strcmp(content.c_str(), expected.c_str()) == 0);
    }

    TEST(OPML, exporting)
    {
        opml o;

        vector<pair<string, string>> list;
        list.push_back(make_pair("name", "link"));
        list.push_back(make_pair("name", "link"));
        o.setList(list);
        
        o.create(); 
        string path = "~/.config/neix/export.xml";
        o.exportFeeds(path);

        try 
        {
            const string emptyPath = "";
            o.exportFeeds(emptyPath);
            EXPECT_TRUE(false); 
        } catch(...) {
            EXPECT_TRUE(true); 
        }
    }

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
