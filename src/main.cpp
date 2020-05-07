#include <iostream>
#include "config.h"
#include "Application.h"
#include "feed/FeedLoader.h"

using namespace crss;

int main()
{
    std::cout << prefix << "Starting version 0.1.0 ..." << std::endl;

    FeedLoader loader;
    std::cout << prefix << "Loading feeds from config ..." << std::endl;
    if (!loader.loadFeedsFromConfig())
    {
        std::cout << "Error while loading feeds from config!" << std::endl;
    }

    std::cout << prefix << "Load content of feeds ..." << std::endl;
    if (!loader.loadArticlesOfFeeds())
    {
        std::cout << "Error while loading articles from feeds!" << std::endl;
    }

    Application app;
    app.show();

    return 0;
}
