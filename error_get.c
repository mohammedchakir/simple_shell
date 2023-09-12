#include "main.h"

/**
 * err_get - executes the error according to the permission, syntax or builtin
 * @datash: shell info
 * @eval: value of errror
 * Return: err
 */
int err_get(data_shell *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = env_err(datash);
		break;
	case 126:
		err = path_denied_err(datash);
		break;
	case 127:
		err = not_found_err(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			err = exit_shell_err(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			err = get_cd_err(datash);
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
