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

#ifndef CRSS_COMMAND_H
#define CRSS_COMMAND_H

namespace crss
{
    class Command
    {
    public:
        Command(const char *arg);
        ~Command();

		virtual void exec() = 0;

    protected:
		char *argument;
    };
}

#endif //CRSS_COMMAND_H
