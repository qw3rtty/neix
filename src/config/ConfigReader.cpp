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
#include "config.h"
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
	this->list.clear();
}


/**
 * Destructor
 */
ConfigReader::~ConfigReader() = default;

/**
 * Parse config file
 */
void ConfigReader::parse()
{
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
		if (line.rfind('#', 0) == 0)
		{
			continue;	
		}

        name = line.substr(0, line.find(delimiter));
		name = trim(name);

        link = line.substr(line.find(delimiter) + 1, line.length());
        link = trim(link);

        if (!name.empty() && !link.empty())
        {
            pair<string, string> pair = make_pair(name, link);
            this->list.push_back(pair);
        }
    }
    file.close();
}

/**
 * Get the count of parsed entries
 */
int ConfigReader::count()
{
	return this->list.size();
}

/**
 * Check if entry exists in parsed config
 * 
 * @param	Entry name which should be checked
 * @return
 */
bool ConfigReader::hasEntry(const char* entryName)
{
	bool entryExists = false;
	for (auto & entry : this->list)
	{
		if (strcmp(entry.first.c_str(), entryName) == 0)
		{
			entryExists = true;	
		}	
	}
	return entryExists;
}

/**
 * Get entry by given name
 *
 * @param	Name of the entry which should be returned
 * @return
 */
string ConfigReader::getEntryByName(const char* entryName)
{
	string value;
	for (auto & entry : this->list)
	{
		if (strcmp(entry.first.c_str(), entryName) == 0)
		{
			value = entry.second;
		}	
	}
	return value;
}

/**
 * Get entry list
 *
 * @return
 */
vector<pair<string, string>> ConfigReader::getList()
{
	return this->list;
}


/**
 * Get config by given path
 *
 * @param   path    - Path where the config file is located
 * @return
 */
ConfigReader ConfigReader::create(const char *path)
{
	ConfigReader reader(path);
    try {
    	reader.parse();
    } catch (const char *msg) {
        cout << prefix << "Failed to load: " << path << endl;
        cout << prefix <<  msg << endl;
        exit(0);
    }

    return reader;
}
