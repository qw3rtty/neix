/**
 * TEST TextConverter
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.3
 * @filesource
 */
#include <gtest/gtest.h>

#include "helper/TextConverter.h"

using namespace std;
using namespace neix;
namespace {
    TEST(TextConverter, instance)
    {
        try
        {
            TextConverter tc("Hello <b>World</b>");
            EXPECT_TRUE(true);
        }
        catch(...)
        {
            EXPECT_TRUE(false);
        }
    }
    
    TEST(TextConverter, stripHtml)
    {
        TextConverter hw("Hello <b>World</b>");
        string txt = hw.stripHtml();
        EXPECT_STREQ(txt.c_str(), "Hello World");

        TextConverter simple("Lorem <b>Ipsum</b> <a href='httsp://github.com'>dolor sit</a> amet.");
        txt = simple.stripHtml();
        EXPECT_STREQ(txt.c_str(), "Lorem Ipsum dolor sit amet.");

    }

    TEST(TextConverter, execCmd)
    {
        TextConverter tc("Hello <b>World</b> <p>Lorem ispum.</p>", "w3m -dump -T text/html");
        string txt = tc.execCmd();
        EXPECT_STREQ(txt.c_str(), "Hello World\n\nLorem ispum."); 
    }
}
