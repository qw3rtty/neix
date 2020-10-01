/**
 * Database Interface
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.3
 * @filesource
 */

#ifndef NEIX_DATABASEINTERFACE_H
#define NEIX_DATABASEINTERFACE_H

#include <string>

using namespace std;
namespace neix
{
    class DatabaseInterface
    {
    public:
        virtual DatabaseInterface() = default;
        virtual ~DatabaseInterface() = default;

        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual bool exists() = 0;
        virtual struct rssItem** search(string term) = 0;

        virtual void createSchema() = 0;
        virtual void insertFeed(struct rss *feed) = 0;
        virtual void insertArticle(struct rssItem *article, int feedID) = 0;
        virtual void markArticleAsRead(int articleID) = 0;

        virtual struct rss** getFeeds() = 0;
        virtual struct rss* getFeedById(int feedID) = 0;

        virtual struct rssItem** getArticles() = 0;
        virtual struct rssItem* getArticleById(int feedID) = 0;
    }
}

#endif //NEIX_DATABASEINTERFACE_H
