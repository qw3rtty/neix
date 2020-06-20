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
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <gtest/gtest.h>
#include "feed/Feeds.h"

using namespace std;
using namespace crss;
namespace {
    TEST(Feeds, instance)
    {
        Feeds *feeds = Feeds::getInstance();
        EXPECT_TRUE(feeds != nullptr);
        EXPECT_TRUE(feeds->getCount() == 0);
    }

    TEST(Feeds, addFeeds)
    {
        Feeds *feeds = Feeds::getInstance();
        // Create an feed to addFeed
        struct rss *newFeed = (struct rss*) calloc(1, sizeof(struct rss));
        newFeed->title = strdup("Title");
        newFeed->url = strdup("https://www.some-example-url.com");

        // Add new feed
        feeds->addFeed(newFeed);
        EXPECT_TRUE(feeds->getCount() == 1);
        EXPECT_EQ(feeds->validIndex(1), true);

        // Add new feed
        feeds->addFeed(newFeed);
        EXPECT_TRUE(feeds->getCount() == 2);
        EXPECT_EQ(feeds->validIndex(2), true);

        // Check for some invalid index values
        EXPECT_TRUE(!feeds->validIndex(3));
        EXPECT_TRUE(!feeds->validIndex(-1));
    }

    TEST(Feeds, addArticles)
    {
        Feeds *feeds = Feeds::getInstance();

        // Create an feed to addFeed
        struct rss *newFeed = (struct rss*) calloc(1, sizeof(struct rss));
        newFeed->title = strdup("Title");
        newFeed->url = strdup("https://www.some-example-url.com");

        // Add new feed
        feeds->addFeed(newFeed);

        // Create an article to add
        struct rssItem *newArticle = (struct rssItem*) calloc(1, sizeof(struct rssItem));
        newArticle->title = strdup("Article title");
        newArticle->url = strdup("https://www.some-example-url.com");
        newArticle->description = strdup("This is a description just for test.");
        newArticle->date = strdup("2003-12-13T18:30:02Z");
        newArticle->read = 1;

        bool articleAdded = feeds->addArticle(1, 1, newArticle);
        EXPECT_TRUE(articleAdded);

        articleAdded = feeds->addArticle(1, 2, newArticle);
        EXPECT_TRUE(articleAdded);

        // Check feed title
        string title = strdup(feeds->getFeedLineTitle(1));
        EXPECT_EQ(title, "Title [2/2]");
        EXPECT_NE(title, "Sub power title");

        EXPECT_ANY_THROW(feeds->addArticle(5, 5, newArticle));
    }
}
