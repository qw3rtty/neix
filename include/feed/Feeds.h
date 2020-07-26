/**
 * Feeds singleton class.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef neix_FEEDS_H
#define neix_FEEDS_H

#define FEEDS_MAX 100

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
    int articleCount;
    int unreadCount;
    struct rssItem *items[FEEDS_MAX];
};

namespace neix
{
    class Feeds
    {
    public:
        static Feeds *getInstance();
        struct rss *getFeed(int index);
        struct rssItem *getArticle(int feedIndex, int articleIndex);
        int getCount();
        char* getFeedLineTitle(int feedIndex, unsigned int length = 0);

        bool validIndex(int index);
        bool addFeed(struct rss *newFeed);
        bool addArticle(int feedIndex, int articleIndex, struct rssItem *newArticle);

    private:
        Feeds();
        int count;

        static Feeds *instance;
        struct rss *rssFeeds[FEEDS_MAX];
    };
}

#endif //neix_FEEDS_H
