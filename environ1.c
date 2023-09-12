#include "main.h"

/**
 * comp_env_names - compares env variables
 * @nenv: name of the env variable
 * @name: name
 * Return: 0 or other number.
 */
int comp_env_names(const char *nenv, const char *name)
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
 * _getenv - get env variable
 * @name: name of the env variable
 * @_environ: env variable
 * Return: value of the env variable or NULL if not found
 */
char *_getenv(const char *name, char **_environ)
{
	char *env_ptr;
	int i;
	int checker = 0;

	env_ptr = NULL;

	for (i = 0; _environ[i]; i++)
	{
		checker = comp_env_names(_environ[i], name);
		if (checker)
		{
			env_ptr = _environ[i];
			break;
		}
	}
	return (env_ptr + checker);
}

/**
 * env_printer - prints  env variables
 * @datash: shell info
 * Return: 1
 */
int env_printer(data_shell *datash)
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
