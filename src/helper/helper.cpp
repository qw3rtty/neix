/**
 * Helper functions.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <iostream>
#include <string>
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