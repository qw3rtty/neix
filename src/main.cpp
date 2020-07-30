#include <iostream>
#include "config.h"
#include "application/Application.h"
#include "feed/FeedLoader.h"
#include "parser/Parser.h"
#include "parser/FactoryParser.h"
#include "config/ConfigReader.h"

using namespace std;
using namespace neix;


/**
 * Helper to read config files
 *
 * @param   path    - Path to the config file which should be read
 * @return  config map
 */
map<string, string> getConfigByPath(string path)
{
    ConfigReader reader(path.c_str());
    map <string, string> config;

    try {
        config = reader.read();
    } catch (const char *msg) {
        cout << prefix << "Failed to load: " << path << endl;
        cout << prefix <<  msg << endl;
        exit(0);
    }

    return config;
}


int main()
{
    cout << prefix << "Starting version " << VERSION << endl;

    Feeds *feeds = Feeds::getInstance();
    FeedLoader loader;

    cout << prefix << "Loading configuration files" << endl;
    map <string, string> mainConfig = getConfigByPath(MAIN_CONFIG_PATH);
    string locale = mainConfig.at("locale");
    setlocale (LC_ALL, locale.c_str());

    map<string, string> feedList = getConfigByPath(FEED_CONFIG_PATH);
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
