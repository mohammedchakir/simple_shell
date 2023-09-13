#include "main.h"

/**
 * gethelp - Invokes the built-in help function.
 * @datash: A pointer to shell information.
 * Return: Returns 1.
 */
int gethelp(data_shell *datash)
{
	if (datash->args[1] == 0)
		helpgeneral();
	else if (compareStrings(datash->args[1], "setenv") == 0)
		helpsetenv();
	else if (compareStrings(datash->args[1], "env") == 0)
		helpenv();
	else if (compareStrings(datash->args[1], "unsetenv") == 0)
		helpunsetenv();
	else if (compareStrings(datash->args[1], "help") == 0)
		help();
	else if (compareStrings(datash->args[1], "exit") == 0)
		helpexit();
	else if (compareStrings(datash->args[1], "cd") == 0)
		helpcd();
	else if (compareStrings(datash->args[1], "alias") == 0)
		helpalias();
	else
		write(STDERR_FILENO, datash->args[0],
		      getStringLength(datash->args[0]));

	datash->status = 0;
	return (1);
}
