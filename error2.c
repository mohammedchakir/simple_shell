#include "main.h"

/**
 * env_err - env error message
 * @datash: data from current shell
 * Return: Full error message
 */
char *env_err(data_shell *datash)
{
	int len;
	char *err;
	char *str_var;
	char *message;

	str_var = aux_itoa(datash->counter);
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
 * path_denied_err - path denied error message
 * @datash: data from current shell
 * Return: Full error message
 */
char *path_denied_err(data_shell *datash)
{
	int len;
	char *str_var, *err;

	str_var = aux_itoa(datash->counter);
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
