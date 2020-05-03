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
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "feed/Feeds.h"

using namespace crss;
int main()
{
    Feeds *feeds = Feeds::getInstance();
    assert(feeds != nullptr);
    assert(feeds->getCount() == 0);

    // Create an feed to add
    struct rss *newFeed = (struct rss*) calloc(1, sizeof(struct rss));
    newFeed->title = strdup("Title");
    newFeed->url = strdup("https://www.some-example-url.com");

    // Add new feed
    feeds->add(newFeed);
    assert(feeds->getCount() == 1);
    assert(feeds->validIndex(1));

    // Add new feed
    feeds->add(newFeed);
    assert(feeds->getCount() == 2);
    assert(feeds->validIndex(2));

    assert(!feeds->validIndex(3));

    // Create an article to add
    struct rssItem *newArticle = (struct rssItem*) calloc(1, sizeof(struct rssItem));
    newArticle->title = strdup("Article title");
    newArticle->url = strdup("https://www.some-example-url.com");

    bool articleAdded = feeds->addArticle(1, 1, newArticle);
    assert(articleAdded);

    try {
        feeds->addArticle(5, 5, newArticle);
    }
    catch (std::out_of_range e) {
        assert(strcmp(e.what(), "Index is out of range!") == 0);
    }

    return 0;
}
