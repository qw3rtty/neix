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
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "feed/FeedLoader.h"

using namespace crss;
int main()
{
    FeedLoader feedLoader;
    feedLoader.configPath.clear();
    feedLoader.configPath.str("");
    feedLoader.configPath << getenv("PWD") << "/test/testFeeds.conf";

    bool feedsLoaded = feedLoader.loadFeedsFromConfig();
    assert(feedsLoaded);

    bool articleLoaded = feedLoader.loadArticlesOfFeeds();
    assert(articleLoaded);

    bool xmlLoaded = feedLoader.load("https://www.heise.de/developer/rss/news-atom.xml");
    assert(xmlLoaded);

    struct rawRss xml_feed = feedLoader.getFeed();
    assert(xml_feed.content != NULL);
    assert(xml_feed.size > 0);

    return 0;
}
