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
#include <cassert>
#include <cstring>
#include <fstream>
#include <string>

#include "parser/FactoryParser.h"
#include "parser/Parser.h"

using namespace std;
using namespace crss;

void testParser()
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
    assert(strcmp(dateFormat, "%d.%m.%Y %H:%M") == 0);

    struct rssItem *item = parser->getFeedItem();
    assert(item != nullptr);

    char htmlText[] = "<p>Some text</p>";
    char *plaintext = parser->convertHtmlToPlaintext(htmlText);
    assert(strcmp(plaintext, "Some text") == 0);

    char *timeString = parser->formatTimeString("2020-04-26T15:15:00+02:00");
    assert(strcmp(timeString, "26.04.2020 15:15") == 0);

    parser->setTimeFormatUI("%d.%m.%Y");
    timeString = parser->formatTimeString("2020-04-26T12:25:00.350+02:00");
    assert(strcmp(timeString, "26.04.2020") == 0);
}

void testAtomParser()
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
    assert(item != nullptr);
}

void testRss0x91Parser()
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
    assert(item != nullptr);
}


void testRss0x92Parser()
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
    assert(item != nullptr);
}


void testRss20Parser()
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
    assert(item != nullptr);
}

int main()
{
	testParser();
    testAtomParser();
    testRss0x91Parser();
    testRss0x92Parser();
    testRss20Parser();

    return 0;
}
