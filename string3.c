#include "main.h"

/**
 * rev_string - Reverses the characters in a string.
 * @s: The string to be reversed.
 * Return: Void.
 */
void rev_string(char *s)
{
	int ctr = 0;
	int n, m;
	char *_str, tem;

	while (ctr >= 0)
	{
		if (s[ctr] == '\0')
			break;
		ctr++;
	}
	_str = s;
	for (n = 0; n < (ctr - 1); n++)
	{
		for (m = n + 1; m > 0; m--)
		{
			tem = *(_str + m);
			*(_str + m) = *(_str + (m - 1));
			*(_str + (m - 1)) = tem;
		}
	}
}
