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

#include "parser/FactoryParser.h"
#include "parser/Parser.h"

using namespace crss;
int main()
{
    std::string content(R"(<?xml version="1.0" encoding="utf-8"?><feed xmlns="http://www.w3.org/2005/Atom"><title>Example Feed</title><link href="http://example.org/"/><updated>2020-05-05T17:05:00+02:00</updated><author><name>John Doe</name></author><id>urn:uuid:60a76c80-d399-11d9-b93C-0003939e0af6</id><entry><title>Atom-Powered Robots Run Amok</title><link href="http://example.org/2003/12/13/atom03"/><id>urn:uuid:1225c695-cfb8-4ebb-aaaa-80da344efa6a</id><updated>2003-12-13T18:30:02Z</updated><summary>Some text.</summary></entry></feed>)");
    struct rawRss rawFeed = {};
    rawFeed.content = strdup(content.c_str());
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

    return 0;
}
