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

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
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
 * Return: A pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
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
	int n, m, bool;

	for (n = 0; *(s + n) != '\0'; n++)
	{
		bool = 1;
		for (m = 0; *(accept + m) != '\0'; m++)
		{
			if (*(s + n) == *(accept + m))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}

	return (n);
}
