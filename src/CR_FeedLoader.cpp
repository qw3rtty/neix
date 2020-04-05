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
#include <utility>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>

#include "CR_FeedLoader.h"

struct rss *feeds[FEEDS_MAX];
int feeds_count = 0;


/**
 * Constructor
 */
CR_FeedLoader::CR_FeedLoader()
{
    this->url = "";

    this->feed = (struct rawRss*) malloc(sizeof(struct rawRss*));
    this->feed->content = (char*) malloc(sizeof(char));
    this->feed->size = 0;
}


/**
 * Destructor
 */
CR_FeedLoader::~CR_FeedLoader()
{
    free(this->feed);
}


/**
 * Load xml feed of given url
 *
 * @param   {std::string}   url   - URL which should be used for load the feed
 * @return  {bool}                - true on success, false else
 */
bool CR_FeedLoader::load(std::string feedUrl)
{
    this->url = std::move(feedUrl);
    bool loaded = this->loadXml();

    // TODO: Create real feed items!
    for (int i = 0; i < FEEDS_MAX; i++)
    {
        feeds[i] = (struct rss*) malloc(sizeof(struct rss));

        feeds[i]->title = (char*) "RSS Feed";
        feeds[i]->url = (char*) "https://www.heise.de/developer/rss/news-atom.xml";

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            struct rssItem *item_temp = (struct rssItem*) malloc(sizeof(struct rssItem));
            item_temp->title = (char*) "RSS Article";

            feeds[i]->items[j] = (struct rssItem*) malloc(FEEDS_MAX * sizeof(struct rssItem));
            feeds[i]->items[j] = item_temp;
        }
        feeds_count++;
    }

    return loaded;
}


/**
 * Get loaded feed
 *
 * @return  {struct rawRss}
 */
struct rawRss CR_FeedLoader::getFeed()
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
size_t CR_FeedLoader::curlCalculateMemory(void *content, size_t size, size_t nmemb, void *userp)
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
bool CR_FeedLoader::loadXml()
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CR_FeedLoader::curlCalculateMemory);
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

