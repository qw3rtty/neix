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
#include <string>

#include "parser/Parser.h"
#include "parser/ParserAtom.h"
#include "parser/ParserRSS2.h"
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
    double version = FactoryParser::getRssVersion(content.content);
    Parser *parser;

	if (version == 2)
	{
		parser = new ParserRSS2(content);
	}
	else if (version == 0.91 || version == 0.92)
	{
		parser = new ParserRSS2(content);
	}
	else
	{
		parser = new ParserAtom(content);	
	}

    return parser;
}

/**
 * Determines the rss version
 *
 * @param content
 * @return
 */
double FactoryParser::getRssVersion(char* content)
{
	double version = 0.0;

    std::string str(content);
    std::regex regex(R"(<rss.+version="(\d+.\d+)\")");
    std::smatch match;

    if (std::regex_search(str, match, regex))
    {
        version = std::stod(match.str(1));
    }

    return version;
}


