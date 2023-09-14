#include "main.h"

/**
 * get_len - Determines the length of an integer.
 * @i: The integer to measure.
 * Return: The length of the integer.
 */
int get_len(int i)
{
	unsigned int num;
	int length = 1;

	if (i < 0)
	{
		length++;
		num = i * -1;
	}
	else
		num = i;
	while (num > 9)
	{
		length++;
		num = num / 10;
	}
	return (length);
}
/**
 * aux_itoa - Converts an integer to a string representation.
 * @i: The integer to be converted.
 * Return: The resulting string.
 */
char *aux_itoa(int i)
{
	unsigned int num;
	int length = get_len(n);
	char *buff;

	buff = malloc(sizeof(char) * (length + 1));
	if (buff == 0)
		return (NULL);
	*(buff + length) = '\0';
	if (i < 0)
	{
		num = i * -1;
		buff[0] = '-';
	}
	else
		num = i;
	length--;
	do {
		*(buff + length) = (num % 10) + '0';
		num = num / 10;
		length--;
	}
	while (num > 0)
		;
	return (buff);
}
/**
 * _atoi - Converts a string to an integer.
 * @s: The input string.
 * Return: The integer value parsed from the string.
 */
int _atoi(char *s)
{
	unsigned int ctr = 0, size = 0;
	int final = 0, sign = 1, power = 1;
	unsigned int n;

	while (*(s + ctr) != '\0')
	{
		if (size > 0 && (*(s + ctr) < '0' || *(s + ctr) > '9'))
			break;
		if (*(s + ctr) == '-')
			sign *= -1;
		if ((*(s + ctr) >= '0') && (*(s + ctr) <= '9'))
		{
			if (size > 0)
				power *= 10;
			size++;
		}
		ctr++;
	}
	for (n = ctr - size; n < ctr; n++)
	{
		final = final + ((*(s + n) - 48) * power);
		power /= 10;
	}
	return (final * sign);
}
