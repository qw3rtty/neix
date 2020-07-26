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

#include <regex>
#include <string>

#include "parser/Parser.h"
#include "parser/ParserAtom.h"
#include "parser/ParserRSS.h"
#include "parser/FactoryParser.h"

using namespace std;
using namespace neix;

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
		parser = new ParserRSS(content);
	}
	else if (version == 0.91 || version == 0.92)
	{
		parser = new ParserRSS(content);
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

    string str(content);
    regex regex(R"(<rss.+version="(\d+.\d+)\")");
    smatch match;

    if (regex_search(str, match, regex))
    {
        version = stod(match.str(1));
    }

    return version;
}


