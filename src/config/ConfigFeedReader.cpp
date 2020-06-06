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

#include <string.h>
#include <iostream>
#include <map>
#include <fstream>
#include "config/ConfigFeedReader.h"

using namespace crss;

/**
 * Constructor
 */
ConfigFeedReader::ConfigFeedReader(const char *configPath)
{
    this->path = strdup(configPath);
}


/**
 * Destructor
 */
ConfigFeedReader::~ConfigFeedReader() = default;

/**
 * Read given feed config file
 *
 * @return  Map with entries of configuration file
 */
std::map<std::string, std::string> ConfigFeedReader::read()
{
    std::map<std::string, std::string> feedMap;
    std::ifstream file;
    std::string line;

    std::string delimiter = "=";
    std::string name;
    std::string link;

    file.open(this->path);
    if (!file.is_open())
    {
        throw "Configuration file for feeds not found!";
    }

    while (!file.eof())
    {
        getline(file, line);
        name = line.substr(0, line.find(delimiter));
        link = line.substr(line.find(delimiter) + 1, line.length());

        if (name.empty() || link.empty())
        {
            continue;
        }

        std::pair<std::string, std::string> pair = std::pair<std::string, std::string>(name.c_str(), link.c_str());
        feedMap.insert(pair);
    }
    file.close();

    return feedMap;
}