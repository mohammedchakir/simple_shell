#include "main.h"

/**
 * cd_strcat- concats cd error message
 * @datash: data from current shell
 * @message: message to print
 * @err: error message
 * @str_var: count
 * Return: full error message
 */
char *cd_strcat(data_shell *datash, char *message, char *err, char *str_var)
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
 * get_cd_err - cd error message
 * @datash: data from current shell
 * Return: Full error message
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
	err = cd_strcat(datash, message, err, str_var);
	free(str_var);
	return (err);
}

/**
 * not_found_err - generic error message for command not found
 * @datash: data from current shell
 * Return: Full error message
 */
char *not_found_err(data_shell *datash)
{
	int len;
	char *err, *str_var;

	str_var = aux_itoa(datash->counter);
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
 * exit_shell_err - generic error message for exit in get_exit
 * @datash: data from current shell
 * Return: Full error message
 */
char *exit_shell_err(data_shell *datash)
{
	int len;
	char *err, *str_var;

	str_var = aux_itoa(datash->counter);
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
