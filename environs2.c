#include "main.h"

/**
 * copy_info - function copies info to create new env or alias.
 * @name: the name.
 * @value: the value.
 * Return: the new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, length;

	len_name = _strlen(name);
	len_value = _strlen(value);
	length = len_name + len_value + 2;
	new = malloc(sizeof(char) * (length));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - function sets an environment variable.
 * @name: the name of the environment variable.
 * @value: the value of the environment variable.
 * @datash: the data structure.
 * Return: no return printed.
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int n;
	char *var_env, *name_env;

	for (n = 0; datash->_environ[n]; n++)
	{
		var_env = _strdup(datash->_environ[n]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[n]);
			datash->_environ[n] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, n, sizeof(char *) * (n + 2));
	datash->_environ[n] = copy_info(name, value);
	datash->_environ[n + 1] = NULL;
}

/**
 * _setenv - function compares env variables names
 * with the name passed.
 * @datash: the data relevant.
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - function deletes a environment variable.
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int n, m, l;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	l = -1;
	for (n = 0; datash->_environ[n]; n++)
	{
		var_env = _strdup(datash->_environ[n]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			l = n;
		}
		free(var_env);
	}
	if (l == -1)
	{
		get_error(datash, -1);
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
