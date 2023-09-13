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
		home = compareStrings("$HOME", dir);
		home2 = compareStrings("~", dir);
		dash = compareStrings("--", dir);
	}
	if (dir == NULL || !home || !home2 || !dash)
	{
		cd_home(datash);
		return (1);
	}
	if (compareStrings("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}
	if (compareStrings(".", dir) == 0 || compareStrings("..", dir) == 0)
	{
		par_cd(datash);
		return (1);
	}
	cd_to(datash);
	return (1);
}
