#include "main.h"

/**
 * compenvnames - Compares environment variable names.
 * @nenv: The name of an environment variable.
 * @name: The name to compare against.
 * Return: 0 if the names match, otherwise a non-zero value.
 */
int compenvnames(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
			return (0);
	}
	return (i + 1);
}

/**
 * getenv - Retrieve the value of an environment variable.
 * @name: The name of the environment variable to find.
 * @_environ: The environment variable array.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *getenv(const char *name, char **_environ)
{
	char *env_ptr;
	int i;
	int checker = 0;

	env_ptr = NULL;

	for (i = 0; _environ[i]; i++)
	{
		checker = compenvnames(_environ[i], name);
		if (checker)
		{
			env_ptr = _environ[i];
			break;
		}
	}
	return (env_ptr + checker);
}

/**
 * envprinter - Prints environment variables.
 * @datash: Shell information.
 * Return: 1 to indicate successful execution.
 */
int envprinter(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
