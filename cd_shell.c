#include "main.h"

/**
 * changedir - Changes the current working directory.
 * @datash: Relevant data.
 * Return: 1 if successful.
 */
int changedir(data_shell *datash)
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
		cdhome(datash);
		return (1);
	}
	if (compareStrings("-", dir) == 0)
	{
		cdprev(datash);
		return (1);
	}
	if (compareStrings(".", dir) == 0 || compareStrings("..", dir) == 0)
	{
		parcd(datash);
		return (1);
	}
	cdto(datash);
	return (1);
}
