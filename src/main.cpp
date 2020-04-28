#include <iostream>
#include "Application.h"
#include "feed/FeedLoader.h"

using namespace crss;

int main()
{
    FeedLoader loader;

    if (!loader.loadFeedsFromConfig())
    {
        std::cout << "Error while loading feeds from config!" << std::endl;
    }

    if (!loader.loadArticlesOfFeeds())
    {
        std::cout << "Error while loading articles from feeds!" << std::endl;
    }

    Application ui;
    ui.show();

    return 0;
}
