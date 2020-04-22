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

#include "feed/FeedLoader.h"
using namespace crss;

int main()
{
    FeedLoader feedLoader;
    bool xmlLoaded = feedLoader.load("https://www.heise.de/developer/rss/news-atom.xml");
    assert(xmlLoaded);

    bool feedsLoaded = feedLoader.loadFeedsFromConfig();
    assert(feedsLoaded);

    bool articleLoaded = feedLoader.loadArticlesOfFeeds();
    assert(articleLoaded);

    struct rawRss xml_feed = feedLoader.getFeed();
    assert(xml_feed.content != NULL);
    assert(xml_feed.size > 0);

    return 0;
}
