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

#ifndef neix_HELPER_H
#define neix_HELPER_H

#include <string>
using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string& s);
string rtrim(const string& s);
string trim(const string& s);

string subStrWithEndingDots(const string& s, const unsigned int length);

// TODO: Put these functions to ConfigReader as static methods
string getConfigHomePath();
string getConfigPathByName(const string& name);
string getMainConfigPath();
string getFeedConfigPath();
bool configFilesExists();
bool copyDefaultConfigFiles();

#endif //neix_HELPER_H
