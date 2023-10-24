#include "main.h"

/**
 * rev_string - function reverses a string.
 * @s: the input string.
 * Return: no return printed.
 */
void rev_string(char *s)
{
	int count = 0, n, m;
	char *str, tmp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (n = 0; n < (count - 1); n++)
	{
		for (m = n + 1; m > 0; m--)
		{
			tmp = *(str + m);
			*(str + m) = *(str + (m - 1));
			*(str + (m - 1)) = tmp;
		}
	}
}
