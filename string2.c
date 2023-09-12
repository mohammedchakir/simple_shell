#include "main.h"

/**
 * duplicateString - Duplicates a string.
 * @s: Pointer to the string to be duplicated.
 * Return: Pointer to the new duplicated string.
 */
char *duplicateString(const char *s)
{
	char *n;
	size_t length;

	length = getStringLength(s);
	n = malloc(sizeof(char) * (length + 1));
	if (n == NULL)
		return (NULL);
	copyData(n, s, length + 1);
	return (n);
}

/**
 * getStringLength - Calculate the length of a string.
 * @s: Pointer to the string.
 * Return: The length of the string.
 */
int getStringLength(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * compareStrings - Compares two strings.
 * @str: The input string.
 * @delim: The delimiter string.
 * Return: 1 if equal, 0 if not equal.
 */
int compareStrings(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * tokenizeString - Splits a string into tokens using a delimiter.
 * @str: The input string.
 * @delim: The delimiter string.
 * Return: Pointer to the tokenized string.
 */
char *tokenizeString(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_begin;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (compareStrings(str, delim))
			return (NULL);
		splitted = str;
		i = getStringLength(str);
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
 * isDigit - Checks if a character is a digit.
 * @s: The character to check.
 * Return: 1 if it's a digit, 0 otherwise.
 */
int isDigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
