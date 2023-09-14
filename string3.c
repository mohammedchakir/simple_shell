#include "main.h"

/**
 * rev_string - Reverses the characters in a string.
 * @s: The string to be reversed.
 * Return: None.
 */
void rev_string(char *s)
{
	int counter = 0;
	int n, m;
	char *_str, tem;

	while (counter >= 0)
	{
		if (s[counter] == '\0')
			break;
		counter++;
	}
	_str = s;
	for (n = 0; n < (counter - 1); n++)
	{
		for (m = n + 1; m > 0; m--)
		{
			tem = *(_str + m);
			*(_str + m) = *(_str + (m - 1));
			*(_str + (m - 1)) = tem;
		}
	}
}
