#include "main.h"

/**
 * get_len - gets length of int
 * @n: the integer
 * Return: The length
 */
int get_len(int n)
{
	unsigned int num;
	int length = 1;

	if (n < 0)
	{
		length++;
		num = n * -1;
	}
	else
		num = n;
	while (num > 9)
	{
		length++;
		num = num / 10;
	}
	return (length);
}
/**
 * aux_itoa - to int to string.
 * @n: the integer
 * Return: the string
 */
char *aux_itoa(int n)
{
	unsigned int num;
	int length = get_len(n);
	char *buff;

	buff = malloc(sizeof(char) * (length + 1));
	if (buff == 0)
		return (NULL);
	*(buff + length) = '\0';
	if (n < 0)
	{
		num = n * -1;
		buff[0] = '-';
	}
	else
		num = n;
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
 * _atoi - string to integer.
 * @s: string.
 * Return: integer
 */
int _atoi(char *s)
{
	unsigned int counter = 0, size = 0;
	int final = 0, sign = 1, power = 1;
	unsigned int i;

	while (*(s + counter) != '\0')
	{
		if (size > 0 && (*(s + counter) < '0' || *(s + counter) > '9'))
			break;
		if (*(s + counter) == '-')
			sign *= -1;
		if ((*(s + counter) >= '0') && (*(s + counter) <= '9'))
		{
			if (size > 0)
				power *= 10;
			size++;
		}
		counter++;
	}
	for (i = counter - size; i < counter; i++)
	{
		final = final + ((*(s + i) - 48) * power);
		power /= 10;
	}
	return (final * sign);
}
