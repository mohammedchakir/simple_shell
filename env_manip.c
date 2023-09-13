#include "main.h"

/**
 * cmpEnvNames - compares environement variable with a given name
 * @nenvn: name of the current environement variable
 * @n: just a name
 * Return: 0 or plus.
 */
int cmpEnvNames(const char *envn, const char *n)
{
	int i;

	for (i = 0; envn[i] != '='; i++)
	{
		if (envn[i] != n[i])
			return (0);
	}
	return (i + 1);
}

/**
 * CurrEnv - get  current environement variable
 * @n: name of the environement variable
 * @env: current env variable
 * Return: value of the environement variable or NULL 
 */
char *CurrEnv(const char *n, char **env)
{
	char *env_ptr;
	int i;
	int tst = 0;

	env_ptr = NULL;

	for (i = 0; env[i]; i++)
	{
		tst = cmpEnvNames(env[i], n);
		if (tst)
		{
			env_ptr = env[i];
			break;
		}
	}
	return (env_ptr + tst);
}

/**
 * printEnv - prints  environement variables
 * @data: data shell info
 * Return: 1
 */
int printEnv(data_shell *data)
{
	int i, k;

	for (i = 0; data->_environ[i]; i++)
	{

		for (k = 0; datash->_environ[i][k]; k++)
			;
		write(STDOUT_FILENO, datash->_environ[i], k);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
