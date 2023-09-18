#include "main.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * Return: The combined string.
 */
char *_strcat(char *dest, const char *src)
{
	int n;
	int m;

	for (n = 0; dest[n] != '\0'; n++)
		;
	for (m = 0; src[m] != '\0'; m++)
	{
		dest[n] = src[m];
		n++;
	}
	dest[n] = '\0';
	return (dest);
}

/**
 * *_strcpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{

	size_t n;

	for (n = 0; src[n] != '\0'; n++)
		dest[n] = src[n];
	dest[n] = '\0';
	return (dest);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if equal, 1 if s1 is greater, -1 if s2 is greater.
 */
int _strcmp(char *s1, char *s2)
{
	int n;

	for (n = 0; s1[n] == s2[n] && s1[n]; n++)
		;
	if (s1[n] > s2[n])
		return (1);
	if (s1[n] < s2[n])
		return (-1);
	return (0);
}

/**
 * _strchr - Searches for a character in a string.
 * @s: The string to search in.
 * @c: The character to find.
 * Return: A pointer to first occurence of char in string or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int n = 0;

	for (; *(s + n) != '\0'; n++)
		if (*(s + n) == c)
			return (s + n);
	if (*(s + n) == c)
		return (s + n);
	return ('\0');
}

/**
 * _strspn - Computes the length of a substring.
 * @s: The initial segment.
 * @accept: The set of allowed bytes.
 * Return: The number of allowed bytes at the beginning of s.
 */
int _strspn(char *s, char *accept)
{
	int n, m, l;

	for (n = 0; *(s + n) != '\0'; n++)
	{
		l = 1;
		for (m = 0; *(accept + m) != '\0'; m++)
		{
			if (*(s + n) == *(accept + m))
			{
				l = 0;
				break;
			}
		}
		if (l == 1)
			break;
	}

	return (n);
}
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
 * Return: The next token from the input string, or NULL if no tokens found.
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
		n = _strlen(str);
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
/**
 * rev_string - Reverses the characters in a string.
 * @s: The string to be reversed.
 * Return: None.
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
