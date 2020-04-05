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

#ifndef CRSS_CR_FEEDLOADER_H
#define CRSS_CR_FEEDLOADER_H

#define FEEDS_MAX 5

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


class CR_FeedLoader
{
public:
    CR_FeedLoader();
    ~CR_FeedLoader();

    bool load(std::string feedUrl);
    struct rawRss getFeed();

private:
    std::string url;
    struct rawRss *feed;

    static size_t curlCalculateMemory(void *content, size_t size, size_t nmemb, void *userp);
    bool loadXml();
};

#endif //CRSS_CR_FEEDLOADER_H
