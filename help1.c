#include "main.h"

/**
 * help_get - Invokes the built-in help function.
 * @datash: A pointer to shell information.
 * Return: Returns 1.
 */
int help_get(data_shell *datash)
{
	if (datash->args[1] == 0)
		_help_general();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		_help_setenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		_help_env();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		_help_unsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		_help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		_help_exit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		_help_cd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		_help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
