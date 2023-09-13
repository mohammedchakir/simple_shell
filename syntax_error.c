#include "main.h"

/**
 * charRepetitions - Counts the number of repetitions of a character.
 *
 * @input: The input string.
 * @i: The index to check.
 * Return: The number of repetitions.
 */
int charRepetitions(char *input, int i)
{
	if (*(input - 1) == *input)
		return (charRepetitions(input - 1, i + 1));

	return (i);
}

/**
 * syntaxErrorPosition - Searches for syntax errors in input.
 * @input: The input string.
 * @i: The current index to check.
 * @last: The last character that was read.
 * Return: The index of the error position or 0 if none is found.
 */
int syntaxErrorPosition(char *input, int i, char last)
{
	int counter;

	counter = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syntaxErrorPosition(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);
		if (last == '|')
		{
			counter = charRepetitions(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}
	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);
		if (last == '&')
		{
			counter = charRepetitions(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}
	return (syntaxErrorPosition(input + 1, i + 1, *input));
}

/**
 * firstChar - Locates the index of the first character in a string.
 * @input: The input string.
 * @i: The starting index for the search.
 * Return: 1 if found, 0 if not found.
 */
int firstChar(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * printSyntaxError - Outputs an error message when a syntax error is encountered.
 * @datash: Shell-related information.
 * @input: The input string.
 * @i: The position of the error.
 * @bool: Controls whether to display the error message.
 * Return: None.
 */
void printSyntaxError(data_shell *datash, char *input, int i, int bool)
{
	char *message, *message2, *message3, *err, *count;
	int len;

	if (input[i] == ';')
	{
		if (bool == 0)
			message = (input[i + 1] == ';' ? ";;" : ";");
		else
			message = (input[i - 1] == ';' ? ";;" : ";");
	}
	if (input[i] == '|')
		message = (input[i + 1] == '|' ? "||" : "|");
	if (input[i] == '&')
		message = (input[i + 1] == '&' ? "&&" : "&");
	message2 = ": Syntax error: \"";
	message3 = "\" unexpected\n";
	count = aux_itoa(datash->counter);
	len = getStringLength(datash->av[0]) + getStringLength(count);
	len += getStringLength(message) + getStringLength(message2) + getStringLength(message3) + 2;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(count);
		return;
	}
	copyString(err, datash->av[0]);
	concatenateStrings(err, ": ");
	concatenateStrings(err, count);
	concatenateStrings(err, message2);
	concatenateStrings(err, message);
	concatenateStrings(err, message3);
	concatenateStrings(err, "\0");
	write(STDERR_FILENO, err, len);
	free(err);
	free(count);
}

/**
 * checkSyntaxError - Identifies and displays syntax errors.
 * @datash: Shell-related information.
 * @input: The input string.
 * Return: 1 if a syntax error is found, 0 otherwise.
 */
int checkSyntaxError(data_shell *datash, char *input)
{
	int start = 0;
	int first_char = 0;
	int i = 0;

	first_char = firstChar(input, &start);
	if (first_char == -1)
	{
		printSyntaxError(datash, input, start, 0);
		return (1);
	}
	i = syntaxErrorPosition(input + start, 0, *(input + start));
	if (i != 0)
	{
		printSyntaxError(datash, input, start + i, 1);
		return (1);
	}
	return (0);
}
