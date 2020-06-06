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

#ifndef CRSS_CONFIGFEEDREADER_H
#define CRSS_CONFIGFEEDREADER_H

#include <map>

namespace crss
{
    class ConfigFeedReader
    {
    public:
        ConfigFeedReader(const char *configPath);
        ~ConfigFeedReader();

         std::map<std::string, std::string> read();

    protected:
        char *path;
    };
}

#endif //CRSS_CONFIGFEEDREADER_H
