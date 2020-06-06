/**
 * TEST Config reader.
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
#include <cassert>

#include "config/ConfigFeedReader.h"

using namespace std;
using namespace crss;

int main()
{
    map<string, string> feedMap;
    ConfigFeedReader reader(FEED_CONFIG_PATH_TEST);

    feedMap = reader.read();
    assert(feedMap.size() == 1);

    return 0;
}
