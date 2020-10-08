/**
 * TextConverter class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.3
 * @filesource
 */
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#include "helper/helper.h"
#include "helper/TextConverter.h"

using namespace std;
using namespace neix;

/**
 * Constructor
 */
TextConverter::TextConverter(string t, string c)
{
    this->text = move(t);
    this->cmd = move(c);
}


/**
 * Destructor
 */
TextConverter::~TextConverter() = default;


/**
 * Strip HTML tags
 */
string TextConverter::stripHtml()
{
    regex regex("<[^>]*>");
    string convertedText;

    convertedText = regex_replace(text, regex, "");
    convertedText = trim(convertedText);

    return convertedText;
}


/**
 * Executes command
 */
string TextConverter::execCmd()
{
    if (this->cmd.empty())
    {
        return this->stripHtml(); 
    }

    string homePath = getenv("HOME");
    string rawFilePath = homePath + "/.config/neix/tmp-raw.txt";
    string renderedFilePath = homePath + "/.config/neix/tmp-rendered.txt";

    this->_prepareRawText(rawFilePath, this->text);
    string renderCmd = this->_buildFullRenderCommand(rawFilePath, 
        renderedFilePath);
    this->_renderText(renderCmd);

    return this->_getRenderedText(renderedFilePath);
}


/**
 * Build render command for system call
 *
 * @param   rawFilePath         - Path to the file which should contain the raw text
 * @param   renderedFilePath    - Path to the file for the rendered text
 * @return
 */
string TextConverter::_buildFullRenderCommand(const string& rawFilePath, 
    const string& renderedFilePath)
{
    string renderCmd = this->cmd;
    renderCmd += " ";
    renderCmd += rawFilePath;
    renderCmd += " > ";
    renderCmd += renderedFilePath;

    return renderCmd;
}


/**
 * Prepares the raw text file
 *
 * @param   rawFilePath     - Path to the file which should contain the raw text
 * @param   text            - Text to write into file
 * @return
 */
bool TextConverter::_prepareRawText(const string& rawFilePath, const string text)
{
    bool success = false;
    ofstream rawFile;
    rawFile.open(rawFilePath);
    if (rawFile.is_open())
    {
        rawFile << text;
        rawFile.close();
        success = true;
    }
    return success;
}


/**
 * Execute the system command
 *
 * @param   command     - Command which should be executed
 * @return
 */
int TextConverter::_renderText(const string& command)
{
    return system(command.c_str());
}


/**
 * Get rendered text
 *
 * @param   filePath    - Path to the file which contains the rendered text
 * @return
 */
string TextConverter::_getRenderedText(const string& filePath)
{
    string renderedText;
    string line;

    ifstream renderedFile(filePath);
    if (renderedFile.is_open())
    {
        while ( getline (renderedFile,line) )
        {
            renderedText += line;
            renderedText += "\n";
        }
        renderedFile.close();
    }

    return trim(renderedText);
}
