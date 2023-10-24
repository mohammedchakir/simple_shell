#include "main.h"

/**
 * cmp_env_name - the compares env variables names
 * with the name passed.
 * @nenv: the name of the environment variable.
 * @name: the name passed.
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int n;

	for (n = 0; nenv[n] != '='; n++)
	{
		if (nenv[n] != name[n])
		{
			return (0);
		}
	}

	return (n + 1);
}

/**
 * _getenv - function gets an environment variable.
 * @name: the name of the environment variable.
 * @_environ: the environment variable.
 * Return: the value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int n, mov;

	ptr_env = NULL;
	mov = 0;

	for (n = 0; _environ[n]; n++)
	{
		mov = cmp_env_name(_environ[n], name);
		if (mov)
		{
			ptr_env = _environ[n];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - function prints the evironment variables.
 * @datash: the data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
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
