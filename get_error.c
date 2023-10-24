#include "main.h"

/**
 * get_error - function calls error according the builtin, syntax or perm.
 * @datash: the data structure that contains arguments.
 * @eval: the error value.
 * Return: the error.
 */
int get_error(data_shell *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = error_env(datash);
		break;
	case 126:
		err = error_path_126(datash);
		break;
	case 127:
		err = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	datash->status = eval;
	return (eval);
}
