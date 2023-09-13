#include "main.h"

/**
 * concat_cd- concatenate  cd error messages
 * @data: data information about shell
 * @m: message to print on the output stream
 * @err: error message
 * @str: concats counter
 * Return: full concatenated err message
 */
char *concat_cd(data_shell *data, char *m, char *err, char *str)
{
	char *merg;

	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, m);
	if (data->args[1][0] == '-')
	{
		merg = malloc(3);
		merg[0] = '-';
		merg[1] = datash->args[1][1];
		merg[2] = '\0';
		_strcat(err, merg);
		free(merg);
	}
	else
	_strcat(err, data->args[1]);
	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * cd_err - cd error message
 * @data: data from current shell
 * Return: Full error message
 */
char *cd_err(data_shell *data)
{
	int l, id;
	char *err, *str;
	char *message;

	str = int_tostring(data->counter);
	if (data->args[1][0] == '-')
	{
		message = ": forbiden option ";
		id = 2;
	}
	else
	{
		message = ": can't cd to ";
		id = _strlen(data->args[1]);
	}
	l = _strlen(data->av[0]) + _strlen(data->args[0]);
	l += _strlen(str) + _strlen(message) + id + 5;
	err = malloc(sizeof(char) * (l + 1));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}
	err = cd_strcat(data, message, err, str);
	free(str);
	return (err);
}

/**
 * miss_err - error message for 404 cmd
 * @data: data from current shell
 * Return: complete err message
 */
char *miss_err(data_shell *data)
{
	int len;
	char *err, *str_var;

	str_var = int_tostring(data->counter);
	len = _strlen(data->av[0]) + _strlen(str_var);
	len += _strlen(data->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str_var);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": 404 ! not found\n");
	_strcat(err, "\0");
	free(str_var);
	return (err);
}

/**
 * exit_err - exit error message
 * @data: data information about curr shell
 * Return: complete error message
 */
char *exit_err(data_shell *data)
{
	int len;
	char *err, *str_var;

	str_var = int_tostring(data->counter);
	len = _strlen(data->av[0]) + _strlen(str_var);
	len += _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_var);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Forbiden number: ");
	_strcat(err, data->args[1]);
	_strcat(err, "\n\0");
	free(str_var);
	return (err);
}

/**
 * eerrOfEnv - environement error message
 * @datash: data information from current shell
 * Return: complete error message
 */
char *errOfEnv(data_shell *data)
{
	int len;
	char *err;
	char *str_var;
	char *message;

	str_var = int_tostring(data->counter);
	message = ": Unable to add/remove from environment\n";
	len = _strlen(data->av[0]) + _strlen(str_var);
	len += _strlen(data->args[0]) + _strlen(message) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str_var);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, message);
	_strcat(err, "\0");
	free(str_var);
	return (err);
}
