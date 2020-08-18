/**
 * Config feed reader.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_CONFIGREADER_H
#define neix_CONFIGREADER_H

#include <vector>

using namespace std;
namespace neix
{
    class ConfigReader
    {
    public:
        ConfigReader(const char *configPath);
        ~ConfigReader();

         vector<pair<string, string>> read();

    protected:
        char *path;
    };
}

#endif //neix_CONFIGREADER_H
