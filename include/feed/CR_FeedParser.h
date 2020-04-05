/**
 * Feed parser class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef CRSS_CR_FEEDPARSER_H
#define CRSS_CR_FEEDPARSER_H

#include "CR_FeedLoader.h"

class CR_FeedParser
{
public:
    CR_FeedParser();
    ~CR_FeedParser();

    void setRawRss(struct rawRss rawContent);

    char* getFeedTitle();
    char* getFeedUrl();
    struct rssItem* getFeedItem();

private:
    struct rawRss *rss;
};

#endif //CRSS_CR_FEEDPARSER_H
