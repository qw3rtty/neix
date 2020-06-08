#include <iostream>
#include "config.h"
#include "Application.h"
#include "feed/FeedLoader.h"
#include "parser/Parser.h"
#include "parser/FactoryParser.h"
#include "config/ConfigFeedReader.h"

using namespace std;
using namespace crss;

int main()
{
    cout << prefix << "Starting version " << VERSION << endl;

    Feeds *feeds = Feeds::getInstance();
    FeedLoader loader;
    ConfigFeedReader cfgFeedReader(FEED_CONFIG_PATH);
    map<string, string> feedList = cfgFeedReader.read();

    cout << prefix << feedList.size() << " feeds found" << endl;
    map<string, string>::iterator it;
    for (it = feedList.begin(); it != feedList.end(); ++it)
    {
        cout << prefix << "Loading: " << it->first << endl;
        struct rss *newFeed = loader.createNewFeed(it->first.c_str(), it->second.c_str());
        feeds->addFeed(newFeed);
        loader.load(it->second);

        Parser *parser = FactoryParser::getInstance(loader.getFeed());
        int index = distance(feedList.begin(), it);
        for (int j = 0; j < FEEDS_MAX; j++)
        {
            struct rssItem *newArticle = parser->getFeedItem();
            feeds->addArticle(index, j, newArticle);
        }
    }

    cout << prefix << "Launch TUI" << endl;
    Application app;
    app.show();

    return 0;
}
