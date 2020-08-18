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

#include <cstring>
#include <iostream>
#include <map>
#include <fstream>
#include "helper/helper.h"
#include "config/ConfigReader.h"

using namespace std;
using namespace neix;

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
 * @return  Vector with entries of configuration file
 */
vector<pair<string, string>> ConfigReader::read()
{
    vector<pair<string, string>> feedList;
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

        pair<string, string> pair = make_pair(name, link);
        feedList.push_back(pair);
    }
    file.close();

    return feedList;
}
