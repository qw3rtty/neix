/**
 * Factory parser class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef CRSS_FACTORYPARSER_H
#define CRSS_FACTORYPARSER_H

#include "Parser.h"
#include "feed/FeedLoader.h"

namespace crss
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

#endif //CRSS_FACTORYPARSER_H
