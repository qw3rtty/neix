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

#ifndef CRSS_FEEDPARSER_H
#define CRSS_FEEDPARSER_H

#include "FeedLoader.h"

namespace cr
{
    class FeedParser
    {
    public:
        FeedParser();
        ~FeedParser();

        void setRawRss(struct rawRss rawContent);
        struct rssItem* getFeedItem();

    private:
        struct rawRss *rss;
    };
}

#endif //CRSS_FEEDPARSER_H
