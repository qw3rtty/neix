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
#include "rapidxml/rapidxml.hpp"
#include "parser/Parser.h"
#include "parser/ParserRSS.h"

using namespace rapidxml;
using namespace neix;

/**
 * Constructor
 */
ParserRSS::ParserRSS(struct rawRss content) : Parser(content)
{}


/**
 * Destructor
 */
ParserRSS::~ParserRSS() = default;


/**
 * Get correct date format of atom feeds
 *
 * @return  Date format string
 */
char* ParserRSS::getFeedDateFormat()
{
    return (char*) "%a, %d %b %Y %H:%M:%S %z";
}

/**
 * Get first feed node
 *
 * @return  First node
 */
xml_node<> * ParserRSS::getFirstNode()
{
    return this->rootNode->first_node("channel")->first_node("item");
}


/**
 * Get title
 *
 * @return  The title
 */
char * ParserRSS::getFeedTitle()
{
    char *title = this->getNodeContent(this->entryNode->first_node("title"));
    return this->convertHtmlToPlaintext(title);
}


/**
 * Get content
 *
 * @return  The content
 */
char * ParserRSS::getFeedContent()
{
    return this->getNodeContent(this->entryNode->first_node("description"));
}


/**
 * Get link
 *
 * @return  The link
 */
char * ParserRSS::getFeedLink()
{
    char *url = nullptr;
    if (this->entryNode->first_node("link"))
    {
        url = this->getNodeContent(this->entryNode->first_node("link"));
    }

    return url;
}


/**
 * Get date
 *
 * @return  The date
 */
char * ParserRSS::getFeedDate()
{
    char *date = this->getNodeContent(this->entryNode->first_node("pubDate"));
    return this->formatTimeString(date);
}

