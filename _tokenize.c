#include "main.h"

/**
 * swapchar - Swaps the characters '|' and '&' in the input string.
 * @input: The input string to perform the swap on.
 * @bool: The type of swap to perform.
 * Return: The input string with the specified characters swapped.
 */
char *swapchar(char *input, int bool)
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
 * addnodes - Adds separators and command lines to their respective lists.
 * @head_s: The head of the separator list.
 * @head_l: The head of the command lines list.
 * @input: The input to be processed.
 * Return: None.
 */
void addnodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line_ptr;

	input = swapchar(input, 0);

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
		line_ptr = swapchar(line_ptr, 1);
		appendLineToEnd(head_l, line_ptr);
		line_ptr = tokenizeString(NULL, ";|&");
	}

	while (line_ptr != NULL);
}

/**
 * nextcmdline - Proceed to the next command line.
 * @list_s: The separator list.
 * @list_l: The command line list.
 * @datash: Shell information.
 * Return: None.
 */
void nextcmdline(sep_list **list_s, line_list **list_l, data_shell *datash)
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
 * cmdsplit - Splits command lines into components.
 * @datash: Shell information.
 * @input: The input to be processed.
 * Return: 0 if successful, 1 if there was an error.
 */
int cmdsplit(data_shell *datash, char *input)
{

	sep_list *head_sep, *list_sep;
	line_list *head_line, *list_line;
	int lp;

	head_sep = NULL;
	head_line = NULL;
	addnodes(&head_sep, &head_line, input);
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
		nextcmdline(&list_sep, &list_line, datash);

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
 * tokenizeline - Tokenizes the input string.
 * @input: The input string to be tokenized.
 * Return: A collection of tokens obtained from the input string.
 */
char **tokenizeline(char *input)
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
