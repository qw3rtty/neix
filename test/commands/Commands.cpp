/**
 * TEST Commands.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <string>
#include <gtest/gtest.h>

#include "commands/Command.h"
#include "commands/CommandVersion.h"

using namespace std;
using namespace crss;
namespace {
    TEST(commands, version)
    {
        string arg;
        Command *cmd = new CommandVersion(arg.c_str());

        EXPECT_FALSE(cmd == nullptr);
    }
}
