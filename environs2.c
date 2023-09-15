#include "main.h"

/**
 * info_cp - Copies informations.
 * @name: The name of the item to copy.
 * @value: The value of the item to copy.
 * Return: A new environment or alias containing the copied information.
 */
char *info_cp(char *name, char *value)
{
	char *new_ptr;
	int name_l, value_l, length;

	name_l = _strlen(name);
	value_l = _strlen(value);
	length = name_l + value_l + 2;
	new_ptr = malloc(sizeof(char) * (length));
	_strcpy(new_ptr, name);
	_strcat(new_ptr, "=");
	_strcat(new_ptr, value);
	_strcat(new_ptr, "\0");
	return (new_ptr);
}

/**
 * environ_set - Sets an environment variable.
 * @name: The name of the environment variable to set.
 * @value: The value to assign to the environment variable.
 * @datash: Shell information.
 * Return: None.
 */
void environ_set(char *name, char *value, data_shell *datash)
{
	int n;
	char *var_environ, *name_environ;

	for (n = 0; datash->_environ[n]; n++)
	{
		var_environ = _strdup(datash->_environ[n]);
		name_environ = _strtok(var_environ, "=");
		if (_strcmp(name_environ, name) == 0)
		{
			free(datash->_environ[n]);
			datash->_environ[n] = info_cp(name_environ, value);
			free(var_environ);
			return;
		}
		free(var_environ);
	}
	datash->_environ = _reallocdp(datash->_environ, n, sizeof(char *) * (n + 2));
	datash->_environ[n] = info_cp(name, value);
	datash->_environ[n + 1] = NULL;
}

/**
 * _setenv - Sets environment variables.
 * @datash: Shell information.
 * Return: 1 to indicate successful execution.
 */
int _setenv(data_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		err_get(datash, -1);
		return (1);
	}
	environ_set(datash->args[1], datash->args[2], datash);
	return (1);
}

/**
 * _unsetenv - Deletes an environment variable.
 * @datash: Shell information.
 * Return: 1 to indicate successful execution.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_environ, *name_environ;
	int n, m, l;

	if (datash->args[1] == NULL)
	{
		err_get(datash, -1);
		return (1);
	}
	l = -1;
	for (n = 0; datash->_environ[n]; n++)
	{
		var_environ = _strdup(datash->_environ[n]);
		name_environ = _strtok(var_environ, "=");
		if (_strcmp(name_environ, datash->args[1]) == 0)
			l = n;
		free(var_environ);
	}
	if (l == -1)
	{
		err_get(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (n));
	for (n = m = 0; datash->_environ[n]; n++)
	{
		if (n != l)
		{
			realloc_environ[m] = datash->_environ[n];
			m++;
		}
	}
	realloc_environ[m] = NULL;
	free(datash->_environ[l]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
