/**
 * RSS 2.0 parser class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef CRSS_PARSERRSS2_H
#define CRSS_PARSERRSS2_H

#include "rapidxml/rapidxml.hpp"
#include "feed/FeedLoader.h"
#include "Parser.h"

using namespace rapidxml;

namespace crss
{
    class ParserRSS2 : public Parser
    {
    public:
        explicit ParserRSS2(struct rawRss content);
        ~ParserRSS2();
        struct rssItem* getFeedItem() override;

    protected:
        char* getFeedDateFormat() override;
    };
}

#endif //CRSS_PARSERRSS2_H
