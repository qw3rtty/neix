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

#ifndef CRSS_FEEDLOADER_H
#define CRSS_FEEDLOADER_H

#define FEEDS_MAX 10

#include <string>

extern struct rss *feeds[FEEDS_MAX];
extern int feeds_count;

struct rawRss
{
    char *content;
    size_t size;
};

struct rssItem
{
    char *title;
    char *description;
    char *date;
    char *url;
    int read;
};

struct rss
{
    char *title;
    char *url;
    struct rssItem *items[FEEDS_MAX];
};

namespace crss
{
    class FeedLoader
    {
    public:
        FeedLoader();
        ~FeedLoader();

        bool loadFeedsFromConfig();
        bool load(std::string feedUrl);
        struct rawRss getFeed();

    private:
        std::string url;
        struct rawRss *feed;

        void resetFeed();
        static size_t curlCalculateMemory(void *content, size_t size, size_t nmemb, void *userp);
        bool loadXml();
    };
}

#endif //CRSS_FEEDLOADER_H
