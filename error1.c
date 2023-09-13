#include "main.h"

/**
 * cdstrcat - Concatenates a CD error message.
 * @datash: Data from the current shell.
 * @message: Message to print.
 * @err: Error message.
 * @str_var: Count.
 * Return: The complete error message.
 */
char *cdstrcat(data_shell *datash, char *message, char *err, char *str_var)
{
	char *illegal_f;

	copyString(err, datash->av[0]);
	concatenateStrings(err, ": ");
	concatenateStrings(err, str_var);
	concatenateStrings(err, ": ");
	concatenateStrings(err, datash->args[0]);
	concatenateStrings(err, message);
	if (datash->args[1][0] == '-')
	{
		illegal_f = malloc(3);
		illegal_f[0] = '-';
		illegal_f[1] = datash->args[1][1];
		illegal_f[2] = '\0';
		concatenateStrings(err, illegal_f);
		free(illegal_f);
	}
	else
		concatenateStrings(err, datash->args[1]);
	concatenateStrings(err, "\n");
	concatenateStrings(err, "\0");
	return (err);
}

/**
 * getcderr - Retrieve a CD error message.
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *getcderr(data_shell *datash)
{
	int len, l_id;
	char *err, *str_var;
	char *message;

	str_var = auxitoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		message = ": Illegal option ";
		l_id = 2;
	}
	else
	{
		message = ": can't cd to ";
		l_id = getStringLength(datash->args[1]);
	}
	len = getStringLength(datash->av[0]) + getStringLength(datash->args[0]);
	len += getStringLength(str_var) + getStringLength(message) + l_id + 5;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_var);
		return (NULL);
	}
	err = cdstrcat(datash, message, err, str_var);
	free(str_var);
	return (err);
}

/**
 * notfounderr - Generates a generic error message for "command not found."
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *notfounderr(data_shell *datash)
{
	int len;
	char *err, *str_var;

	str_var = auxitoa(datash->counter);
	len = getStringLength(datash->av[0]) + getStringLength(str_var);
	len += getStringLength(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str_var);
		return (NULL);
	}
	copyString(err, datash->av[0]);
	concatenateStrings(err, ": ");
	concatenateStrings(err, str_var);
	concatenateStrings(err, ": ");
	concatenateStrings(err, datash->args[0]);
	concatenateStrings(err, ": not found\n");
	concatenateStrings(err, "\0");
	free(str_var);
	return (err);
}

/**
 * exitshellerr - Creates generic error message for "exit" command in get_exit function.
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *exitshellerr(data_shell *datash)
{
	int len;
	char *err, *str_var;

	str_var = auxitoa(datash->counter);
	len = getStringLength(datash->av[0]) + getStringLength(str_var);
	len += getStringLength(datash->args[0]) + getStringLength(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_var);
		return (NULL);
	}
	copyString(err, datash->av[0]);
	concatenateStrings(err, ": ");
	concatenateStrings(err, str_var);
	concatenateStrings(err, ": ");
	concatenateStrings(err, datash->args[0]);
	concatenateStrings(err, ": Illegal number: ");
	concatenateStrings(err, datash->args[1]);
	concatenateStrings(err, "\n\0");
	free(str_var);
	return (err);
}
