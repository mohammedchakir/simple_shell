#include "main.h"

/**
 * geterr - Executes error handling based on permission, syntax, or built-in command issues.
 * @datash: Shell information.
 * @eval: Error code.
 * Return: Error information.
 */
int geterr(data_shell *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = enverr(datash);
		break;
	case 126:
		err = pathdeniederr(datash);
		break;
	case 127:
		err = notfounderr(datash);
		break;
	case 2:
		if (compareStrings("exit", datash->args[0]) == 0)
			err = exitshellerr(datash);
		else if (compareStrings("cd", datash->args[0]) == 0)
			err = get_cd_err(datash);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, getStringLength(err));
		free(err);
	}

	datash->status = eval;
	return (eval);
}
