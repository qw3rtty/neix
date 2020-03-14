/**
 * TEST MAIN.
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


int main(int argc, char **argv)
{
    int ret = 0;
    ret += run_test_feeds();

    return ret;
}
