#include "main.h"

/**
 * read_line - funtion reads the input string.
 * @i_eof: the return value of getline.
 * Return: the input string.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
