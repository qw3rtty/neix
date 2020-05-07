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
Parser::Parser(struct rawRss content)
{
   this->setRawRss(content);
}


/**
 * Destructor
 */
Parser::~Parser() = default;


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
 * Get the attribute content of given node
 *
 * @param   node        - Node of which the attribute should be get
 * @param   attribute   - Name of the attribute
 * @return              - Content of the attribute
 */
char * Parser::getNodeAttribute(xml_node<> *node, const char *attribute)
{
    char *attributeValue = nullptr;
    if (node == nullptr)
    {
        return attributeValue;
    }

    xml_attribute<> *nodeAttr = node->first_attribute(attribute);
    if (nodeAttr == nullptr)
    {
        return attributeValue;
    }

    attributeValue = nodeAttr->value();
    return attributeValue;
}


/**
 * Get content of given node
 *
 * @param   node        - The node of which the content should get
 * @return
 */
char * Parser::getNodeContent(xml_node<> *node)
{
    char *nodeValue = nullptr;
    char *content = (char*) calloc(1, sizeof(char));
    strcpy(content, "");

    if (node == nullptr)
    {
        return content;
    }

    char *attr = this->getNodeAttribute(node, "type");
    if (attr != nullptr && strcmp(attr, "html") == 0)
    {
        node = node->first_node();
    }

    if (node != nullptr)
    {
        nodeValue = node->value();
        content = (char*) calloc(strlen(nodeValue), sizeof(char));
        strcpy(content, nodeValue);
    }

    return content;
}


/**
 * Get an feed item of raw content
 *
 * @return  Item of feed
 */
struct rssItem* Parser::getFeedItem()
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
    formattedTimeString << std::put_time(&when, "%d.%m.%Y %H:%M"); // TODO: getFeed format from config

    std::string tmp(formattedTimeString.str());
    char *formattedDate = strdup(tmp.c_str());

    return formattedDate;
}