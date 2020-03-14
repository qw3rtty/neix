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
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "feeds.h"

static void test_feeds_load(void **state)
{
    int success = feeds_load();
    assert_true(success);
}

static void test_feeds_count(void **state)
{
    assert_true(feeds_count == FEEDS_MAX);
}

int run_test_feeds(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_feeds_load),
        cmocka_unit_test(test_feeds_count),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}