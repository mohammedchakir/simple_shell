#include "main.h"

/**
 * cpyInfo - copies information between name and value
 * @n: name
 * @v: value
 * Return: new ptr of an alias or env.
 */
char *cpyInfo(char *n, char *v)
{
	char *new_ptr;
	int nl, vl, length;

	nl = _strlen(n);
	vl = _strlen(v);
	length = nl + vl + 2;
	new_ptr = malloc(sizeof(char) * (length));
	_strcpy(new_ptr, n);
	_strcat(new_ptr, "=");
	_strcat(new_ptr, v);
	_strcat(new_ptr, "\0");
	return (new_ptr);
}

/**
 * setEnv - sets an environ variable
 * @n: name of the environ variable
 * @v: value of the environ variable
 * @data: data of shell info
 * Return: void
 */
void setEnv(char *n, char *v, data_shell *data)
{
	int i;
	char *venviron, *nenviron;

	for (i = 0; data->_environ[i]; i++)
	{
		venviron = _strdup(data->_environ[i]);
		nenviron = _strtok(venviron, "=");
		if (_strcmp(nenviron, n) == 0)
		{
			free(data->_environ[i]);
			data->_environ[i] = cpyInfo(nenviron, v);
			free(venviron);
			return;
		}
		free(venviron);
	}
	data->_environ = _reallocdp(data->_environ, i, sizeof(char *) * (i + 2));
	data->_environ[i] = cpyInfo(n, v);
	data->_environ[i + 1] = NULL;
}


/**
 * getErr - display the apropriete error type
 * @data: information about shell
 * @value: value of a givem err
 * Return: err value
 */
int getErr(data_shell *data, int value)
{
	char *err;

	switch (value)
	{
	case -1:
		err = errOfEnv(data);
		break;
	case 126:
		err = deniedPath(data);
		break;
	case 127:
		err = miss_err(data);
		break;
	case 2:
		if (_strcmp("exit", data->args[0]) == 0)
			err = exit_err(data);
		else if (_strcmp("cd", data->args[0]) == 0)
			err = cd_err(data);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	data->status = value;
	return (value);
}
 
/**
 * cmpEnv - compares environement variables
 * @data: data of shell info
 * Return: 1
 */
int cmpEnv(data_shell *data)
{
	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		getErr(data, -1);
		return (1);
	}
	setEnv(data->args[1], data->args[2], data);
	return (1);
}

/**
 * deleteEnv - Unset envirob variable
 * @data: data information about shell
 * Return: 1
 */
int deleteEnv(data_shell *data)
{
	char **realloc_environ;
	char *venviron, *nenviron;
	int i, j, k;

	if (data->args[1] == NULL)
	{
		getErr(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->_environ[i]; i++)
	{
		venviron = _strdup(data->_environ[i]);
		nenviron = _strtok(venviron, "=");
		if (_strcmp(nenviron, data->args[1]) == 0)
			k = i;
		free(venviron);
	}
	if (k == -1)
	{
		getErr(data, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = data->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(data->_environ[k]);
	free(data->_environ);
	data->_environ = realloc_environ;
	return (1);
}

