/**
 * Feed loader class.
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
#include <fstream>
#include <sstream>
#include <utility>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>

#include "feed/FeedLoader.h"
using namespace cr;

struct rss *feeds[FEEDS_MAX];
int feeds_count = 0;


/**
 * Constructor
 */
FeedLoader::FeedLoader()
{
    this->url = "";
    this->resetFeed();
}


/**
 * Destructor
 */
FeedLoader::~FeedLoader()
{
    free(this->feed);
}


/**
 * Reset feet
 */
void FeedLoader::resetFeed()
{
    this->feed = (struct rawRss*) malloc(sizeof(struct rawRss*));
    this->feed->content = (char*) malloc(sizeof(char));
    this->feed->size = 0;
}


/**
 * Load feeds from config file
 */
bool FeedLoader::loadFeedsFromConfig()
{
    std::ifstream file;
    std::string line;

    std::string delimiter = "=";
    std::string name;
    std::string link;

    std::stringstream path;
    path << getenv("HOME") << "/.config/crss/feeds.conf";

    file.open(path.str());
    if (!file.is_open())
    {
        std::cout << "Could not load config file!" << std::endl;
        return false;
    }

    while (!file.eof())
    {
        getline(file, line);
        name = line.substr(0, line.find(delimiter));
        link = line.substr(line.find(delimiter) + 1, line.length());

        if (name.empty() || link.empty())
        {
            continue;
        }

        feeds[feeds_count] = (struct rss*) malloc(sizeof(struct rss));
        feeds[feeds_count]->title = (char*) malloc(sizeof(char) * name.length());
        feeds[feeds_count]->url = (char*) malloc(sizeof(char) * link.length());

        strcpy(feeds[feeds_count]->title, name.c_str());
        strcpy(feeds[feeds_count]->url, link.c_str());

        feeds_count++;
    }
    file.close();

    return true;
}


/**
 * Load xml feed of given url
 *
 * @param   {std::string}   url   - URL which should be used for load the feed
 * @return  {bool}                - true on success, false else
 */
bool FeedLoader::load(std::string feedUrl)
{
    this->url = std::move(feedUrl);
    bool loaded = this->loadXml();

    return loaded;
}


/**
 * Get loaded feed
 *
 * @return  {struct rawRss}
 */
struct rawRss FeedLoader::getFeed()
{
    return *this->feed;
}


/**
 * Calculate size of loaded xml feed
 *
 * @param   {void *}    content     - The content
 * @param   {size_t}    size        - The size
 * @param   {size_t}    nmemb       - The count of members
 * @param   {void *}    userp       - The userp
 *
 * @return  {size_t}                - The calculated size
 */
size_t FeedLoader::curlCalculateMemory(void *content, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    struct rawRss *mem = (struct rawRss *) userp;

    char *ptr = (char*) realloc(mem->content, mem->size + real_size + 1);
    if (ptr == NULL)
    {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->content = ptr;
    memcpy(&(mem->content[mem->size]), content, real_size);
    mem->size += real_size;
    mem->content[mem->size] = 0;

    return real_size;
}


/**
 * Load's the feed with CURL
 *
 * @return  {boolean}   - true on success, false else
 */
bool FeedLoader::loadXml()
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        this->resetFeed();

        curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FeedLoader::curlCalculateMemory);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) this->feed);
    }

    // maybe do some verification checks ?!

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK)
    {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    //std::cout << (unsigned long) this->feed->size << " bytes loaded" << std::endl;

    return true;
}

