/**
 * TEST Feeds.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <stddef.h>
#include <assert.h>

#include "feeds.h"

int run_test_feeds(void)
{
    int success = feeds_load();
    assert(success);
    assert(feeds_count == FEEDS_MAX);

    struct curl_temp xml_feed = feeds_load_rss("https://www.heise.de/developer/rss/news-atom.xml");

    assert(xml_feed.content != NULL);
    assert(xml_feed.size > 0);

    return 0;
}
