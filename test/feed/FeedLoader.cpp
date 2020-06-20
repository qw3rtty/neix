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
#include <cstdlib>
#include <gtest/gtest.h>

#include "feed/FeedLoader.h"

using namespace crss;
namespace {
    TEST(FeedLoader, load)
    {
        FeedLoader loader;
        bool xmlLoaded = loader.load("https://www.heise.de/developer/rss/news-atom.xml");
        EXPECT_TRUE(xmlLoaded);
    }

    TEST(FeedLoader, checkFeed)
    {
        FeedLoader loader;
        loader.load("https://www.heise.de/developer/rss/news-atom.xml");

        struct rawRss xml_feed = loader.getFeed();
        EXPECT_TRUE(xml_feed.content != NULL);
        EXPECT_GT(xml_feed.size, 0);
    }
}
