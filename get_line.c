#include "main.h"

/**
 * bring_line - function assigns the line var for get_line.
 * @lineptr: the Buffer that store the input string.
 * @buffer: the string that is been called to line.
 * @n: the size of line.
 * @m: the size of buffer.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t m)
{

	if (*lineptr == NULL)
	{
		if  (m > BUFSIZE)
			*n = m;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < m)
	{
		if (m > BUFSIZE)
			*n = m;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - function Read inpt from stream.
 * @lineptr: the buffer that stores the input.
 * @n: the size of lineptr.
 * @stream: the stream to read from.
 * Return: The number of bytes.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int b;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		b = read(STDIN_FILENO, &t, 1);
		if (b == -1 || (b == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (b == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (b != 0)
		input = 0;
	return (retval);
}
