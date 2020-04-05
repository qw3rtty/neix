#include <ncurses.h>

#include "config.h"
#include "ui.h"
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
            struct rssItem *item_temp = parser.getFeedItem();

            feeds[i]->items[j] = (struct rssItem*) malloc(FEEDS_MAX * sizeof(struct rssItem));
            feeds[i]->items[j] = item_temp;
        }
        feeds_count++;
    }



    WINDOW *window_feeds;
    int rss_choice = 1;
    int rss_article_choice = 0;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();

    int width = COLS;
    int height = LINES - 2;

    window_feeds = newwin(height, width, 2, 0);
    keypad(window_feeds, TRUE);
    mvprintw(0, 0, "Use arrow/vim keys to go up and down, Press enter to select a choice, Press 'q' to quit.");
    refresh();

    ui_print_feeds(window_feeds, rss_choice, rss_article_choice);

    while (1)
    {
        c = wgetch(window_feeds);
        switch (c)
        {
            case KEY_UP:
            case KEY_K:
                rss_article_choice = 0;
                rss_choice = decrease_choice(rss_choice);
                break;

            case KEY_DOWN:
            case KEY_J:
                rss_article_choice = 0;
                rss_choice = increase_choice(rss_choice);
                break;

            case KEY_UPPER_K:
                rss_article_choice = decrease_choice(rss_article_choice);
                break;

            case KEY_UPPER_J:
                rss_article_choice = increase_choice(rss_article_choice);
                break;

            case ENTER:
            case KEY_Q:
                choice = rss_choice;
                break;
                
            default:
                mvprintw(1, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }

        ui_print_feeds(window_feeds, rss_choice, rss_article_choice);
        if (choice != 0)
        {
            break;
        }
    }

    clrtoeol();
    refresh();
    endwin();

    return 0;
}
