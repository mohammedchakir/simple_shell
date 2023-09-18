#include "main.h"

 
void rev_string(char *s)
{
	int ctr = 0;
	int n, m;
	char *_str, tem;

	while (ctr >= 0)
	{
		if (s[ctr] == '\0')
			break;
		ctr++;
	}
	_str = s;
	for (n = 0; n < (ctr - 1); n++)
	{
		for (m = n + 1; m > 0; m--)
		{
			tem = *(_str + m);
			*(_str + m) = *(_str + (m - 1));
			*(_str + (m - 1)) = tem;
		}
	}
}
/**
 * char_repeat - Counts the repetitions of a character in a string.
 * @input: The input string.
 * @n: The character index to check.
 * Return: The number of times the character repeats.
 */
int char_repeat(char *input, int n)
{
	if (*(input - 1) == *input)
		return (char_repeat(input - 1, n + 1));

	return (n);
}

/**
 * syntax_err_op - Searches for syntax errors in the input.
 * @input: The input string.
 * @n: The current index in the string.
 * @last: The last character that was read.
 * Return: The index of the error position or 0 if no error is found.
 */
int syntax_err_op(char *input, int n, char last)
{
	int ctr;

	ctr = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syntax_err_op(input + 1, n + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (n);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (n);
		if (last == '|')
		{
			ctr = char_repeat(input, 0);
			if (ctr == 0 || ctr > 1)
				return (n);
		}
	}
	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (n);
		if (last == '&')
		{
			ctr = char_repeat(input, 0);
			if (ctr == 0 || ctr > 1)
				return (n);
		}
	}
	return (syntax_err_op(input + 1, n + 1, *input));
}

/**
 * fst_char - Finds the index of the first non-whitespace character.
 * @input: The input string.
 * @n: The starting index for the search.
 * Return: 1 if a non-whitespace character is found, 0 otherwise.
 */
int fst_char(char *input, int *n)
{

	for (*n = 0; input[*n]; *n += 1)
	{
		if (input[*n] == ' ' || input[*n] == '\t')
			continue;
		if (input[*n] == ';' || input[*n] == '|' || input[*n] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * syntax_err_printer - Prints an error message when a syntax error is found.
 * @datash: Shell information.
 * @input: The input string.
 * @n: The position of the error.
 * @m: Controls whether to print the error message.
 * Return: None.
 */
void syntax_err_printer(data_shell *datash, char *input, int n, int m)
{
	char *msg, *msg2, *msg3, *err, *count;
	int lenght;

	if (input[n] == ';')
	{
		if (m == 0)
			msg = (input[n + 1] == ';' ? ";;" : ";");
		else
			msg = (input[n - 1] == ';' ? ";;" : ";");
	}
	if (input[n] == '|')
		msg = (input[n + 1] == '|' ? "||" : "|");
	if (input[n] == '&')
		msg = (input[n + 1] == '&' ? "&&" : "&");
	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	count = aux_itoa(datash->counter);
	lenght = _strlen(datash->av[0]) + _strlen(count);
	lenght += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;
	err = malloc(sizeof(char) * (lenght + 1));
	if (err == 0)
	{
		free(count);
		return;
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, count);
	_strcat(err, msg2);
	_strcat(err, msg);
	_strcat(err, msg3);
	_strcat(err, "\0");
	write(STDERR_FILENO, err, lenght);
	free(err);
	free(count);
}



