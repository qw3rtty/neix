/**
 * Command version.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <iostream>

#include "commands/Command.h"
#include "commands/CommandVersion.h"

using namespace crss;


/**
 * Constructor
 *
 * @param	arg		- Argument for command
 */
CommandVersion::CommandVersion(const char *arg) : Command(arg) {}


/**
 * Destructor
 */
CommandVersion::~CommandVersion() = default;


/**
 * Execute command
 */
void CommandVersion::exec()
{
    std::cout << "Version " << VERSION << std::endl;
}


