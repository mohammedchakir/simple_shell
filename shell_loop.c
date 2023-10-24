#include "main.h"

/**
 * without_comment - function deletes comments from the input.
 * @input: the input string.
 * Return: the input without comments.
 */
char *without_comment(char *input)
{
	int n, up_to;

	up_to = 0;
	for (n = 0; input[n]; n++)
	{
		if (input[n] == '#')
		{
			if (n == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[n - 1] == ' ' || input[n - 1] == '\t' || input[n - 1] == ';')
				up_to = n;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, n, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * shell_loop - the loop function of shell.
 * @datash: the data relevant.
 * Return: no return printed.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
