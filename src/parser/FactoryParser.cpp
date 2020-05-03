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

#include "parser/Parser.h"
#include "parser/FactoryParser.h"
using namespace crss;


/**
 * Constructor
 */
FactoryParser::FactoryParser() = default;


/**
 * Destructor
 */
FactoryParser::~FactoryParser() = default;


/**
 * Get correct parser
 *
 * @param content
 * @return
 */
Parser* FactoryParser::getInstance(struct rawRss content)
{
    Parser *parser;

    parser = new Parser(content);

    return parser;
}

/**
 * Determines the rss version
 *
 * @param content
 * @return
 */
unsigned int FactoryParser::getRssVersion(char* content)
{
    unsigned int version = 0;

    return version;
}


