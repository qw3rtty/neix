/**
 * RSS 2.0 parser class.
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
#include "parser/ParserRSS2.h"

using namespace rapidxml;
using namespace crss;

/**
 * Constructor
 */
ParserRSS2::ParserRSS2(struct rawRss content) : Parser(content)
{}


/**
 * Destructor
 */
ParserRSS2::~ParserRSS2() = default;


/**
 * Get correct date format of atom feeds
 *
 * @return  Date format string
 */
char* ParserRSS2::getFeedDateFormat()
{
    return (char*) "%a, %d %b %Y %H:%M:%S %z";
}


/**
 * Get an feed item of raw content
 *
 * @return  Item of feed
 */
struct rssItem* ParserRSS2::getFeedItem()
{
    struct rssItem *item = (struct rssItem*) calloc(1, sizeof(struct rssItem));
    item->read = 0;

    if (this->rootNode == nullptr)
    {
        return item;
    }

    if (this->entryNode == nullptr)
    {
        this->entryNode = this->rootNode->first_node("channel")->first_node("item");
    }
    else
    {
        this->entryNode = this->entryNode->next_sibling();
    }

    // Get feed title
    item->title = this->getNodeContent(this->entryNode->first_node("title"));
    item->title = this->convertHtmlToPlaintext(item->title);

    // Get feed content
    item->description = this->getNodeContent(this->entryNode->first_node("description"));
    item->description = this->convertHtmlToPlaintext(item->description);

    // Get feed link
    if (this->entryNode->first_node("link"))
    {
        item->url = this->getNodeContent(this->entryNode->first_node("link"));
    }

    // Get feed date
    item->date = this->getNodeContent(this->entryNode->first_node("pubDate"));
    item->date = this->formatTimeString(item->date);

    return item;
}
