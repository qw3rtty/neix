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

#include "../rapidxml/rapidxml.hpp"
#include "FeedLoader.h"

using namespace rapidxml;

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
        xml_document<> xmlDocument;
        xml_node<> *rootNode;
        xml_node<> *entryNode;
        struct rawRss *rss;
    };
}

#endif //CRSS_FEEDPARSER_H
