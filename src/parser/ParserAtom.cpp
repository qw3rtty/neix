/**
 * Atom parser class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>

#include "rapidxml/rapidxml.hpp"
#include "parser/Parser.h"
#include "parser/ParserAtom.h"

using namespace rapidxml;
using namespace crss;

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
 * Get an feed item of raw content
 *
 * @return  Item of feed
 */
struct rssItem* ParserAtom::getFeedItem()
{
    struct rssItem *item = (struct rssItem*) calloc(1, sizeof(struct rssItem));
    item->read = 0;

    if (this->rootNode == nullptr)
    {
        return item;
    }

    if (this->entryNode == nullptr)
    {
        this->entryNode = this->rootNode->first_node("entry");
    }
    else
    {
        this->entryNode = this->entryNode->next_sibling();
    }

    // Get feed title
    item->title = this->getNodeContent(this->entryNode->first_node("title"));
    item->title = this->convertHtmlToPlaintext(item->title);

    // Get feed content
    item->description = this->getNodeContent(this->entryNode->first_node("summary"));
    if (strlen(item->description) == 0)
    {
        item->description = this->getNodeContent(this->entryNode->first_node("content"));
    }
    item->description = this->convertHtmlToPlaintext(item->description);

    // Get feed link
    if (this->entryNode->first_node("link"))
    {
        char *url = this->getNodeAttribute(this->entryNode->first_node("link"), "href");
        item->url = strdup(url);
    }

    // Get feed date
    item->date = this->getNodeContent(this->entryNode->first_node("updated"));
    item->date = this->formatTimeString(item->date);

    return item;
}
