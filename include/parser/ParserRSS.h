/**
 * RSS 2.0 parser class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_PARSERRSS_H
#define neix_PARSERRSS_H

#include "rapidxml/rapidxml.hpp"
#include "feed/FeedLoader.h"
#include "Parser.h"

using namespace rapidxml;

namespace neix
{
    class ParserRSS : public Parser
    {
    public:
        explicit ParserRSS(struct rawRss content);
        ~ParserRSS();

        xml_node<>* getFirstNode() override;
        char* getFeedTitle() override;
        char* getFeedContent() override;
        char* getFeedLink() override;
        char* getFeedDate() override;

    protected:
        char* getFeedDateFormat() override;
    };
}

#endif //neix_PARSERRSS_H
