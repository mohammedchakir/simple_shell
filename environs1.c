#include "main.h"

/**
 * comp_env_names - Compares environment vari.
 * @nenv: The name of an environment variable.
 * @name: The name to compare against.
 * Return: 0 if the names match, otherwise a non-zero value.
 */
int comp_env_names(const char *nenv, const char *name)
{
	int n;

	for (n = 0; nenv[n] != '='; n++)
	{
		if (nenv[n] != name[n])
			return (0);
	}
	return (n + 1);
}

/**
 * _getenv - Retrieve the value of an environment variable.
 * @name: The name of the environment variable to find.
 * @_environ: The environment variable array.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name, char **_environ)
{
	char *env_ptr;
	int n;
	int checker = 0;

	env_ptr = NULL;

	for (n = 0; _environ[n]; n++)
	{
		checker = comp_env_names(_environ[n], name);
		if (checker)
		{
			env_ptr = _environ[n];
			break;
		}
	}
	return (env_ptr + checker);
}

/**
 * env_printer - Prints environment variables.
 * @datash: Shell information.
 * Return: 1 to indicate successful execution.
 */
int env_printer(data_shell *datash)
{
	int n, m;

	for (n = 0; datash->_environ[n]; n++)
	{

		for (m = 0; datash->_environ[n][m]; m++)
			;
		write(STDOUT_FILENO, datash->_environ[n], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
