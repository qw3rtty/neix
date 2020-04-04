/**
 * TEST Feeds.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <cassert>

#include "CR_FeedLoader.h"

int run_test_feeds()
{
    CR_FeedLoader feedLoader;
    bool feedLoaded = feedLoader.load("https://www.heise.de/developer/rss/news-atom.xml");
    assert(feedLoaded);
    assert(feeds_count == FEEDS_MAX);

    struct curl_temp xml_feed = feedLoader.getFeed();
    assert(xml_feed.content != NULL);
    assert(xml_feed.size > 0);

    return 0;
}
