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
#include "feed/Feeds.h"
#include "feed/FeedLoader.h"

using namespace crss;
int main()
{
	Feeds *feeds = Feeds::getInstance();
    FeedLoader feedLoader;
    feedLoader.configPath.clear();
    feedLoader.configPath.str("");
    feedLoader.configPath << getenv("PWD") << "/test/testFeeds.conf";

    bool feedsLoaded = feedLoader.loadFeedsFromConfig(feeds);
    assert(feedsLoaded);

    bool articleLoaded = feedLoader.loadArticlesOfFeeds(feeds);
    assert(articleLoaded);

    bool xmlLoaded = feedLoader.load("https://www.heise.de/developer/rss/news-atom.xml");
    assert(xmlLoaded);

    struct rawRss xml_feed = feedLoader.getFeed();
    assert(xml_feed.content != NULL);
    assert(xml_feed.size > 0);

    return 0;
}
