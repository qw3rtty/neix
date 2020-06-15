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
#include "helper/helper.h"
#include "config/ConfigReader.h"

using namespace std;
using namespace crss;

/**
 * Constructor
 */
ConfigReader::ConfigReader(const char *configPath)
{
    this->path = strdup(configPath);
}


/**
 * Destructor
 */
ConfigReader::~ConfigReader() = default;

/**
 * Read given feed config file
 *
 * @return  Map with entries of configuration file
 */
map<string, string> ConfigReader::read()
{
    map<string, string> feedMap;
    ifstream file;
    string line, name, link, delimiter = "=";

    file.open(this->path);
    if (!file.is_open())
    {
        throw "Configuration file not found!";
    }

    while (!file.eof())
    {
        getline(file, line);
		if (line.rfind("#", 0) == 0)
		{
			continue;	
		}

        name = line.substr(0, line.find(delimiter));
		name = trim(name);

        link = line.substr(line.find(delimiter) + 1, line.length());
        link = trim(link);

        if (name.empty() || link.empty())
        {
            continue;
        }

        feedMap[name] = link;
    }
    file.close();

    return feedMap;
}
