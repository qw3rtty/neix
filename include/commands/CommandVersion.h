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

#ifndef CRSS_COMMANDVERSION_H
#define CRSS_COMMANDVERSION_H

#include "commands/Command.h"

namespace crss
{
    class CommandVersion : public Command
    {
    public:
        CommandVersion(const char *arg);
        ~CommandVersion();

		void exec();

    protected:
		char *argument;
    };
}

#endif //CRSS_COMMANDVERSION_H
