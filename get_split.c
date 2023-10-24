#include "main.h"

/**
 * swap_char - function swaps | and & for non-printed chars.
 * @input: the input string.
 * @bool: the type of swap.
 * Return: the swapped string.
 */
char *swap_char(char *input, int bool)
{
	int n;

	if (bool == 0)
	{
		for (n = 0; input[n]; n++)
		{
			if (input[n] == '|')
			{
				if (input[n + 1] != '|')
					input[n] = 16;
				else
					n++;
			}

			if (input[n] == '&')
			{
				if (input[n + 1] != '&')
					input[n] = 12;
				else
					n++;
			}
		}
	}
	else
	{
		for (n = 0; input[n]; n++)
		{
			input[n] = (input[n] == 16 ? '|' : input[n]);
			input[n] = (input[n] == 12 ? '&' : input[n]);
		}
	}
	return (input);
}

/**
 * add_nodes - append separators and command lines in the lists.
 * @head_s: the head of separator list.
 * @head_l: the head of command lines list.
 * @input: the input string.
 * Return: no return printed.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int n;
	char *line;

	input = swap_char(input, 0);

	for (n = 0; input[n]; n++)
	{
		if (input[n] == ';')
			add_sep_node_end(head_s, input[n]);

		if (input[n] == '|' || input[n] == '&')
		{
			add_sep_node_end(head_s, input[n]);
			n++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - function goes to next command line stored.
 * @list_s: the separator list.
 * @list_l: the command line list.
 * @datash: the data structure.
 * Return: no return printed.
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - function splits command lines according to
 * the separators ;, | and &, and executes them.
 * @datash: the data structure.
 * @input: the input string.
 * Return: 0 to exit, 1 to continue.
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - function tokenizes the input string.
 * @input: the input string.
 * Return: the string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t n;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (n = 1; token != NULL; n++)
	{
		if (n == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, n, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[n] = token;
	}

	return (tokens);
}
