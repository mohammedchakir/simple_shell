#include "main.h"

/**
 * change_dir - changes current working directory
 * @datash: data relevant
 * Return: 1 on success
 */
int change_dir(data_shell *datash)
{
	char *dir;
	int home, home2, dash;

	dir = datash->args[1];
	if (dir != NULL)
	{
		home = _strcmp("$HOME", dir);
		home2 = _strcmp("~", dir);
		dash = _strcmp("--", dir);
	}
	if (dir == NULL || !home || !home2 || !dash)
	{
		cd_home(datash);
		return (1);
	}
	if (_strcmp("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		par_cd(datash);
		return (1);
	}
	cd_to(datash);
	return (1);
}
