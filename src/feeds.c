/**
 * Feeds.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "feeds.h"

struct rss *feeds[FEEDS_MAX];
int feeds_count = 0;

int feeds_load()
{
    // struct curl_temp feed = feeds_load_rss("https://www.heise.de/developer/rss/news-atom.xml");
    // TODO: Parse XML

    for (int i = 0; i < FEEDS_MAX; i++)
    {
        feeds[i] = malloc(sizeof(struct rss));

        feeds[i]->title = "RSS Feed";
        feeds[i]->url = "https://www.heise.de/developer/rss/news-atom.xml";

        for (int j = 0; j < FEEDS_MAX; j++)
        {
            struct rss_item *item_temp = malloc(sizeof(struct rss_item));
            item_temp->title = "RSS Article";

            feeds[i]->items[j] = malloc(FEEDS_MAX * sizeof(struct rss_item));
            feeds[i]->items[j] = item_temp;
        }
        feeds_count++;
    }

    return feeds_count == 0 ? 0 : 1;
}


static size_t feeds_curl_memory(void *content, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    struct curl_temp *mem = (struct curl_temp *) userp;

    char *ptr = realloc(mem->content, mem->size + real_size + 1);
    if (ptr == NULL)
    {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->content = ptr;
    memcpy(&(mem->content[mem->size]), content, real_size);
    mem->size += real_size;
    mem->content[mem->size] = 0;

    return real_size;
}


struct curl_temp feeds_load_rss(char feed_url[])
{
    struct curl_temp rss_feed;
    rss_feed.content = malloc(1);
    rss_feed.size = 0;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, feed_url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, feeds_curl_memory);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &rss_feed);
    }

    // maybe do some verification checks ?!

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // printf("%lu bytes retrieved\n", (unsigned long) rss_feed.size);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return rss_feed;
}
