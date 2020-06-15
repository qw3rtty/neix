/**
 * TEST Helper function.
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
#include <cassert>

#include "helper/helper.h"

using namespace std;

int main()
{
    string text = "   \t\tHello World";
    assert(ltrim(text) == "Hello World");

    text = "Hello World\t\t\n    \t\n";
    assert(rtrim(text) == "Hello World");

    text = "   \t Hello World \t\v   ";
    assert(trim(text) == "Hello World");

    return 0;
}
