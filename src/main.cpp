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
    ConfigReader mainConfig = ConfigReader::create(MAIN_CONFIG_PATH);
    if (mainConfig.count() == 0)
    {
        cout << prefix << "It looks like there are no entries in your neix.conf. Take a look on the README.md." << endl;
        return 0;
    }

    ConfigReader feedConfig = ConfigReader::create(FEED_CONFIG_PATH);
    if (feedConfig.count() == 0)
    {
        cout << prefix << "No feeds configured! Take a look into your feeds.conf file." << endl;
        return 0;
    }
    
    // Set locale for application
	if (mainConfig.hasEntry("locale"))
	{
		string locale = mainConfig.getEntryByName("locale");
    	setlocale (LC_ALL, locale.c_str());
	}
	else
	{
		cout << prefix << "! Could not set 'locale', no entry found in config." << endl;	
	}

    cout << prefix << "Loading feeds " << flush;
	vector<pair<string, string>> feedList = feedConfig.getList();
    vector<pair<string, string>>::iterator it;
    for (it = feedList.begin(); it != feedList.end(); ++it)
    {
        cout << "." << flush;
        struct rss *newFeed = loader.createNewFeed(it->first.c_str(), it->second.c_str());
        feeds->addFeed(newFeed);
        loader.load(it->second);

        Parser *parser = FactoryParser::getInstance(loader.getFeed());
        parser->applyConfig(mainConfig.getList());
        int index = distance(feedList.begin(), it);

        int articleIndex = 0;
        struct rssItem *newArticle;
        while ((newArticle = parser->getFeedItem()) != nullptr)
        {
            feeds->addArticle(index, articleIndex++, newArticle);
        }
    }
    cout << " Done" << endl;
	
	if (!mainConfig.hasEntry("openCommand"))
	{
		cout << prefix << "! Will not set 'openCommand', no entry found in config." << endl;
	}

    cout << prefix << "Launch TUI" << endl;
    Application app;
   	app.openCommand = mainConfig.getEntryByName("openCommand");
    app.show();

    return 0;
}
