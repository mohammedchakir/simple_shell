#include "main.h"

/**
 * repeated_char - function counts the repetitions of a char.
 * @input: the input string.
 * @n: the index.
 * Return: the repetitions.
 */
int repeated_char(char *input, int n)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, n + 1));

	return (n);
}

/**
 * error_sep_op - function finds syntax errors.
 * @input: the input string.
 * @n: the index.
 * @last: the last character to read.
 * Return: the index of error. 0 when there are no errors.
 */
int error_sep_op(char *input, int n, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, n + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (n);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (n);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (n);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (n);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (n);
		}
	}

	return (error_sep_op(input + 1, n + 1, *input));
}

/**
 * first_char - function finds index of the first character.
 * @input: the input string.
 * @n: the index.
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *n)
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
 * print_syntax_error - function prints when a syntax error is found.
 * @datash: the data structure.
 * @input: the input string.
 * @n: the index of the error.
 * @bool: the control msg error.
 * Return: no return printed.
 */
void print_syntax_error(data_shell *datash, char *input, int n, int bool)
{
	char *msg, *msg2, *msg3, *err, *count;
	int len;

	if (input[n] == ';')
	{
		if (bool == 0)
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
	len = _strlen(datash->av[0]) + _strlen(count);
	len += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	err = malloc(sizeof(char) * (len + 1));
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

	write(STDERR_FILENO, err, len);
	free(err);
	free(count);
}

/**
 * check_syntax_error - the intermediate function to
 * find and print a syntax error.
 * @datash: the data structure.
 * @input: the input string.
 * Return: 1 if there is an error. 0 in other case.
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int n = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	n = error_sep_op(input + begin, 0, *(input + begin));
	if (n != 0)
	{
		print_syntax_error(datash, input, begin + n, 1);
		return (1);
	}

	return (0);
}
