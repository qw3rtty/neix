/**
 * Factory parser class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_FACTORYPARSER_H
#define neix_FACTORYPARSER_H

#include "Parser.h"
#include "feed/FeedLoader.h"

namespace neix
{
    class FactoryParser
    {
    public:
        FactoryParser();
        ~FactoryParser();

        static Parser* getInstance(struct rawRss content);
        static double getRssVersion(char* content);
    };
}

#endif //neix_FACTORYPARSER_H
