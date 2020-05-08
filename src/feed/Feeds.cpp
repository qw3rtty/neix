/**
 * Feeds singleton class.
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
#include <cstdio>
#include "feed/Feeds.h"

using namespace crss;


/**
 * Instance
 */
Feeds *Feeds::instance = nullptr;


/**
 * Constructor
 */
Feeds::Feeds()
{
    this->count = 0;
}


/**
 * Get instance of feeds
 *
 * @return  The instance
 */
Feeds *Feeds::getInstance()
{
    if (!instance)
    {
        instance = new Feeds;
    }

    return instance;
}


/**
 * Validate if given index is in range
 *
 * @param  index    - Index to check
 * @return         true if index is valid, false else
 */
bool Feeds::validIndex(int index)
{
    bool valid = true;

    if (index < 0 || index > this->getCount())
    {
        valid = false;
    }

    return valid;
}


/**
 * Add given feed
 *
 * @param   newFeed     - New feed to addFeed
 * @return  true on success, false else
 */
bool Feeds::addFeed(struct rss *newFeed)
{
    this->rssFeeds[this->count] = (struct rss*) calloc(1, sizeof(struct rss));
    this->rssFeeds[this->count]->articleCount = newFeed->articleCount;
    this->rssFeeds[this->count]->unreadCount = newFeed->unreadCount;

    memcpy(&this->rssFeeds[this->count]->title, &newFeed->title, sizeof(newFeed->title));
    memcpy(&this->rssFeeds[this->count]->url, &newFeed->url, sizeof(newFeed->url));
    this->count++;

    return true;
}


/**
 * Add given article to feed
 *
 * @param   feedIndex       - Index of feed
 * @param   articleIndex    - Index of new article
 * @param   newArticle      - The new article to addFeed
 * @return  true on success, false else
 */
bool Feeds::addArticle(int feedIndex, int articleIndex, struct rssItem *newArticle)
{
    if (!this->validIndex(feedIndex))
    {
        throw std::out_of_range("Index is out of range!");
    }

    this->rssFeeds[feedIndex]->items[articleIndex] = (struct rssItem*) calloc(FEEDS_MAX, sizeof(struct rssItem));
    this->rssFeeds[feedIndex]->items[articleIndex] = newArticle;

    this->rssFeeds[feedIndex]->articleCount++;
    this->rssFeeds[feedIndex]->unreadCount++;

    return true;
}


/**
 * Get feed of given index
 *
 * @param   index   - Index of feed which should be returned
 * @return  The RSS feed
 */
struct rss *Feeds::getFeed(int index)
{
    if (!this->validIndex(index))
    {
        throw std::out_of_range("Index is out of range!");
    }

    return this->rssFeeds[index];
}


/**
 * Get specific article of feed
 *
 * @param   feedIndex       - Index of feed
 * @param   articleIndex    - Index of article
 * @return  RSS article of feed
 */
struct rssItem * Feeds::getArticle(int feedIndex, int articleIndex)
{
    if (!this->validIndex(feedIndex))
    {
        throw std::out_of_range("Index is out of range!");
    }

    return this->rssFeeds[feedIndex]->items[articleIndex];
}


/**
 * Get count of all feeds
 *
 * @return  Count of feeds
 */
int Feeds::getCount()
{
    return this->count;
}


/**
 * Create feed line with unread/item count
 *
 * @param   feedIndex   Index of feed
 * @return  Title line of feed
 */
char* Feeds::getFeedLineTitle(int feedIndex)
{
    Feeds *feeds = Feeds::getInstance();
    struct rss *feed = feeds->getFeed(feedIndex);

    char *line = feed->title;
    char *lineWithCount = (char*) calloc((strlen(line) + 10), sizeof(char));
    sprintf(lineWithCount, "%s [%d/%d]", line, feed->unreadCount, feed->articleCount);

    return lineWithCount;
}
