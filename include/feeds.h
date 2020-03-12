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

#define FEEDS_MAX 20
#define FEEDS_MAX_LENGTH 50

extern char** feeds;
extern int feeds_count;

int feeds_load();

#endif //CRSS_FEEDS_H
