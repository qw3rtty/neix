#include <iostream>
#include "config.h"
#include "Application.h"
#include "feed/FeedLoader.h"
#include "parser/Parser.h"
#include "parser/FactoryParser.h"
#include "config/ConfigReader.h"

using namespace std;
using namespace crss;

int main()
{
    cout << prefix << "Starting version " << VERSION << endl;

    Feeds *feeds = Feeds::getInstance();
    FeedLoader loader;
    ConfigReader feedConfigReader(FEED_CONFIG_PATH);
    map<string, string> feedList = feedConfigReader.read();

    cout << prefix << feedList.size() << " feeds found" << endl;
    cout << prefix << "Loading feeds " << flush;
    map<string, string>::iterator it;
    for (it = feedList.begin(); it != feedList.end(); ++it)
    {
        cout << "." << flush;
        struct rss *newFeed = loader.createNewFeed(it->first.c_str(), it->second.c_str());
        feeds->addFeed(newFeed);
        loader.load(it->second);

        Parser *parser = FactoryParser::getInstance(loader.getFeed());
        int index = distance(feedList.begin(), it);

        struct rssItem *newArticle = parser->getFeedItem();
        int articleIndex = 0;
        while (newArticle != nullptr)
        {
            feeds->addArticle(index, articleIndex++, newArticle);
            newArticle = parser->getFeedItem();
        }
    }
    cout << " Done" << endl;

    cout << prefix << "Launch TUI" << endl;
    Application app;
    app.show();

    return 0;
}
