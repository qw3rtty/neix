#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "application/Application.h"
#include "feed/FeedLoader.h"
#include "parser/Parser.h"
#include "parser/FactoryParser.h"
#include "config/ConfigReader.h"
#include "config/opml.h"
#include "helper/helper.h"

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
    unsigned int imported = 0;

    string path;
    ConfigReader fc("");
    opml opmlExporter;

    while ((option = getopt(argc, argv, "vi:e:")) != -1)
    {
        switch (option)
        {
            case 'v':
                cout << prefix << "Installed version: " << VERSION << endl;
                break;

            case 'i':
                cout << prefix << "Import feeds from: " << optarg << endl;
                imported = opml::import(optarg, FEED_CONFIG_PATH);
                cout << prefix << imported << " feed(s) was imported" << endl;
                break;

            case 'e':
                cout << prefix << "Export feeds to: " << optarg << endl;
                path = getFeedConfigPath();
                fc = ConfigReader::create(path.c_str());
                
                opmlExporter.setList(fc.getList());
                opmlExporter.create();
                opmlExporter.exportFeeds(optarg);
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
    // Set default configured environment, ncurses unicode support
    setlocale(LC_ALL, "");
    processArguments(argc, argv);
    if (!configFilesExists())
    {
        copyDefaultConfigFiles();
        cout << prefix << "No config files found. Copied default config files!" << endl;
    }

    cout << prefix << "Starting version " << VERSION << endl;
    Feeds *feeds = Feeds::getInstance();
    FeedLoader loader;

    cout << prefix << "Loading configuration files" << endl;
    string mainConfigPath = getMainConfigPath();
    ConfigReader mainConfig = ConfigReader::create(mainConfigPath.c_str());
    if (mainConfig.count() == 0)
    {
        cout << prefix << "It looks like there are no entries in your neix.conf. Take a look on the README.md." << endl;
        return 0;
    }

    string feedConfigPath = getFeedConfigPath();
    ConfigReader feedConfig = ConfigReader::create(feedConfigPath.c_str());
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

    if (!mainConfig.hasEntry("openCommand"))
    {
        cout << prefix << "! Will not set 'openCommand', no entry found in config." << endl;
    }

    cout << prefix << "Loading feeds " << endl;
    vector<pair<string, string>> feedList = feedConfig.getList();
    vector<pair<string, string>>::iterator it;
    
    // Fill feeds  
    for (it = feedList.begin(); it != feedList.end(); ++it)
    {
        struct rss *newFeed = loader.createNewFeed(it->first.c_str(), it->second.c_str());
        feeds->addFeed(newFeed);
    }

    cout << prefix << "Launch TUI" << endl;
    Application app;
    app.openCommand = mainConfig.getEntryByName("openCommand");
    app.renderCommand = mainConfig.getEntryByName("renderText");
    thread asyncThread(&Application::show, &app);

    // Load and fill articles
    for (it = feedList.begin(); it != feedList.end(); ++it)
    {
        if (!loader.load(it->second))
        {
            continue;
        }

        int index = distance(feedList.begin(), it);
        try 
        {
            Parser *parser = FactoryParser::getInstance(loader.getFeed());
            parser->applyConfig(mainConfig.getList());

            int articleIndex = 0;
            struct rssItem *newArticle;
            while ((newArticle = parser->getFeedItem()) != nullptr)
            {
                feeds->addArticle(index, articleIndex++, newArticle);
            }
        } catch(exception& e) {
            struct rss* errorFeed = feeds->getFeed(index);
            errorFeed->error = true;
        }

        app.fillWindowsWithContent();
        app.printWindows();
    }
    asyncThread.join();

    return 0;
}
