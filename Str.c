#include "main.h"


 



 * Return: A pointer to first occurence of char in string or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int n = 0;

	for (; *(s + n) != '\0'; n++)
		if (*(s + n) == c)
			return (s + n);
	if (*(s + n) == c)
		return (s + n);
	return ('\0');
}

/**
 * _strspn - Computes the length of a substring.
 * @s: The initial segment.
 * @accept: The set of allowed bytes.
 * Return: The number of allowed bytes at the beginning of s.
 */
int _strspn(char *s, char *accept)
{
	int n, m, l;

	for (n = 0; *(s + n) != '\0'; n++)
	{
		l = 1;
		for (m = 0; *(accept + m) != '\0'; m++)
		{
			if (*(s + n) == *(accept + m))
			{
				l = 0;
				break;
			}
		}
		if (l == 1)
			break;
	}

	return (n);
}

 * @s: Pointer to the string to be duplicated.
 * Return: A pointer to the newly created duplicate string.
 */
char *_strdup(const char *s)
{
	char *n;
	size_t len;

	len = _strlen(s);
	n = malloc(sizeof(char) * (len + 1));
	if (n == NULL)
		return (NULL);
	_memcpy(n, s, len + 1);
	return (n);
}

/**
 * _strlen - Computes the length of a string.
 * @s: Pointer to the string.
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - Compares two strings.
 * @str: The string to compare.
 * @delim: The delimiter string.
 * Return: 1 if the strings match, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int n, m, l;

	for (n = 0, l = 0; str[n]; n++)
	{
		for (m = 0; delim[m]; m++)
		{
			if (str[n] == delim[m])
			{
				l++;
				break;
			}
		}
	}
	if (n == l)
		return (1);
	return (0);
}

/**
 * _strtok - Splits a string into tokens using a delimiter.
 * @str: The input string.
 * @delim: The delimiter string.
 * Return: The next token from the input string, or NULL if no tokens found.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_begin;
	unsigned int n, m;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		n = _strlen(str);
		str_end = &str[n];
	}
	str_begin = splitted;
	if (str_begin == str_end)
		return (NULL);
	for (m = 0; *splitted; splitted++)
	{
		if (splitted != str_begin)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (n = 0; delim[n]; n++)
		{
			if (*splitted == delim[n])
			{
				*splitted = '\0';
				if (splitted == str_begin)
					str_begin++;
				break;
			}
		}
		if (m == 0 && *splitted)
			m = 1;
	}
	if (m == 0)
		return (NULL);
	return (str_begin);
}

/**
 * _isdigit - Checks if a string contains digits.
 * @s: The string to check.
 * Return: 1 if the string contains only digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int n;

	for (n = 0; s[n]; n++)
	{
		if (s[n] < 48 || s[n] > 57)
			return (0);
	}
	return (1);
}
/**
 * rev_string - Reverses the characters in a string.
 * @s: The string to be reversed.
 * Return: None.
 */
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



