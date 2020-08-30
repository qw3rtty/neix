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
       throw "Could not found opml file to import!"; 
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
    configFile.open(configPath);
    if (!configFile.is_open())
    {
        return count; 
    }

    while (outline != 0)
    {
        xml_attribute<> *title = outline->first_attribute("title");
        xml_attribute<> *link = outline->first_attribute("xmlUrl");
   
        if (title && link)
        {
            configFile << title->value() << "=" << link->value() << endl;
            count++;
        } 

        outline = outline->next_sibling();
    }
    configFile.close();

    return count;
}


