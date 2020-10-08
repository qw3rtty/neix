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
#include <cstring>
#include "rapidxml/rapidxml.hpp"
#include "parser/Parser.h"
#include "parser/ParserAtom.h"

using namespace rapidxml;
using namespace neix;

/**
 * Constructor
 */
ParserAtom::ParserAtom(struct rawRss content) : Parser(content)
{}


/**
 * Destructor
 */
ParserAtom::~ParserAtom() = default;


/**
 * Get correct date format of atom feeds
 *
 * @return  Date format string
 */
char* ParserAtom::getFeedDateFormat()
{
    return (char*) "%Y-%m-%dT%H:%M:%S";
}


/**
 * Get first feed node
 *
 * @return  First node
 */
xml_node<> * ParserAtom::getFirstNode()
{
   return this->rootNode->first_node("entry");
}


/**
 * Get title
 *
 * @return  The title
 */
char * ParserAtom::getFeedTitle()
{
    char *title = this->getNodeContent(this->entryNode->first_node("title"));
    return this->convertHtmlToPlaintext(title);
}


/**
 * Get content
 *
 * @return  The content
 */
char * ParserAtom::getFeedContent()
{
    char *content = this->getNodeContent(this->entryNode->first_node("summary"));
    if (strlen(content) == 0)
    {
        content = this->getNodeContent(this->entryNode->first_node("content"));
    }

    return content;
}


/**
 * Get link
 *
 * @return  The link
 */
char * ParserAtom::getFeedLink()
{
    char *url = nullptr;
    if (this->entryNode->first_node("link"))
    {
        url = this->getNodeAttribute(this->entryNode->first_node("link"), "href");
        url = strdup(url);
    }

    return url;
}


/**
 * Get date
 *
 * @return  The date
 */
char * ParserAtom::getFeedDate()
{
    char *date = this->getNodeContent(this->entryNode->first_node("updated"));
    return this->formatTimeString(date);
}

