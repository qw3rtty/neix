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

using namespace crss;

void testAtomParser()
{
    std::ifstream atom("./test/assets/atom.xml");
    std::stringstream atomContent;
    atomContent << atom.rdbuf();

    struct rawRss rawFeed = {};
    rawFeed.content = strdup(atomContent.str().c_str());
    rawFeed.size = 1234;

    Parser *parser = FactoryParser::getInstance(rawFeed);

    struct rssItem *item = parser->getFeedItem();
    assert(item != nullptr);

    char htmlText[] = "<p>Some text</p>";
    char *plaintext = parser->convertHtmlToPlaintext(htmlText);
    assert(strcmp(plaintext, "Some text") == 0);

    char *timeString = parser->formatTimeString("2020-04-26T15:15:00+02:00");
    assert(strcmp(timeString, "26.04.2020 15:15") == 0);

    timeString = parser->formatTimeString("2020-04-26T12:25:00.350+02:00");
    assert(strcmp(timeString, "26.04.2020 12:25") == 0);
}

void testRss20Parser()
{
    std::ifstream rss2("./test/assets/rss2.0.xml");
    std::stringstream rssContent;
    rssContent << rss2.rdbuf();

    struct rawRss rawFeed = {};
    rawFeed.content = strdup(rssContent.str().c_str());
    rawFeed.size = 1234;

    Parser *parser = FactoryParser::getInstance(rawFeed);

    struct rssItem *item = parser->getFeedItem();
    assert(item != nullptr);

    char htmlText[] = "<p>Some text</p>";
    char *plaintext = parser->convertHtmlToPlaintext(htmlText);
    assert(strcmp(plaintext, "Some text") == 0);

    char *timeString = parser->formatTimeString("Sun, 17 May 2020 03:45:56 +0200");
    assert(strcmp(timeString, "17.05.2020 03:45") == 0);

    timeString = parser->formatTimeString("Sat, 16 May 2020 23:20:16 +0200");
    assert(strcmp(timeString, "16.05.2020 23:20") == 0);
}

int main()
{
    testAtomParser();
    testRss20Parser();

    return 0;
}
