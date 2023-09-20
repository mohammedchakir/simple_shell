#include "main.h"

/**
 * shell_exit - Exits the shell.
 * @datash: Shell information.
 * Return: 0 for successful exit, 1 for an error.
 */
int shell_exit(data_shell *datash)
{
	unsigned int _status;
	int check_digit, str_length, big_num;

	if (datash->args[1] != NULL)
	{
		_status = _atoi(datash->args[1]);
		check_digit = _isdigit(datash->args[1]);
		str_length = _strlen(datash->args[1]);
		big_num = _status > (unsigned int)INT_MAX;
		if (!check_digit || str_length > 10 || big_num)
		{
			err_get(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (_status % 256);
	}
	return (0);
}

/**
 * _sigint - Handles the Ctrl+C functionality.
 * @sig: The signal handler.
 */
void _sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n--> ", 5);
}

