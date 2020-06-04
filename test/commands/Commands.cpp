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
#include <cassert>

#include "commands/Command.h"
#include "commands/CommandVersion.h"

using namespace crss;

int main() {
    std::string arg;
    Command *cmd = new CommandVersion(arg.c_str());
    cmd->exec();

    return 0;
}
