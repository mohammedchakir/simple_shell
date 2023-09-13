#include "main.h"

/**
 * infocp - Copies information.
 * @name: The name of the item to copy.
 * @value: The value of the item to copy.
 * Return: A new environment or alias containing the copied information.
 */
char *infocp(char *name, char *value)
{
	char *new_ptr;
	int name_l, value_l, length;

	name_l = getStringLength(name);
	value_l = getStringLength(value);
	length = name_l + value_l + 2;
	new_ptr = malloc(sizeof(char) * (length));
	copyString(new_ptr, name);
	concatenateStrings(new_ptr, "=");
	concatenateStrings(new_ptr, value);
	concatenateStrings(new_ptr, "\0");
	return (new_ptr);
}

/**
 * environset - Sets an environment variable.
 * @name: The name of the environment variable to set.
 * @value: The value to assign to the environment variable.
 * @datash: Shell information.
 * Return: None.
 */
void environset(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_environ, *name_environ;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_environ = duplicateString(datash->_environ[i]);
		name_environ = tokenizeString(var_environ, "=");
		if (compareStrings(name_environ, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = info_cp(name_environ, value);
			free(var_environ);
			return;
		}
		free(var_environ);
	}
	datash->_environ = resizeDblePtrMem(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = info_cp(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * setenv - Sets environment variables.
 * @datash: Shell information.
 * Return: 1 to indicate successful execution.
 */
int setenv(data_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		err_get(datash, -1);
		return (1);
	}
	environset(datash->args[1], datash->args[2], datash);
	return (1);
}

/**
 * unsetenv - Deletes an environment variable.
 * @datash: Shell information.
 * Return: 1 to indicate successful execution.
 */
int unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_environ, *name_environ;
	int i, j, a;

	if (datash->args[1] == NULL)
	{
		err_get(datash, -1);
		return (1);
	}
	a = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_environ = duplicateString(datash->_environ[i]);
		name_environ = tokenizeString(var_environ, "=");
		if (compareStrings(name_environ, datash->args[1]) == 0)
			a = i;
		free(var_environ);
	}
	if (a == -1)
	{
		err_get(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != a)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[a]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
