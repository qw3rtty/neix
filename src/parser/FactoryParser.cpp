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

#include <regex>
#include <iostream>
#include <string>
#include <cstring>

#include "parser/Parser.h"
#include "parser/ParserAtom.h"
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
    unsigned int version = FactoryParser::getRssVersion(content.content);
    Parser *parser;

    parser = new ParserAtom(content);

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

    std::string str(content);
    std::regex regex(R"(<rss.+version="(\d+.\d+)\")");
    std::smatch match;

    if (std::regex_search(str, match, regex))
    {
        version = std::stoi(match.str(1));
    }

    return version;
}


