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

#include "feed/FeedLoader.h"
#include "parser/Parser.h"
using namespace crss;

int main()
{
    FeedLoader feedLoader;
    feedLoader.load("https://www.heise.de/developer/rss/news-atom.xml");

    Parser parser;
    parser.setRawRss(feedLoader.getFeed());

    struct rssItem *item = parser.getFeedItem();
    assert(item != nullptr);

    char htmlText[] = "<p>Some text</p>";
    char *plaintext = parser.convertHtmlToPlaintext(htmlText);
    assert(strcmp(plaintext, "Some text") == 0);

    char *timeString = parser.formatTimeString("2020-04-26T15:15:00+02:00");
    assert(strcmp(timeString, "26.04.2020 15:15") == 0);

    return 0;
}
