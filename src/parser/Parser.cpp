/**
 * Feed parser class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <regex>

#include "rapidxml/rapidxml.hpp"
#include "parser/Parser.h"
#include "helper/helper.h"

using namespace rapidxml;
using namespace std;
using namespace neix;

/**
 * Constructor
 */
Parser::Parser(struct rawRss content)
{
    this->loadXml(content);
    this->timeFormatUI = nullptr;
    this->renderCommand = nullptr;
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
void Parser::loadXml(struct rawRss rawContent)
{
    const int parseFlags = parse_trim_whitespace;
    this->xmlDocument.parse<parseFlags>(rawContent.content);
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
char *Parser::getNodeAttribute(xml_node<> *node, const char *attribute)
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
char *Parser::getNodeContent(xml_node<> *node)
{
    char *nodeValue = nullptr;
    char *content = (char *) calloc(1, sizeof(char));
    strcpy(content, "");

    if (node == nullptr)
    {
        return content;
    }

    char *attr = this->getNodeAttribute(node, "type");
    if ((attr != nullptr && strcmp(attr, "html") == 0) || node->first_node())
    {
        node = node->first_node();
    }

    if (node != nullptr)
    {
        nodeValue = node->value();
        content = (char *) calloc(strlen(nodeValue) + 1, sizeof(char));
        strcpy(content, nodeValue);
    }

    return content;
}


/**
 * Get next feed node
 *
 * @return  Next node
 */
xml_node<> *Parser::getNextNode()
{
    xml_node<> *node = nullptr;

    if (this->rootNode == nullptr)
    {
        return node;
    }

    if (this->rootNode != nullptr && this->entryNode == nullptr)
    {
        node = this->getFirstNode();
    }
    else
    {
        node = this->entryNode->next_sibling();
    }

    return this->entryNode = node;
}


/**
 * Get an feed item of raw content
 *
 * @return  Item of feed
 */
struct rssItem *Parser::getFeedItem()
{
    if (this->getNextNode() == nullptr)
    {
        return nullptr;
    }

    struct rssItem *item = (struct rssItem *) calloc(1, sizeof(struct rssItem));
    item->read = 0;
    item->title = this->getFeedTitle();
    item->description = this->getFeedContent();
    item->url = this->getFeedLink();
    item->date = this->getFeedDate();

    return item;
}


/**
 * Convert given text to plaintext
 * > removes html tags
 *
 * @param   text    - The text which should be parsed
 * @return
 */
char *Parser::convertHtmlToPlaintext(const char *text)
{
    char *plaintext;
    regex regex("<[^>]*>");
    string convertedText;

    convertedText = regex_replace(text, regex, "");
    convertedText = trim(convertedText);
    plaintext = strdup(convertedText.c_str());

    return plaintext;
}


/**
 * Render given text to plaintext
 *
 * @param   text    - Text which should be rendered into plaintext
 * @return
 */
char * Parser::renderTextToPlaintext(const char *text)
{
    if (this->renderCommand == nullptr)
    {
        return this->convertHtmlToPlaintext(text);
    }

    string homePath = getenv("HOME");
    string rawFilePath = homePath + "/.config/neix/tmp-raw.txt";
    string renderedFilePath = homePath + "/.config/neix/tmp-rendered.txt";

    this->prepareRawText(rawFilePath, text);
    string renderCmd = this->buildFullRenderCommand(rawFilePath, renderedFilePath);
    this->renderText(renderCmd);

    string renderedText = this->getRenderedText(renderedFilePath);
    return strdup(renderedText.c_str());
}


/**
 * Build render command for system call
 *
 * @param   rawFilePath         - Path to the file which should contain the raw text
 * @param   renderedFilePath    - Path to the file for the rendered text
 * @return
 */
string Parser::buildFullRenderCommand(const string& rawFilePath, const string& renderedFilePath)
{
    string renderCmd = this->renderCommand;
    renderCmd += " ";
    renderCmd += rawFilePath;
    renderCmd += " > ";
    renderCmd += renderedFilePath;

    return renderCmd;
}


/**
 * Prepares the raw text file
 *
 * @param   rawFilePath     - Path to the file which should contain the raw text
 * @param   text            - Text to write into file
 * @return
 */
bool Parser::prepareRawText(const string& rawFilePath, const char *text)
{
    bool success = false;
    ofstream rawFile;
    rawFile.open(rawFilePath);
    if (rawFile.is_open())
    {
        rawFile << text;
        rawFile.close();
        success = true;
    }
    return success;
}


/**
 * Execute the system command
 *
 * @param   command     - Command which should be executed
 * @return
 */
int Parser::renderText(const string& command)
{
    return system(command.c_str());
}


/**
 * Get rendered text
 *
 * @param   filePath    - Path to the file which contains the rendered text
 * @return
 */
string Parser::getRenderedText(const string& filePath)
{
    string renderedText;
    string line;

    ifstream renderedFile(filePath);
    if (renderedFile.is_open())
    {
        while ( getline (renderedFile,line) )
        {
            renderedText += line;
            renderedText += "\n";
        }
        renderedFile.close();
    }

    return trim(renderedText);
}

/**
 * Format given times string to configured format
 *
 * @param   timeString
 * @return  Formatted time string
 */
char *Parser::formatTimeString(const char *timeString)
{
    stringstream date(timeString);
    ostringstream formattedTimeString;
    struct tm when{0};
    memset(&when, 0, sizeof(when));

    date >> get_time(&when, this->getFeedDateFormat());
    formattedTimeString << put_time(&when, this->getTimeFormatUI());

    string tmp(formattedTimeString.str());
    tmp = trim(tmp);
    char *formattedDate = strdup(tmp.c_str());

    return formattedDate;
}


/**
 * Get time format
 *
 * @return  Time format
 */
char *Parser::getTimeFormatUI()
{
    return this->timeFormatUI;
}


/**
 * Set time format
 *
 * @param   format  - String which represents the time format
 */
void Parser::setTimeFormatUI(const char *format)
{
    if (format != nullptr)
    {
        this->timeFormatUI = strdup(format);
    }
}

/**
 * Set the render command
 *
 * @param   command     - String which contains the system command for rendering an text
 */
void Parser::setRenderCommand(const char *command)
{
    if (command != nullptr)
    {
        this->renderCommand = strdup(command);
    }
}
