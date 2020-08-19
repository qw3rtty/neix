/**
 * Feed loader class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <iostream>
#include <utility>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>

#include "feed/Feeds.h"
#include "feed/FeedLoader.h"

using namespace std;
using namespace neix;


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
    if (this->feed->content != nullptr)
    {
        free(this->feed->content);
    }
}


/**
 * Reset feet
 */
void FeedLoader::resetFeed()
{
    if (this->feed != nullptr)
    {
        free(this->feed);
    }
    this->feed = (struct rawRss*) calloc(100, sizeof(struct rawRss*));
}


/**
 * Create new feed item
 *
 * @return	Pointer to the new feed item
 */
struct rss* FeedLoader::createNewFeed(const char* name, const char* link)
{
	struct rss *newFeed = (struct rss*) calloc(1, sizeof(struct rss));
    newFeed->title = (char*) calloc(strlen(name) + 1, sizeof(char));
    newFeed->url = (char*) calloc(strlen(link) + 1, sizeof(char));
    newFeed->articleCount = 0;
    newFeed->unreadCount = 0;

    strcpy(newFeed->title, name);
    strcpy(newFeed->url, link);

	return newFeed;
}


/**
 * Load xml feed of given url
 *
 * @param   feedUrl     - URL which should be used for load the feed
 * @return  true on success, false else
 */
bool FeedLoader::load(string feedUrl)
{
    this->url = move(feedUrl);
    bool loaded = this->loadXml();

    return loaded;
}


/**
 * Get loaded feed
 *
 * @return  raw loaded feed
 */
struct rawRss FeedLoader::getFeed()
{
    return *this->feed;
}


/**
 * Calculate size of loaded xml feed
 *
 * @param content   - The content
 * @param size      - The size
 * @param nmemb     - The count of members
 * @param userp     - The userp
 * @return          The calculated size
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
 * @return  true on success, false else
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
	    
	// TODO: add verification and security options!
    }

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK)
    {
        cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return false;
    }

    return true;
}

