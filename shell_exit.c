#include "main.h"

/**
 * exitShell - Exits the shell.
 * @datash: Shell-related information.
 * Return: 0 for success, 1 for failure.
 */
int exitShell(data_shell *datash)
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
 * handleCtrlC - Functionality for handling Ctrl+C.
 * @sig: Signal handler.
 */
void handleCtrlC(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n--> ", 5);
}

