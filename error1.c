#include "main.h"

/**
 * cd_strcat - Concatenates a CD error message.
 * @datash: Data from the current shell.
 * @message: Message to print.
 * @err: Error message.
 * @str_var: Count.
 * Return: The complete error message.
 */
char *cd_strcat(data_shell *datash, char *message, char *err, char *str_var)
{
	char *illegal_f;

	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, message);
	if (datash->args[1][0] == '-')
	{
		illegal_f = malloc(3);
		illegal_f[0] = '-';
		illegal_f[1] = datash->args[1][1];
		illegal_f[2] = '\0';
		_strcat(err, illegal_f);
		free(illegal_f);
	}
	else
		_strcat(err, datash->args[1]);
	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * get_cd_err - Retrieve a CD error message.
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *get_cd_err(data_shell *datash)
{
	int len, l_id;
	char *err, *str_var;
	char *message;

	str_var = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		message = ": Illegal option ";
		l_id = 2;
	}
	else
	{
		message = ": can't cd to ";
		l_id = _strlen(datash->args[1]);
	}
	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(str_var) + _strlen(message) + l_id + 5;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_var);
		return (NULL);
	}
	err = cd_strcat(datash, message, err, str_var);
	free(str_var);
	return (err);
}

/**
 * not_found_err - Generates a generic error message for "command not found."
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *not_found_err(data_shell *datash)
{
	int len;
	char *err, *str_var;

	str_var = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(str_var);
	len += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str_var);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(str_var);
	return (err);
}

/**
 * exit_shell_err - Creates a generic error message for the "exit" command in the get_exit function.
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *exit_shell_err(data_shell *datash)
{
	int len;
	char *err, *str_var;

	str_var = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(str_var);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_var);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->args[1]);
	_strcat(err, "\n\0");
	free(str_var);
	return (err);
}
