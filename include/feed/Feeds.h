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

#ifndef NEIX_FEEDS_H
#define NEIX_FEEDS_H

#include <vector>
using namespace std;

struct rssItem
{
    char* title;
    char* description;
    char* date;
    char* url;
    int read;
};

struct rss
{
    char* title;
    char* url;
    int articleCount;
    int unreadCount;
    bool error;
    bool loading;
    vector<struct rssItem*> items;
};

namespace neix
{
    class Feeds
    {
    public:
        static Feeds* getInstance();
        struct rss* getFeed(int index);
        struct rssItem* getArticle(int feedIndex, int articleIndex);
        int getCount();
        char* getFeedLineTitle(int feedIndex, unsigned int length = 0);

        bool validIndex(int index);
        bool addFeed(struct rss* newFeed);
        bool addArticle(int feedIndex, int articleIndex, struct rssItem* newArticle);

    private:
        Feeds();
        int count;

        static Feeds* instance;
        vector<struct rss*> rssFeeds;
    };
}

#endif //NEIX_FEEDS_H
