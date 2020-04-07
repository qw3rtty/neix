#include "CR_UI.h"
#include "feed/CR_FeedLoader.h"
#include "feed/CR_FeedParser.h"

int main()
{
    char feedUrl[5][100] = {
        "https://www.heise.de/developer/rss/news-atom.xml",
        "https://www.heise.de/developer/rss/modernes-cplusplus-blog-atom.xml",
        "https://www.heise.de/autos/rss/news-atom.xml",
        "https://www.heise.de/security/rss/news-atom.xml",
        "https://www.heise.de/mac-and-i/news-atom.xml"
    };
    CR_FeedLoader loader;
    CR_FeedParser parser;

    for (int i = 0; i < FEEDS_MAX; i++)
    {
        feeds[i] = (struct rss*) malloc(sizeof(struct rss));

        loader.load(feedUrl[i]);
        parser.setRawRss(loader.getFeed());

        feeds[i]->title = (char*) malloc(sizeof(char) * 100);
        strcpy(feeds[i]->title, parser.getFeedTitle());

        feeds[i]->url = parser.getFeedUrl();

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            parser.setRawRss(loader.getFeed());
            struct rssItem *item_temp = parser.getFeedItem();

            feeds[i]->items[j] = (struct rssItem*) malloc(FEEDS_MAX * sizeof(struct rssItem));
            feeds[i]->items[j] = item_temp;
        }
        feeds_count++;
    }


    CR_UI ui;
    ui.showUI();

    return 0;
}
