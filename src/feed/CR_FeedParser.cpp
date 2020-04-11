/**
 * Feed parser class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <string>
#include <cstring>
#include <cassert>

#include "../include/rapidxml/rapidxml.hpp"
#include "feed/CR_FeedParser.h"

using namespace rapidxml;

/**
 * Constructor
 */
CR_FeedParser::CR_FeedParser()
{}


/**
 * Destructor
 */
CR_FeedParser::~CR_FeedParser()
{}


/**
 * Set raw rss content
 *
 * @param   {struct rawRss}     rawContent      - The loaded raw content
 */
void CR_FeedParser::setRawRss(struct rawRss rawContent)
{
    this->rss = &rawContent;
}


/**
 * Get an feed item of raw content
 *
 * @return  {struct rssItem*}    - Item of feed
 */
struct rssItem* CR_FeedParser::getFeedItem()
{
    struct rssItem *item = (struct rssItem*) malloc(sizeof(struct rssItem));
    item->title = (char*) malloc(sizeof(char) * 100);

    std::string s(this->rss->content);
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    char *test = const_cast<char *>(s.c_str());

    xml_document<> doc;
    doc.parse<0>(test);

    rapidxml::xml_node<>* rootNode = doc.first_node();
    rapidxml::xml_node<>* entryNode = rootNode->first_node("entry");

    strcpy(item->title, entryNode->first_node("title")->value());

    return item;
}