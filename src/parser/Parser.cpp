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
#include "parser/Parser.h"

using namespace rapidxml;
using namespace crss;

/**
 * Constructor
 */
Parser::Parser()
{}


/**
 * Destructor
 */
Parser::~Parser()
{}


/**
 * Set raw rss content
 *
 * @param rawContent    - The loaded raw content
 */
void Parser::setRawRss(struct rawRss rawContent)
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
struct rssItem* Parser::getFeedItem()
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
    char *tmp = this->formatTimeString(date);
    item->date = strdup(tmp);

    return item;
}


/**
 * Convert given text to plaintext
 * > removes html tags
 *
 * @param   text    - The text which should be parsed
 * @return
 */
char * Parser::convertHtmlToPlaintext(char *text)
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
char* Parser::formatTimeString(const char *timeString)
{
    std::stringstream date(timeString);
    std::ostringstream formattedTimeString;
    struct std::tm when{0};
    memset(&when, 0, sizeof(when));

    date >> std::get_time(&when,"%Y-%m-%dT%H:%M:%S");
    formattedTimeString << std::put_time(&when, "%d.%m.%Y %H:%M"); // TODO: get format from config

    std::string tmp(formattedTimeString.str());
    char *formattedDate = strdup(tmp.c_str());

    return formattedDate;
}