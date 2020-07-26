/**
 * Atom parser class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_PARSERATOM_H
#define neix_PARSERATOM_H

#include "rapidxml/rapidxml.hpp"
#include "feed/FeedLoader.h"
#include "Parser.h"

using namespace rapidxml;

namespace neix
{
    class ParserAtom : public Parser
    {
    public:
        explicit ParserAtom(struct rawRss content);
        ~ParserAtom();

        xml_node<>* getFirstNode() override;
        char* getFeedTitle() override;
        char* getFeedContent() override;
        char* getFeedLink() override;
        char* getFeedDate() override;

    protected:
        char* getFeedDateFormat() override;
    };
}

#endif //neix_PARSERATOM_H
