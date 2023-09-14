#include "main.h"

/**
 * get_built_in - Retrieves ptr to corresponding built-in funct for given cmd.
 * @cmd: The command for which to fetch the built-in function.
 * Return: A function pointer to the built-in command.
 */
int (*get_built_in(char *cmd))(data_shell *)
{
	builtin_t built[] = {
		{ "env", env_printer },
		{ "exit", shell_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", change_dir },
		{ "help", help_get },
		{ NULL, NULL }
	};
	int m;

	for (m = 0; built[m].name; m++)
	{
		if (_strcmp(built[m].name, cmd) == 0)
			break;
	}
	return (built[m].f);
}
