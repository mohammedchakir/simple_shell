#include "main.h"

/**
 * strcat_cd - the function that concatenates the message for cd error.
 * @datash: the data relevant.
 * @msg: the message to print.
 * @error: the output of message.
 * @ver_str: the counter of lines.
 * Return: the error message printed.
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illeg_flag;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illeg_flag = malloc(3);
		illeg_flag[0] = '-';
		illeg_flag[1] = datash->args[1][1];
		illeg_flag[2] = '\0';
		_strcat(error, illeg_flag);
		free(illeg_flag);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - the error message for cd command in get_cd.
 * @datash: the data relevant.
 * Return: the error message printed.
 */
char *error_get_cd(data_shell *datash)
{
	int len, len_id;
	char *err, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err = strcat_cd(datash, msg, err, ver_str);

	free(ver_str);

	return (err);
}

/**
 * error_not_found - the generic error message for command not found.
 * @datash: the data relevant (counter, arguments).
 * Return: the error message printed.
 */
char *error_not_found(data_shell *datash)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(ver_str);
	return (err);
}

/**
 * error_exit_shell - the generic error message for exit in get_exit.
 * @datash: data relevant (counter, arguments).
 * Return: the error message printed.
 */
char *error_exit_shell(data_shell *datash)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->args[1]);
	_strcat(err, "\n\0");
	free(ver_str);

	return (err);
}
