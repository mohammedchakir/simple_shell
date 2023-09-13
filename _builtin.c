#include "main.h"

/**
 * get_built_in - calls builtin function from command
 * @cmd: command
 * Return: function pointer to the builtin command
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
	int j;

	for (j = 0; built[j].name; j++)
	{
		if (_strcmp(built[j].name, cmd) == 0)
			break;
	}
	return (built[j].f);
}
