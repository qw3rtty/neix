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

#ifndef neix_CONFIGREADER_H
#define neix_CONFIGREADER_H

#include <vector>

using namespace std;
namespace neix
{
    class ConfigReader
    {
    public:
        ConfigReader(const char* configPath);
        ~ConfigReader();

		void parse();
		int count();
       	bool hasEntry(const char* entryName);
	   	string getEntryByName(const char* entryName);
		vector<pair<string, string>> getList();
		static ConfigReader create(const char* path);

    protected:
        char *path;
		vector<pair<string, string>> list;
    };
}

#endif //neix_CONFIGREADER_H
