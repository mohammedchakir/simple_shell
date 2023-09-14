#include "main.h"

/**
 * _strdup - Duplicates a string.
 * @s: Pointer to the string to be duplicated.
 * Return: A pointer to the newly created duplicate string.
 */
char *_strdup(const char *s)
{
	char *n;
	size_t length;

	length = _strlen(s);
	n = malloc(sizeof(char) * (length + 1));
	if (n == NULL)
		return (NULL);
	_memcpy(n, s, length + 1);
	return (n);
}

/**
 * _strlen - Computes the length of a string.
 * @s: Pointer to the string.
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - Compares two strings.
 * @str: The string to compare.
 * @delim: The delimiter string.
 * Return: 1 if the strings match, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int n, m, l;

	for (n = 0, l = 0; str[n]; n++)
	{
		for (m = 0; delim[m]; m++)
		{
			if (str[n] == delim[m])
			{
				l++;
				break;
			}
		}
	}
	if (n == l)
		return (1);
	return (0);
}

/**
 * _strtok - Splits a string into tokens using a delimiter.
 * @str: The input string.
 * @delim: The delimiter string.
 * Return: The next token from the input string, or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_begin;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_begin = splitted;
	if (str_begin == str_end)
		return (NULL);
	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_begin)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_begin)
					str_begin++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_begin);
}

/**
 * _isdigit - Checks if a string contains digits.
 * @s: The string to check.
 * Return: 1 if the string contains only digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int n;

	for (n = 0; s[n]; n++)
	{
		if (s[n] < 48 || s[n] > 57)
			return (0);
	}
	return (1);
}
