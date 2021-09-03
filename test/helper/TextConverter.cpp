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
       
        string expected = "Hello World\n\nLorem ispum.";  
        if (!tc.cmdExecuted)
        {
            expected = "Hello World Lorem ispum."; 
        }
        EXPECT_STREQ(txt.c_str(), expected.c_str());

        TextConverter tcon("Hello <b>World</b> again.");
        txt = tcon.execCmd();
        EXPECT_STREQ(txt.c_str(), "Hello World again."); 
    }

    TEST(TextConverter, execCmd_article_width)
    {
        TextConverter tc("Unused", "f() { echo \"The article width is $article_width\" } && f", 3);
        string txt = tc.execCmd();
       
        string expected = "The article width is 3";
        if (!tc.cmdExecuted)
        {
            expected = "Unused"; 
        }
        EXPECT_STREQ(txt.c_str(), expected.c_str());
        
        TextConverter tc2("Unused", "f() { echo \"The article width is $article_width\" } && f");
        string txt2 = tc2.execCmd();
       
        string expected2 = "The article width is 0";
        if (!tc2.cmdExecuted)
        {
            expected2 = "Unused"; 
        }
        EXPECT_STREQ(txt2.c_str(), expected2.c_str());

        TextConverter tcon("Hello <b>World</b> again.");
        txt = tcon.execCmd();
        EXPECT_STREQ(txt.c_str(), "Hello World again.");
    }
}
