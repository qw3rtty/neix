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

#include <cstring>
#include <cassert>
#include <algorithm>

#include "../include/rapidxml/rapidxml.hpp"
#include "feed/FeedParser.h"

using namespace rapidxml;
using namespace crss;

/**
 * Constructor
 */
FeedParser::FeedParser()
{}


/**
 * Destructor
 */
FeedParser::~FeedParser()
{}


/**
 * Set raw rss content
 *
 * @param   {struct rawRss}     rawContent      - The loaded raw content
 */
void FeedParser::setRawRss(struct rawRss rawContent)
{
    this->rss = &rawContent;

    std::string s(this->rss->content);
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    char *temp = const_cast<char *>(s.c_str());

    this->xmlDocument.parse<0>(temp);
    this->rootNode = this->xmlDocument.first_node();
    this->entryNode = nullptr;
}


/**
 * Get an feed item of raw content
 *
 * @return  {struct rssItem*}    - Item of feed
 */
struct rssItem* FeedParser::getFeedItem()
{
    struct rssItem *item = (struct rssItem*) malloc(sizeof(struct rssItem));
    item->read = 0;
    if (this->entryNode == nullptr)
    {
        this->entryNode = this->rootNode->first_node("entry");
    }
    else
    {
        this->entryNode = this->entryNode->next_sibling();
    }

    char *title = this->entryNode->first_node("title")->value();
    item->title = (char*) malloc(sizeof(char) * strlen(title) + 1);
    strcpy(item->title, title);

    if (this->entryNode->first_node("content"))
    {
        char *description = this->entryNode->first_node("content")->value();
        item->description = (char*) malloc(sizeof(char) * strlen(description) + 1);
        strcpy(item->description, description);
    }

    char *date = this->entryNode->first_node("updated")->value();
    item->date = (char*) malloc(sizeof(char) * strlen(date) + 1);
    strcpy(item->date, date);

    char *url = this->entryNode->first_node("link")->first_attribute("href")->value();
    item->url = (char*) malloc(sizeof(char) * strlen(url) + 1);
    strcpy(item->url, url);

    return item;
}