#include "main.h"

/**
 * remove_comment - Removes all comments from the input.
 * @in: The input string.
 * Return: The input string with comments removed.
 */
char *remove_comment(char *in)
{
	int n, pos;

	pos = 0;
	for (n = 0; in[n]; n++)
	{
		if (in[n] == '#')
		{
			if (n == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[n - 1] == ' ' || in[n - 1] == '\t' || in[n - 1] == ';')
				pos = n;
		}
	}
	if (pos != 0)
	{
		in = _realloc(in, n, pos + 1);
		in[pos] = '\0';
	}
	return (in);
}

/**
 * loop_shell - The main shell loop.
 * @datash: current shell informations.
 * Return: No return value.
 */
void loop_shell(data_shell *datash)
{
	int lp, i_eof;
	char *input;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "--> ", 4);
		input = _readline(&i_eof);
		if (i_eof != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (syntax_err_checker(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, datash);
			lp = command_split(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			lp = 0;
			free(input);
		}
	}
}

/**
 * _readline - Reads input line from the user.
 * @i_eof: Return value of the getline function.
 * Return: The user's input as a string.
 */
char *_readline(int *i_eof)
{
	char *input = NULL;
	size_t size = 0;

	*i_eof = getline(&input, &size, stdin);

	return (input);
}
