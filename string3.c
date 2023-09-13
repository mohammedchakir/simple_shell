#include "main.h"
/**
 * rev_string - reverses a string.
 * @s: string.
 * Return: Non
 */
void rev_string(char *s)
{
	int counter = 0;
	int i, j;
	char *_str, tem;

	while (counter >= 0)
	{
		if (s[counter] == '\0')
			break;
		counter++;
	}
	_str = s;
	for (i = 0; i < (counter - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			tem = *(_str + j);
			*(_str + j) = *(_str + (j - 1));
			*(_str + (j - 1)) = tem;
		}
	}
}
