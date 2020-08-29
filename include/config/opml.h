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

using namespace std;
namespace neix
{
    class opml 
    {
    public:
        opml();
        ~opml();

        static bool import(const string& importPath, const string& configPath);
    };
}

#endif //NEIX_OPML_H
