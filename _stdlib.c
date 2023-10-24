#include "main.h"

/**
 * get_len - gets the lenght of a number.
 * @n: the type int number.
 * Return: the lenght of a number.
 */
int get_len(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}

	return (len);
}
/**
 * aux_itoa - the function converts int to string.
 * @n: the type int number.
 * Return: the string.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int len = get_len(n);
	char *buff;

	buff = malloc(sizeof(char) * (len + 1));
	if (buff == 0)
		return (NULL);

	*(buff + len) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = n;
	}

	len--;
	do {
		*(buff + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (buff);
}

/**
 * _atoi - the function converts a string to an integer.
 * @s: the input string.
 * Return: the integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, n;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (n = count - size; n < count; n++)
	{
		oi = oi + ((*(s + n) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
