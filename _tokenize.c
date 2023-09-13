#include "main.h"

/**
 * char_swap - swaps | and &
 * @input: input
 * @bool: swap type
 * Return: swapped input
 */
char *char_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command in the lists
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input
 * Return: Non
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line_ptr;

	input = char_swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			addSeparatorAtEnd(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			addSeparatorAtEnd(head_s, input[i]);
			i++;
		}
	}
	line_ptr = tokenizeString(input, ";|&");
	do {
		line_ptr = char_swap(line_ptr, 1);
		appendLineToEnd(head_l, line_ptr);
		line_ptr = tokenizeString(NULL, ";|&");
	}

	while (line_ptr != NULL);
}

/**
 * next_cmd_line - move to the next cmd line
 * @list_s: separator list
 * @list_l: command line list
 * @datash: shell info
 * Return: Non
 */
void next_cmd_line(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int lp_sep;
	sep_list *ls_sep;
	line_list *ls_line;

	lp_sep = 1;
	ls_sep = *list_s;
	ls_line = *list_l;

	while (ls_sep != NULL && lp_sep)
	{
		if (datash->status == 0)
		{
			if (ls_sep->separator == '&' || ls_sep->separator == ';')
				lp_sep = 0;
			if (ls_sep->separator == '|')
				ls_line = ls_line->next, ls_sep = ls_sep->next;
		}
		else
		{
			if (ls_sep->separator == '|' || ls_sep->separator == ';')
				lp_sep = 0;
			if (ls_sep->separator == '&')
				ls_line = ls_line->next, ls_sep = ls_sep->next;
		}
		if (ls_sep != NULL && !lp_sep)
			ls_sep = ls_sep->next;
	}
	*list_s = ls_sep;
	*list_l = ls_line;
}

/**
 * command_split - splits command lines
 * @datash: shell info
 * @input: input
 * Return: 0 or 1
 */
int command_split(data_shell *datash, char *input)
{

	sep_list *head_sep, *list_sep;
	line_list *head_line, *list_line;
	int lp;

	head_sep = NULL;
	head_line = NULL;
	add_nodes(&head_sep, &head_line, input);
	list_sep = head_sep;
	list_line = head_line;
	while (list_line != NULL)
	{
		datash->input = list_line->line;
		datash->args = tokenize_line(datash->input);
		lp = execute_line(datash);
		free(datash->args);
		if (lp == 0)
			break;
		next_cmd_line(&list_sep, &list_line, datash);

		if (list_line != NULL)
			list_line = list_line->next;
	}
	freeSeparatorList(&head_sep);
	freeLineList(&head_line);
	if (lp == 0)
		return (0);
	return (1);
}

/**
 * tokenize_line - tokenize the string
 * @input: input
 * Return: splitted string.
 */
char **tokenize_line(char *input)
{
	size_t size;
	size_t i;
	char **token_arr;
	char *token;

	size = TOK_BUFSIZE;
	token_arr = malloc(sizeof(char *) * (size));
	if (token_arr == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = tokenizeString(input, TOK_DELIM);
	token_arr[0] = token;
	for (i = 1; token != NULL; i++)
	{
		if (i == size)
		{
			size += TOK_BUFSIZE;
			token_arr = resizeDblePtrMem(token_arr, i, sizeof(char *) * size);
			if (token_arr == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = tokenizeString(NULL, TOK_DELIM);
		token_arr[i] = token;
	}
	return (token_arr);
}
