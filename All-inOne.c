#include "main.h"


/**
 * cd_strcat - Concatenates a CD error message.
 * @datash: Current shell informations.
 * @msg: Message to print.
 * @err: Error message.
 * @str_var: Count.
 * Return: The complete error message.
 */
char *cd_strcat(data_shell *datash, char *msg, char *err, char *str_var)
{
	char *illegal_f;

	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, str_var);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, msg);
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
 * @datash: Currentt shell informations.
 * Return: The complete error message.
 */
char *get_cd_err(data_shell *datash)
{
	int len, l_id;
	char *err, *str_var;
	char *msg;

	str_var = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		l_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		l_id = _strlen(datash->args[1]);
	}
	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(str_var) + _strlen(msg) + l_id + 5;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str_var);
		return (NULL);
	}
	err = cd_strcat(datash, msg, err, str_var);
	free(str_var);
	return (err);
}

/**
 * not_found_err - Generates a generic error message for "command not found."
 * @datash: Current shell informations.
 * Return: The complete error message.
 */
char *not_found_err(data_shell *datash)
{
	int lenght;
	char *err, *str_var;

	str_var = aux_itoa(datash->counter);
	lenght = _strlen(datash->av[0]) + _strlen(str_var);
	lenght += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (lenght + 1));
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
 * exit_shell_err - Creates generic error msg for "exit" cmd in get_exit funct.
 * @datash: Current shell informations.
 * Return: The complete error message.
 */
char *exit_shell_err(data_shell *datash)
{
	int lenght;
	char *err, *str_var;

	str_var = aux_itoa(datash->counter);
	lenght = _strlen(datash->av[0]) + _strlen(str_var);
	lenght += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (lenght + 1));
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

/**
 * env_err - Generates an error message for environment-related issues.
 * @datash: Current shell informations.
 * Return: The complete error message.
 */
char *env_err(data_shell *datash)
{
	int lenght;
	char *err;
	char *str_var;
	char *msg;

	str_var = aux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	lenght = _strlen(datash->av[0]) + _strlen(str_var);
	lenght += _strlen(datash->args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (lenght + 1));
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
	_strcat(err, msg);
	_strcat(err, "\0");
	free(str_var);
	return (err);
}
/**
 * path_denied_err - Generat error msg for perm denied when accessing  path.
 * @datash: Current shel informations.
 * Return: The complete error message.
 */
char *path_denied_err(data_shell *datash)
{
	int lenght;
	char *str_var, *err;

	str_var = aux_itoa(datash->counter);
	lenght = _strlen(datash->av[0]) + _strlen(str_var);
	lenght += _strlen(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (lenght + 1));
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
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(str_var);
	return (err);
}
/**
 * err_get - Execute error handle based on perm, syntax,or built-in cmd issues.
 * @datash: Current Shell information.
 * @eval: Error code.
 * Return: Error information.
 */
int err_get(data_shell *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = env_err(datash);
		break;
	case 126:
		err = path_denied_err(datash);
		break;
	case 127:
		err = not_found_err(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			err = exit_shell_err(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			err = get_cd_err(datash);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	datash->status = eval;
	return (eval);
}
/**
 * remove_comment - Removes all comments from the input.
 * @in: The input string.
 * Return: The input string with comments removed.
 */
char *remove_comment(char *in)
{
	int n, pos;

	pos = 0;
	for (n = 0; in[n]; n++)
	{
		if (in[n] == '#')
		{
			if (n == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[n - 1] == ' ' || in[n - 1] == '\t' || in[n - 1] == ';')
				pos = n;
		}
	}
	if (pos != 0)
	{
		in = _realloc(in, n, pos + 1);
		in[pos] = '\0';
	}
	return (in);
}

/**
 * loop_shell - The main shell loop.
 * @datash: current shell informations.
 * Return: No return value.
 */
void loop_shell(data_shell *datash)
{
	int lp, i_eof;
	char *input;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "--> ", 4);
		input = _readline(&i_eof);
		if (i_eof != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (syntax_err_checker(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, datash);
			lp = command_split(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			lp = 0;
			free(input);
		}
	}
}

/**
 * _readline - Reads input line from the user.
 * @i_eof: Return value of the getline function.
 * Return: The user's input as a string.
 */
char *_readline(int *i_eof)
{
	char *input = NULL;
	size_t size = 0;

	*i_eof = getline(&input, &size, stdin);

	return (input);
}

