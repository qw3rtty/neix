/**
 * Command interface.
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <string.h>
#include "commands/Command.h"

using namespace crss;

/**
 * Constructor
 */
Command::Command(const char *arg)
{
	if (arg != nullptr)
	{
		this->argument = strdup(arg);
	}
}


/**
 * Destructor
 */
Command::~Command() = default;

