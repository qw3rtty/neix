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

#include "feed/Feeds.h"
#include "feed/FeedLoader.h"
#include "feed/FeedParser.h"
using namespace crss;


/**
 * Constructor
 */
FeedLoader::FeedLoader()
{
    this->configPath << getenv("HOME") << "/.config/crss/feeds.conf";
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
 *
 * @return  true on success, false else
 */
bool FeedLoader::loadFeedsFromConfig()
{
    std::ifstream file;
    std::string line;

    std::string delimiter = "=";
    std::string name;
    std::string link;

    file.open(this->configPath.str());
    if (!file.is_open())
    {
        std::cout << "Could not load config file!" << std::endl;
        return false;
    }

    Feeds *feeds = Feeds::getInstance();
    while (!file.eof())
    {
        getline(file, line);
        name = line.substr(0, line.find(delimiter));
        link = line.substr(line.find(delimiter) + 1, line.length());

        if (name.empty() || link.empty())
        {
            continue;
        }

        struct rss *newFeed = (struct rss*) malloc(sizeof(struct rss));
        newFeed->title = (char*) malloc(sizeof(char) * name.length() + 1);
        newFeed->url = (char*) malloc(sizeof(char) * link.length() + 1);

        strcpy(newFeed->title, name.c_str());
        strcpy(newFeed->url, link.c_str());

        newFeed->articleCount = 0;
        newFeed->unreadCount = 0;

        feeds->add(newFeed);
    }
    file.close();

    return true;
}


/**
 * Load articles of all feeds
 *
 * @return  true on success, false else
 */
bool FeedLoader::loadArticlesOfFeeds()
{
    Feeds *feeds = Feeds::getInstance();
    FeedParser parser;

    std::cout << feeds->getCount() << " Feeds to load" << std::endl;
    for (int i = 0; i < feeds->getCount(); i++)
    {
        struct rss *feed = feeds->get(i);
        std::cout << "Loading: " << feed->title << " | " << feed->url << std::endl;

        std::string url(feed->url);
        this->load(url);
        parser.setRawRss(this->getFeed());

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            struct rssItem *newArticle = parser.getFeedItem();
            feeds->addArticle(i, j, newArticle);

            feed->articleCount++;
            feed->unreadCount++;
        }
    }

    return true;
}


/**
 * Load xml feed of given url
 *
 * @param   feedUrl     - URL which should be used for load the feed
 * @return  true on success, false else
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

