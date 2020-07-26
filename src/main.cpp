#include <iostream>
#include "config.h"
#include "application/Application.h"
#include "feed/FeedLoader.h"
#include "parser/Parser.h"
#include "parser/FactoryParser.h"
#include "config/ConfigReader.h"

using namespace std;
using namespace neix;

int main()
{
    cout << prefix << "Starting version " << VERSION << endl;

    Feeds *feeds = Feeds::getInstance();
    FeedLoader loader;

    ConfigReader mainConfigReader(MAIN_CONFIG_PATH);
    map <string, string> mainConfig;
    try {
        cout << prefix << "Loading main configuration" << endl;
        mainConfig = mainConfigReader.read();
    } catch (const char *msg) {
        cout << prefix <<  msg << endl;
        exit(0);
    }

    string locale = mainConfig.at("locale");
    setlocale (LC_ALL, locale.c_str());

    ConfigReader feedConfigReader(FEED_CONFIG_PATH);
    map<string, string> feedList;
    try {
        cout << prefix << "Loading feeds configuration" << endl;
        feedList = feedConfigReader.read();
    } catch (const char *msg) {
        cout << prefix << msg << endl;
        exit(0);
    }

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
        parser->setTimeFormatUI(mainConfig.at("dateFormat").c_str());
        int index = distance(feedList.begin(), it);

        int articleIndex = 0;
        struct rssItem *newArticle;
        while ((newArticle = parser->getFeedItem()) != nullptr)
        {
            feeds->addArticle(index, articleIndex++, newArticle);
        }
    }
    cout << " Done" << endl;

    cout << prefix << "Launch TUI" << endl;
    Application app;
    app.openCommand = mainConfig.at("openCommand");
    app.show();

    return 0;
}
