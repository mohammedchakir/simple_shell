#include "main.h"

/**
 * cd_shell - function changes current directory.
 * @datash: the data relevant.
 * Return: 1 on success.
 */
int cd_shell(data_shell *datash)
{
	char *directory;
	int ishome1, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome1 = _strcmp("$HOME", directory);
		ishome2 = _strcmp("~", directory);
		isddash = _strcmp("--", directory);
	}

	if (dir == NULL || !ishome1 || !ishome2 || !isddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
