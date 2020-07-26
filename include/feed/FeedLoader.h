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

#ifndef neix_FEEDLOADER_H
#define neix_FEEDLOADER_H

#include <string>
#include <sstream>
#include "Feeds.h"

struct rawRss
{
    char *content;
    size_t size;
};

using namespace std;
namespace neix
{
    class FeedLoader
    {
    public:
        FeedLoader();
        ~FeedLoader();

        struct rss* createNewFeed(const char* name, const char* link);
        bool load(string feedUrl);
        struct rawRss getFeed();

    private:
        string url;
        struct rawRss *feed{};

        void resetFeed();
        static size_t curlCalculateMemory(void *content, size_t size, size_t nmemb, void *userp);
        bool loadXml();
    };
}

#endif //neix_FEEDLOADER_H
