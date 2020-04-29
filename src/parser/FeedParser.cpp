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
#include <regex>

#include "rapidxml/rapidxml.hpp"
#include "parser/FeedParser.h"

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
    item->title = strdup(title);

    if (this->entryNode->first_node("summary"))
    {
        char *description = this->entryNode->first_node("summary")->value();
        item->description = this->convertHtmlToPlaintext(description);
    }

    if (this->entryNode->first_node("content"))
    {
        char *description = this->entryNode->first_node("content")->value();
        item->description = this->convertHtmlToPlaintext(description);
    }

    char *url = this->entryNode->first_node("link")->first_attribute("href")->value();
    item->url = strdup(url);

    char *date = this->entryNode->first_node("updated")->value();
    char *formattedDate = this->formatTimeString(date);
    item->date = strdup(formattedDate);

    return item;
}


/**
 * Convert given text to plaintext
 * > removes html tags
 *
 * @param   text    - The text which should be parsed
 * @return
 */
char * FeedParser::convertHtmlToPlaintext(char *text)
{
    char *plaintext;
    std::regex regex("<[^>]*>");
    std::string convertedText;

    convertedText = std::regex_replace(text, regex, "");
    plaintext = strdup(convertedText.c_str());

    return plaintext;
}


/**
 * Format given times string to configured format
 *
 * @param   timeString
 * @return  Formatted time string
 */
char* FeedParser::formatTimeString(const char *timeString)
{
    char *tmpTimeString = strdup(timeString);
    std::stringstream date(tmpTimeString);
    std::ostringstream formattedTimeString;
    struct std::tm when;

    date >> std::get_time(&when,"%Y-%m-%dT%H:%M:%S+%Z");
    formattedTimeString << std::put_time(&when, "%d.%m.%Y %H:%M"); // TODO: get format from config

    char *formattedDate = strdup(formattedTimeString.str().c_str());
    return formattedDate;
}