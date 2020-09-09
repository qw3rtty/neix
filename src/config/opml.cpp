/**
 * OPML import/export.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     GPL-3.0
 * @since       Version 0.1.2
 * @filesource
 */

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

#include "rapidxml/rapidxml.hpp"
#include "config.h"
#include "config/opml.h"

using namespace std;
using namespace rapidxml;
using namespace neix;


/**
 * Constructor
 */
opml::opml() = default;


/**
 * Destructor
 */
opml::~opml() = default;


/**
 * Reset 
 */
void opml::_reset()
{
    this->_list.clear();
}


/**
 * Set list
 *
 * @param   list    - List to set
 */
void opml::setList(vector<pair<string, string>> list)
{
    this->_reset();
    this->_list = list;
}


/**
 * Get list
 */
vector<pair<string, string>> opml::getList()
{
    return this->_list;
}


/**
 * Create the OPML document
 *
 * @throw
 */
void opml::create()
{
    // TODO: create XML document
}


/**
 * Export OPML to file
 * > location given
 *
 * @param   path    - Path to export
 * @throw   invalid_argument 
 */
void opml::exportFeeds(const string& path)
{
    if (path.empty())
    {
        throw invalid_argument("No path given!");
    }

    // TODO: export
}

/**
 * Import OPML file which contains feeds
 * > new feeds will be append 
 *
 * @param   importPath      - Path to the OPML file which should be imported
 * @param   configPath      - Path to the config file
 * @return  The count of imported feeds
 */
unsigned int opml::import(const string& importPath, const string& configPath)
{
    // TODO: cleanup mess!!
    unsigned int count = 0;
    if (importPath.empty())
    {
        return count; 
    }

    ifstream file;
    file.open(importPath);
    if (!file.is_open())
    {
        return count;
    }

    string line;
    string content;
    while (!file.eof())
    {
        getline(file, line); 
        content += line + '\n';
    }
    file.close();

    xml_document<> doc;
    doc.parse<0>((char*)content.c_str());
    xml_node<> *opml = doc.first_node("opml");
    xml_node<> *body = opml->first_node("body");
    xml_node<> *outline = body->first_node("outline");
  
    ofstream configFile; 
    configFile.open(configPath, ios_base::app);
    if (!configFile.is_open())
    {
        return count; 
    }

    while (outline != 0)
    {
        xml_attribute<> *type = outline->first_attribute("type");
        if (type && (strcmp(type->value(), "rss") == 0 || 
                    strcmp(type->value(), "atom") == 0))
        {
            xml_attribute<> *title = outline->first_attribute("title");
            xml_attribute<> *link = outline->first_attribute("xmlUrl");
       
            if (title && link)
            {
                configFile << title->value() << "=" << link->value() << endl;
                count++;
            } 
        }
        
        outline = outline->next_sibling();
    }
    configFile.close();

    return count;
}


