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

#ifndef NEIX_TEXTCONVERTER_H
#define NEIX_TEXTCONVERTER_H

#include <string>
#include "helper/TextConverter.h"

using namespace std;
namespace neix
{
    class TextConverter 
    {
    public:
        TextConverter(string t, string c = string(), int a_w = 0);
        ~TextConverter();

        string stripHtml();
        string execCmd();
        bool cmdExecuted;

    private:
        string text;
        string cmd;
        int article_width;
        string _buildFullRenderCommand(const string& rawFilePath, 
            const string& renderedFilePath);
        bool _prepareRawText(const string& rawFilePath, const string text);
        int _renderText(const string& command);
        string _getRenderedText(const string& filePath);
    };
}

#endif //NEIX_TEXTCONVERTER_H
