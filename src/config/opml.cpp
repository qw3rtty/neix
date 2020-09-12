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

#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
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
 * Add the declaration node to the main document
 */
void opml::_addDeclarationNode()
{
    xml_node<>* decl = this->_doc.allocate_node(node_declaration);
    decl->append_attribute(this->_doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(this->_doc.allocate_attribute("encoding", "utf-8"));
    
    this->_doc.append_node(decl);
}


/**
 * Add the base OPML node to the main document
 */
void opml::_addOpmlBaseNode()
{
    xml_node<>* root = this->_doc.allocate_node(node_element, "opml");
    root->append_attribute(this->_doc.allocate_attribute("version", "2.0"));
    
    this->_doc.append_node(root);
}


/**
 * Add the head node to the main document
 */
void opml::_addHeadNode()
{
    xml_node<>* root = this->_doc.first_node("opml");
    xml_node<>* head = this->_doc.allocate_node(node_element, "head");
    
    xml_node<>* title = this->_doc.allocate_node(node_element, "title");
    title->value("neix - news reader for your terminal");
    head->append_node(title);

    // TODO: add created tag

    root->append_node(head);
}


/**
 * Add the feeds to the main document
 */
void opml::_addFeedNodes()
{
    xml_node<>* root = this->_doc.first_node("opml");
    xml_node<>* body = this->_doc.allocate_node(node_element, "body");

    if (this->_list.size() > 0)
    {
        for (auto & entry : this->_list)
	    {
            xml_node<>* outline = this->_doc.allocate_node(
                node_element, "outline");

            outline->append_attribute(this->_doc.allocate_attribute(
                "text", entry.first.c_str()));

            outline->append_attribute(this->_doc.allocate_attribute(
                "title", entry.first.c_str()));

            outline->append_attribute(this->_doc.allocate_attribute(
                "xmlUrl", entry.second.c_str()));

            outline->append_attribute(this->_doc.allocate_attribute(
                "type", "rss"));


            body->append_node(outline);    
	    }
 
    }

    root->append_node(body);
}


/**
 * Create the OPML document
 *
 * @throw
 */
void opml::create()
{
    this->_doc.clear();
    this->_addDeclarationNode();
    this->_addOpmlBaseNode();
    this->_addHeadNode();
    this->_addFeedNodes();
}


/**
 * Get document content
 *
 * @return  Document content
 */
string opml::getContent()
{
    string content;
    rapidxml::print(back_inserter(content), 
        this->_doc, print_no_indenting);

    return content;
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

    // TODO: export opml
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


