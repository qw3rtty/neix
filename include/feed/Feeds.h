/**
 * Feeds singleton class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#ifndef CRSS_FEEDS_H
#define CRSS_FEEDS_H

#define FEEDS_MAX 10

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
    int itemCount;
    struct rssItem *items[FEEDS_MAX];
};

namespace crss
{
    class Feeds
    {
    public:
        static Feeds *getInstance();
        struct rss *get(int index);
        struct rssItem *getArticle(int feedIndex, int articleIndex);
        int getCount();

        bool add(struct rss *newFeed);
        bool addArticle(int feedIndex, int articleIndex, struct rssItem *newArticle);

    private:
        Feeds();
        int count;

        static Feeds *instance;
        struct rss *rssFeeds[FEEDS_MAX];

        bool validIndex(int index);
    };
}

#endif //CRSS_FEEDS_H
