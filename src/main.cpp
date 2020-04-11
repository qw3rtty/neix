#include <iostream>
#include "CR_UI.h"
#include "feed/CR_FeedLoader.h"
#include "feed/CR_FeedParser.h"

int main()
{
    CR_FeedParser parser;
    CR_FeedLoader loader;

    if (!loader.loadFeedsFromConfig())
    {
        std::cout << "Error while loading feeds from config!" << std::endl;
    }

    for (int i = 0; i < feeds_count; i++)
    {
        std::cout << "Loading: " << feeds[i]->title << " | " << feeds[i]->url << std::endl;

        std::string url(feeds[i]->url);
        loader.load(url);

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            parser.setRawRss(loader.getFeed());
            struct rssItem *item_temp = parser.getFeedItem();

            feeds[i]->items[j] = (struct rssItem*) malloc(FEEDS_MAX * sizeof(struct rssItem));
            feeds[i]->items[j] = item_temp;
        }
    }

    CR_UI ui;
    ui.showUI();

    return 0;
}
