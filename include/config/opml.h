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

#ifndef NEIX_OPML_H
#define NEIX_OPML_H

#include <string>
#include <vector>
#include "rapidxml/rapidxml.hpp"

using namespace std;
using namespace rapidxml;
namespace neix
{
    class opml 
    {
    public:
        opml();
        ~opml();

        void setList(vector<pair<string, string>> list);
        vector<pair<string, string>> getList();

        void create();
        string getContent();
        void exportFeeds(const string& path);

        static unsigned int import(const string& importPath, 
                const string& configPath);

    private:
        void _reset();
        void _addDeclarationNode();
        void _addOpmlBaseNode();
        void _addHeadNode();
        void _addFeedNodes();

        xml_document<> _doc;
        vector<pair<string, string>> _list;
    };
}

#endif //NEIX_OPML_H
