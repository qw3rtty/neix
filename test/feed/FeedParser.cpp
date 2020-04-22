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
#include <cstdlib>

#include "feed/FeedLoader.h"
#include "feed/FeedParser.h"
using namespace crss;

int main()
{
    FeedLoader feedLoader;
    feedLoader.load("https://www.heise.de/developer/rss/news-atom.xml");

    FeedParser parser;
    parser.setRawRss(feedLoader.getFeed());

    struct rssItem *item = parser.getFeedItem();
    assert(item != nullptr);

    return 0;
}
