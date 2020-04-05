/**
 * Feed parser class.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include "feed/CR_FeedParser.h"


/**
 * Constructor
 */
CR_FeedParser::CR_FeedParser()
{}


/**
 * Destructor
 */
CR_FeedParser::~CR_FeedParser()
{}


/**
 * Set raw rss content
 *
 * @param   {struct rawRss}     rawContent      - The loaded raw content
 */
void CR_FeedParser::setRawRss(struct rawRss rawContent)
{
    this->rss = &rawContent;
}


/**
 * Get title of raw feed
 *
 * @return  {char*}    - Feed title
 */
char* CR_FeedParser::getFeedTitle()
{
    return (char*) "RSS Feed";
}


/**
 * Get URL of raw feed
 *
 * @return  {char*}    - Feed URL
 */
char* CR_FeedParser::getFeedUrl()
{
    return (char*) "https://www.heise.de/developer/rss/news-atom.xml";
}


/**
 * Get an feed item of raw content
 *
 * @return  {struct rssItem*}    - Item of feed
 */
struct rssItem* CR_FeedParser::getFeedItem()
{
    struct rssItem *item = (struct rssItem*) malloc(sizeof(struct rssItem));
    item->title = (char*) "RSS Article";

    return item;
}