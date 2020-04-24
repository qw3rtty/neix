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

#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

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
 * @param rawContent    - The loaded raw content
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
 * @return  Item of feed
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

    char *url = this->entryNode->first_node("link")->first_attribute("href")->value();
    item->url = (char*) malloc(sizeof(char) * strlen(url) + 1);
    strcpy(item->url, url);

    char *date = this->entryNode->first_node("updated")->value();
    item->date = (char*) malloc(sizeof(char) * strlen(date) + 1);
    strcpy(item->date, this->formatTimeString(date));

    return item;
}


/**
 * Format given times string to configured format
 *
 * @param   timeString
 * @return  Formatted time string
 */
char* FeedParser::formatTimeString(char *timeString)
{
    char *tmpTimeString = strdup(timeString);
    std::stringstream date(tmpTimeString);
    std::ostringstream formattedTimeString;
    struct std::tm when;

    date >> std::get_time(&when,"%Y-%m-%dT%H:%M:%S+%Z");
    formattedTimeString << std::put_time(&when, "%d.%m.%Y %H:%M"); // TODO: get format from config

    char *formattedDate = (char*) malloc(sizeof(char) * formattedTimeString.str().length());
    strcpy(formattedDate, formattedTimeString.str().c_str());

    return formattedDate;
}