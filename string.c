#include "main.h"

/**
 * concatenateStrings - Combines two strings.
 * @dest: The first string.
 * @src: The second string.
 * Return: The concatenated strings.
 */
char *concatenateStrings(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * copyString - Copies a string.
 * @dest: The first string.
 * @src: The second string.
 * Return: The destination string.
 */
char *copyString(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * compareStrings - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if equal, 1 if the first is greater, -1 if the second is greater.
 */
int compareStrings(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * findCharacter - Searches for a character in a string.
 * @s: The input string.
 * @c: The character to search for.
 * Return: Pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *findCharacter(char *s, char c)
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
 * countAcceptedBytes - Calculates the length of the initial segment containing only allowed bytes.
 * @s: The initial segment to check.
 * @accept: The set of bytes that are allowed.
 * Return: The number of allowed bytes in the initial segment.
 */
int countAcceptedBytes(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}

	return (i);
}
