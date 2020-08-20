#include <iostream>
#include <unistd.h>
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
 * @return  config vector list
 */
vector<pair<string, string>> getConfigByPath(const string& path)
{
    ConfigReader reader(path.c_str());
    vector<pair<string, string>> config;

    try {
        config = reader.read();
    } catch (const char *msg) {
        cout << prefix << "Failed to load: " << path << endl;
        cout << prefix <<  msg << endl;
        exit(0);
    }

    return config;
}

/**
 * Applies config to parser
 *
 * @param   p               - Parser to configure
 * @param   configList      - Config to apply
 */
void applyConfigToParser (Parser* p, const vector<pair<string, string>>& configList)
{
    p->setTimeFormatUI(configList.at(0).second.c_str());

    if (configList.size() >= 4)
    {
        p->setRenderCommand(configList.at(3).second.c_str());
    }
}

/**
 * Process command line arguments
 * @param   argc
 * @param   argv
 */
void processArguments(int argc, char **argv)
{
    int option;
    while ((option = getopt(argc, argv, "v")) != -1)
    {
        switch (option)
        {
            case 'v':
                cout << prefix << "Installed version: " << VERSION << endl;
                break;

            default:
                break;
        }
    }

    if (argc > 1)
    {
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    processArguments(argc, argv);
    cout << prefix << "Starting version " << VERSION << endl;

    Feeds *feeds = Feeds::getInstance();
    FeedLoader loader;

    cout << prefix << "Loading configuration files" << endl;
    vector<pair<string, string>> mainConfig = getConfigByPath(MAIN_CONFIG_PATH);
    vector<pair<string, string>> feedList = getConfigByPath(FEED_CONFIG_PATH);
    if (feedList.empty())
    {
        cout << prefix << "No feeds configured! Take a look into your feeds.conf file." << endl;
        return 0;
    }
    
    // Set locale for application
    pair<string, string>locale = mainConfig.at(1);
    setlocale (LC_ALL, locale.second.c_str());

    cout << prefix << "Loading feeds " << flush;
    vector<pair<string, string>>::iterator it;
    for (it = feedList.begin(); it != feedList.end(); ++it)
    {
        cout << "." << flush;
        struct rss *newFeed = loader.createNewFeed(it->first.c_str(), it->second.c_str());
        feeds->addFeed(newFeed);
        loader.load(it->second);

        Parser *parser = FactoryParser::getInstance(loader.getFeed());
        applyConfigToParser(parser, mainConfig);
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
    app.openCommand = mainConfig.at(2).second;
    app.show();

    return 0;
}
