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

#include <stdio.h>
#include <string.h>
#include <cstdlib>
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
 * @return  {*Feeds}
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
 * @param   {int}   index   - Index to check
 * @return  {bool}          - true if index is valid, false else
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
 * @param   {struct rss*}   newFeed     - New feed to add
 * @return  {boolean}                   - true on success, false else
 */
bool Feeds::add(struct rss *newFeed)
{
    this->rssFeeds[this->count] = (struct rss*) malloc(sizeof(struct rss));
    memcpy(&this->rssFeeds[this->count], &newFeed, sizeof(newFeed));
    this->count++;

    return true;
}


/**
 * Add given article to feed
 *
 * @param   {int}               feedIndex       - Index of feed
 * @param   {int}               articleIndex    - Index of new article
 * @param   {struct rssItem *}  newArticle      - The new article to add
 * @return  {boolean}                           - true on success, false else
 */
bool Feeds::addArticle(int feedIndex, int articleIndex, struct rssItem *newArticle)
{
    if (!this->validIndex(feedIndex))
    {
        throw "Index is not in range!";
    }

    this->rssFeeds[feedIndex]->items[articleIndex] = (struct rssItem*) malloc(FEEDS_MAX * sizeof(struct rssItem));
    this->rssFeeds[feedIndex]->items[articleIndex] = newArticle;

    return true;
}


/**
 * Get feed of given index
 *
 * @param   {int}           index   - Index of feed which should be returned
 * @return  {struct rss*}           - RSS feed
 */
struct rss *Feeds::get(int index)
{
    if (!this->validIndex(index))
    {
        throw "Index is not in range!";
    }

    return this->rssFeeds[index];
}


/**
 * Get specific article of feed
 *
 * @param   {int}               feedIndex       - Index of feed
 * @param   {int}               articleIndex    - Index of article
 * @return  {struct rssItem*}                   - RSS article of feed
 */
struct rssItem * Feeds::getArticle(int feedIndex, int articleIndex)
{
    if (!this->validIndex(feedIndex))
    {
        throw "Index is not in range!";
    }

    return this->rssFeeds[feedIndex]->items[articleIndex];
}


/**
 * Get count of all feeds
 *
 * @return  {int}   - Count of feeds
 */
int Feeds::getCount()
{
    return this->count;
}