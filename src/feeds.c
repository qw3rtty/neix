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

#include "feeds.h"

char** feeds = NULL;
int feeds_count = 0;

int feeds_load()
{
    feeds = calloc(FEEDS_MAX * FEEDS_MAX_LENGTH, sizeof(char*));
    for (int i = 0; i < FEEDS_MAX; i++)
    {
        feeds[i] = malloc(sizeof(char) * FEEDS_MAX_LENGTH);
        strcpy(feeds[i], "RSS");

        feeds_count++;
    }


    return feeds_count == 0 ? 0 : 1;
}