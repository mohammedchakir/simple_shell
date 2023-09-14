#include "main.h"

/**
 * remove_comment - Removes comments from the input.
 * @in: The input string.
 * Return: The input string with comments removed.
 */
char *remove_comment(char *in)
{
	int i, pos;

	pos = 0;
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
				pos = i;
		}
	}
	if (pos != 0)
	{
		in = _realloc(in, i, pos + 1);
		in[pos] = '\0';
	}
	return (in);
}

/**
 * loop_shell - The main shell loop.
 * @datash: Shell information.
 * Return: No return value.
 */
void loop_shell(data_shell *datash)
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
 * _readline - Reads input from the user.
 * @i_eof: Return value of the getline function.
 * Return: The user's input as a string.
 */
char *_readline(int *i_eof)
{
	char *inp = NULL;
	size_t size = 0;

	*i_eof = getline(&inp, &size, stdin);

	return (inp);
}
