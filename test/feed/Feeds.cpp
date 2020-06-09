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
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "feed/Feeds.h"

using namespace std;
using namespace crss;

int main()
{
    Feeds *feeds = Feeds::getInstance();
    assert(feeds != nullptr);
    assert(feeds->getCount() == 0);

    // Create an feed to addFeed
    struct rss *newFeed = (struct rss*) calloc(1, sizeof(struct rss));
    newFeed->title = strdup("Title");
    newFeed->url = strdup("https://www.some-example-url.com");

    // Add new feed
    feeds->addFeed(newFeed);
    assert(feeds->getCount() == 1);
    assert(feeds->validIndex(1));

    // Add new feed
    feeds->addFeed(newFeed);
    assert(feeds->getCount() == 2);
    assert(feeds->validIndex(2));

    // Check for some invalid index values
    assert(!feeds->validIndex(3));
    assert(!feeds->validIndex(-1));

    // Create an article to add
    struct rssItem *newArticle = (struct rssItem*) calloc(1, sizeof(struct rssItem));
    newArticle->title = strdup("Article title");
    newArticle->url = strdup("https://www.some-example-url.com");
    newArticle->description = strdup("This is a description just for test.");
    newArticle->date = strdup("2003-12-13T18:30:02Z");
    newArticle->read = 1;

    bool articleAdded = feeds->addArticle(1, 1, newArticle);
    assert(articleAdded);

    articleAdded = feeds->addArticle(1, 2, newArticle);
    assert(articleAdded);

    // Check feed title
    char *title = strdup(feeds->getFeedLineTitle(1));
    cout << title << endl;
    assert(strcmp(title, "Title [2/2]") == 0);
    assert(strcmp(title, "Sub power title") != 0);

    try {
        feeds->addArticle(5, 5, newArticle);
    }
    catch (out_of_range &e) {
        assert(strcmp(e.what(), "Index is out of range!") == 0);
    }

    return 0;
}
