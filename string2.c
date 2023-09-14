#include "main.h"

/**
 * _strdup - Duplicates a string.
 * @s: Pointer to the string to be duplicated.
 * Return: A pointer to the newly created duplicate string.
 */
char *_strdup(const char *s)
{
	char *n;
	size_t len;

	len = _strlen(s);
	n = malloc(sizeof(char) * (len + 1));
	if (n == NULL)
		return (NULL);
	_memcpy(n, s, len + 1);
	return (n);
}

/**
 * _strlen - Computes the length of a string.
 * @s: Pointer to the string.
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
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
	unsigned int n, m;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		m = _strlen(str);
		str_end = &str[n];
	}
	str_begin = splitted;
	if (str_begin == str_end)
		return (NULL);
	for (m = 0; *splitted; splitted++)
	{
		if (splitted != str_begin)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (n = 0; delim[n]; n++)
		{
			if (*splitted == delim[n])
			{
				*splitted = '\0';
				if (splitted == str_begin)
					str_begin++;
				break;
			}
		}
		if (m == 0 && *splitted)
			m = 1;
	}
	if (m == 0)
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
