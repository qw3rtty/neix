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

#ifndef CRSS_FEEDS_H
#define CRSS_FEEDS_H

#define FEEDS_MAX 5
#define FEEDS_MAX_LENGTH 50

extern char **feeds;
extern int feeds_count;

struct curl_temp
{
    char *content;
    size_t size;
};

struct rss_item
{
    char *title;
    char *description;
    char *date;
    char *url;
    int read;
};

struct rss
{
    char *title;
    char *url;
    struct rss_item *items[FEEDS_MAX];
};

int feeds_load();
struct curl_temp feeds_load_rss(char feed_url[]);

#endif //CRSS_FEEDS_H
