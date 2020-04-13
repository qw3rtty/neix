#include <iostream>
#include "UI.h"
#include "feed/FeedLoader.h"
#include "feed/FeedParser.h"

using namespace cr;

int main()
{
    FeedParser parser;
    FeedLoader loader;

    if (!loader.loadFeedsFromConfig())
    {
        std::cout << "Error while loading feeds from config!" << std::endl;
    }

    for (int i = 0; i < feeds_count; i++)
    {
        std::cout << "Loading: " << feeds[i]->title << " | " << feeds[i]->url << std::endl;

        std::string url(feeds[i]->url);
        loader.load(url);
        parser.setRawRss(loader.getFeed());

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            struct rssItem *item_temp = parser.getFeedItem();
            feeds[i]->items[j] = (struct rssItem*) malloc(FEEDS_MAX * sizeof(struct rssItem));
            feeds[i]->items[j] = item_temp;
        }
    }

    UI ui;
    ui.showUI();

    return 0;
}
