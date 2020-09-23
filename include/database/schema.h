/**
 * Database schema for neix
 * > for SQLite
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.3
 * @filesource
 */

#ifndef NEIX_SCHEMA_H
#define NEIX_SCHEMA_H

const char *feeds_schema = "CREATE TABLE FEEDS("\
                            "ID     INT PRIMARY KEY     NOT NULL,"\
                            "TITLE  TEXT                NOT NULL,"\
                            "URL    TEXT                NOT NULL"\
                            ");";

const char *article_schema = "CREATE TABLE ARTICLES("\
                              "ID           INT     PRIMARY KEY     NOT NULL,"\
                              "FEED_ID      INT                     NOT NULL,"\
                              "TITLE        TEXT                    NOT NULL,"\
                              "DESCRIPTION  TEXT                    NOT NULL,"\
                              "DATE         TEXT                    NOT NULL,"\
                              "URL          TEXT                    NOT NULL,"\
                              "FOREIGN KEY(FEED_ID) REFERENCES FEEDS(ID)"\
                              ");";

#endif //NEIX_SCHEMA_H
