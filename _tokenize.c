#include "main.h"

/**
 * char_swap - Swaps the characters '|' and '&' in the input string.
 * @input: The input string to perform the swap on.
 * @bool: The type of swap to perform.
 * Return: The input string with the specified characters swapped.
 */
char *char_swap(char *input, int bool)
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
 * add_nodes - Adds separators and command lines to their respective lists.
 * @head_s: The head of the separator list.
 * @head_l: The head of the command lines list.
 * @input: The input to be processed.
 * Return: None.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int n;
	char *line_ptr;

	input = char_swap(input, 0);

	for (n = 0; input[n]; n++)
	{
		if (input[n] == ';')
			add_sep_end(head_s, input[n]);

		if (input[n] == '|' || input[n] == '&')
		{
			add_sep_end(head_s, input[n]);
			n++;
		}
	}
	line_ptr = _strtok(input, ";|&");
	do {
		line_ptr = char_swap(line_ptr, 1);
		add_line_end(head_l, line_ptr);
		line_ptr = _strtok(NULL, ";|&");
	}

	while (line_ptr != NULL);
}

/**
 * next_cmd_line - Proceed to the next command line.
 * @list_s: The separator list.
 * @list_l: The command line list.
 * @datash: Shell information.
 * Return: None.
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
 * command_split - Splits command lines into components.
 * @datash: Shell information.
 * @input: The input to be processed.
 * Return: 0 if successful, 1 if there was an error.
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
	sep_list_free(&head_sep);
	line_list_free(&head_line);
	if (lp == 0)
		return (0);
	return (1);
}

/**
 * tokenize_line - Tokenizes the input string.
 * @input: The input string to be tokenized.
 * Return: A collection of tokens obtained from the input string.
 */
char **tokenize_line(char *input)
{
	size_t size;
	size_t n;
	char **token_arr;
	char *token;

	size = TOK_BUFSIZE;
	token_arr = malloc(sizeof(char *) * (size));
	if (token_arr == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOK_DELIM);
	token_arr[0] = token;
	for (n = 1; token != NULL; n++)
	{
		if (n == size)
		{
			size += TOK_BUFSIZE;
			token_arr = _reallocdp(token_arr, n, sizeof(char *) * size);
			if (token_arr == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		token_arr[n] = token;
	}
	return (token_arr);
}
