/**
 * Helper functions.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "helper/helper.h"

using namespace std;

string ltrim(const string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s)
{
    return rtrim(ltrim(s));
}

/**
 * Cut string after x characters and add ending '...'
 *
 * @param s
 * @param length
 * @return
 */
string subStrWithEndingDots(const string& s, const unsigned int length)
{
    string tmp = s;
    if (s.length() > length)
    {
        tmp = s.substr(0, length-3);
        tmp += "...";
    }

    return tmp;
}

/**
 * Get the config home path of neix 
 * > from current executing user
 *
 * @return  path
 */
string getConfigHomePath()
{
    string path = getenv("HOME");
    path += "/.config/neix/";

    return path;
}

/**
 * Get the config path of the home path of neix if the name is not an absolute file path
 * > from executing user
 *
 * @return  path
 */
string getConfigPathByName(const string& name)
{
    if (name.at(0) == '/') {
        // we consider the name as the full file path
        return name;
    }
    string path = getConfigHomePath();
    path += name;

    return path;
}


/**
 * Get the main config path of neix 
 * > from current executing user
 *
 * @return  path
 */
string getMainConfigPath()
{
    return getConfigPathByName("neix.conf");
}

/**
 * Get the feed config path of neix 
 * > from current executing user
 *
 * @return  path
 */
string getFeedConfigPath(string configName)
{
    if (configName.empty()) {
       configName = "feeds.conf"; 
    }
    return getConfigPathByName(configName);
}

/**
 * Check's if config files exists
 *
 * @return true if they exists, false else
 */
bool configFilesExists()
{
    ifstream mainConfig(getMainConfigPath().c_str());
    ifstream feedConfig(getFeedConfigPath().c_str());

    return mainConfig.good() && feedConfig.good();
}

/**
 * Copy default config files to 'neix' home config directory
 */
bool copyDefaultConfigFiles()
{
    // Copy main config
    std::ifstream defaultMainConfig(DEFAULT_MAIN_CONFIG, std::ios::binary);
    std::ofstream mainConfig(getMainConfigPath().c_str(), std::ios::binary);

    mainConfig << defaultMainConfig.rdbuf(); 
    defaultMainConfig.close();
    mainConfig.close();

    // Copy feeds config
    std::ifstream defaultFeedsConfig(DEFAULT_FEEDS_CONFIG, std::ios::binary);
    std::ofstream feedsConfig(getFeedConfigPath().c_str(), std::ios::binary);

    feedsConfig << defaultFeedsConfig.rdbuf(); 
    defaultFeedsConfig.close();
    feedsConfig.close();

    return true;
}
