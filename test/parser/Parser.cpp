/**
 * TEST feed parser.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <cstring>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

#include "parser/FactoryParser.h"
#include "parser/Parser.h"

using namespace std;
using namespace crss;
namespace {
    TEST(Parser, main)
    {
        ifstream atom("./test/assets/atom.xml");
        stringstream atomContent;
        atomContent << atom.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(atomContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        char *dateFormat = parser->getTimeFormatUI();
        EXPECT_TRUE(strcmp(dateFormat, "%d.%m.%Y %H:%M") == 0);

        struct rssItem *item = parser->getFeedItem();
        EXPECT_TRUE(item != nullptr);

        string title = parser->getFeedTitle();
        EXPECT_EQ(title, "Atom-Powered Robots Run Amok");

        string content = parser->getFeedContent();
        EXPECT_EQ(content, "Some text.");

        string link = parser->getFeedLink();
        EXPECT_EQ(link, "http://example.org/2003/12/13/atom03");

        string date = parser->getFeedDate();
        EXPECT_EQ(date, "13.12.2003 18:30");

        char htmlText[] = "<p>Some text</p>";
        string plaintext = parser->convertHtmlToPlaintext(htmlText);
        EXPECT_EQ(plaintext, "Some text");

        string timeString = parser->formatTimeString("2020-04-26T15:15:00+02:00");
        EXPECT_EQ(timeString, "26.04.2020 15:15");

        parser->setTimeFormatUI("%d.%m.%Y");
        timeString = parser->formatTimeString("2020-04-26T12:25:00.350+02:00");
        EXPECT_EQ(timeString, "26.04.2020");
    }

    TEST(Parser, atom)
    {
        ifstream atom("./test/assets/atom.xml");
        stringstream atomContent;
        atomContent << atom.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(atomContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }

    TEST(Parser, rss0x91)
    {
        ifstream rss("./test/assets/rss0.91.xml");
        stringstream rssContent;
        rssContent << rss.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(rssContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }

    TEST(Parser, rss0x92)
    {
        ifstream rss("./test/assets/rss0.92.xml");
        stringstream rssContent;
        rssContent << rss.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(rssContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }

    TEST(Parser, rss2x0)
    {
        ifstream rss("./test/assets/rss2.0.xml");
        stringstream rssContent;
        rssContent << rss.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(rssContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }
}
