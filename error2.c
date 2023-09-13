#include "main.h"

/**
 * enverr - Generates an error message for environment-related issues.
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *enverr(data_shell *datash)
{
	int len;
	char *err;
	char *str_var;
	char *message;

	str_var = auxitoa(datash->counter);
	message = ": Unable to add/remove from environment\n";
	len = getStringLength(datash->av[0]) + getStringLength(str_var);
	len += getStringLength(datash->args[0]) + getStringLength(message) + 4;
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
	concatenateStrings(err, message);
	concatenateStrings(err, "\0");
	free(str_var);
	return (err);
}

/**
 * pathdeniederr - Generates an error message for permission denied when accessing a path.
 * @datash: Data from the current shell.
 * Return: The complete error message.
 */
char *pathdeniederr(data_shell *datash)
{
	int len;
	char *str_var, *err;

	str_var = auxitoa(datash->counter);
	len = getStringLength(datash->av[0]) + getStringLength(str_var);
	len += getStringLength(datash->args[0]) + 24;
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
	concatenateStrings(err, ": Permission denied\n");
	concatenateStrings(err, "\0");
	free(str_var);
	return (err);
}
