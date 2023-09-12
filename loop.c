#include "main.h"

/**
 * removeComments - Eliminates comments from the input.
 *
 * @in: The input string containing comments.
 * Return: The input string with comments removed.
 */
char *removeComments(char *in)
{
	int i, position;

	position = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				position = i;
		}
	}
	if (position != 0)
	{
		in = _realloc(in, i, position + 1);
		in[position] = '\0';
	}
	return (in);
}

/**
 * shellLoop - Implements the main shell loop.
 * @datash: Shell-related information.
 * Return: No return value.
 */
void shellLoop(data_shell *datash)
{
	int lp, i_eof;
	char *inp;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "--> ", 4);
		inp = _readline(&i_eof);
		if (i_eof != -1)
		{
			inp = remove_comment(inp);
			if (inp == NULL)
				continue;

			if (syntax_err_checker(datash, inp) == 1)
			{
				datash->status = 2;
				free(inp);
				continue;
			}
			inp = replace_var(inp, datash);
			lp = command_split(datash, inp);
			datash->counter += 1;
			free(inp);
		}
		else
		{
			lp = 0;
			free(inp);
		}
	}
}

/**
 * readInput - Reads input data.
 * @i_eof: Return value of the getline function.
 * Return: Input data as a string.
 */
char *readInput(int *i_eof)
{
	char *inp = NULL;
	size_t size = 0;

	*i_eof = getline(&inp, &size, stdin);

	return (inp);
}
