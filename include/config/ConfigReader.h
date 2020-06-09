/**
 * Config feed reader.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef CRSS_CONFIGREADER_H
#define CRSS_CONFIGREADER_H

#include <map>

using namespace std;
namespace crss
{
    class ConfigReader
    {
    public:
        ConfigReader(const char *configPath);
        ~ConfigReader();

         map<string, string> read();

    protected:
        char *path;
    };
}

#endif //CRSS_CONFIGREADER_H
