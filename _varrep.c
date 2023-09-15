#include "main.h"

/**
 * env_checker - Verifies if a variable is an environment variable.
 * @h: Head of the list of environment variables.
 * @in: The input variable to check.
 * @data: current Shell information.
 * Return: None.
 */
void env_checker(r_var **h, char *in, data_shell *data)
{
	int rw, ch, n, lval;
	char **_envrn;

	_envrn = data->_environ;
	for (rw = 0; _envrn[rw]; rw++)
	{
		for (n = 1, ch = 0; _envrn[rw][ch]; ch++)
		{
			if (_envrn[rw][ch] == '=')
			{
				lval = _strlen(_envrn[rw] + ch + 1);
				add_var_end(h, n, _envrn[rw] + ch + 1, lval);
				return;
			}

			if (in[n] == _envrn[rw][ch])
				n++;
			else
				break;
		}
	}
	for (n = 0; in[n]; n++)
	{
		if (in[n] == ' ' || in[n] == '\t' || in[n] == ';' || in[n] == '\n')
			break;
	}

	add_var_end(h, n, NULL, 0);
}

/**
 * var_checker - Checks if the input represents either "$$" or "$".
 * @h: Head of the list.
 * @in: The input string to check.
 * @st: The shell status.
 * @data: Shell information.
 * Return: None.
 */
int var_checker(r_var **h, char *in, char *st, data_shell *data)
{
	int n, l_st, l_pid;

	l_st = _strlen(st);
	l_pid = _strlen(data->pid);
	for (n = 0; in[n]; n++)
	{
		if (in[n] == '$')
		{
			if (in[n + 1] == '?')
				add_var_end(h, 2, st, l_st), n++;
			else if (in[n + 1] == '$')
				add_var_end(h, 2, data->pid, l_pid), n++;
			else if (in[n + 1] == '\n')
				add_var_end(h, 0, NULL, 0);
			else if (in[n + 1] == '\0')
				add_var_end(h, 0, NULL, 0);
			else if (in[n + 1] == ' ')
				add_var_end(h, 0, NULL, 0);
			else if (in[n + 1] == '\t')
				add_var_end(h, 0, NULL, 0);
			else if (in[n + 1] == ';')
				add_var_end(h, 0, NULL, 0);
			else
				env_checker(h, in + n, data);
		}
	}
	return (n);
}

/**
 * var_input - Replaces variables in the input string with their values.
 * @head: Head of the list containing variables.
 * @input: The original input string.
 * @new_input: The resulting string with variables replaced.
 * @nlen: The new length of the string.
 * Return: The new string with variables replaced.
 */
char *var_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *ind;
	int n, m, l;

	ind = *head;
	for (m = n = 0; n < nlen; n++)
	{
		if (input[m] == '$')
		{
			if (!(ind->len_var) && !(ind->len_val))
			{
				new_input[n] = input[m];
				m++;
			}
			else if (ind->len_var && !(ind->len_val))
			{
				for (l = 0; l < ind->len_var; l++)
					m++;
				n--;
			}
			else
			{
				for (l = 0; l < ind->len_val; l++)
				{
					new_input[n] = ind->val[l];
					n++;
				}
				m += (ind->len_var);
				n--;
			}
			ind = ind->next;
		}
		else
		{
			new_input[n] = input[m];
			m++;
		}
	}
	return (new_input);
}

/**
 * replace_var - Replaces variables in the input string with their values.
 * @input: The input string to be processed.
 * @datash: Shell information.
 * Return: The input string with variables replaced.
 */
char *replace_var(char *input, data_shell *datash)
{
	r_var *h, *ind;
	char *st, *n_input;
	int mlen, nlen;

	st = aux_itoa(datash->status);
	h = NULL;
	mlen = var_checker(&h, input, st, datash);
	if (h == NULL)
	{
		free(st);
		return (input);
	}
	ind = h;
	nlen = 0;
	while (ind != NULL)
	{
		nlen += (ind->len_val - ind->len_var);
		ind = ind->next;
	}
	nlen += mlen;
	n_input = malloc(sizeof(char) * (nlen + 1));
	n_input[nlen] = '\0';
	n_input = var_input(&h, input, n_input, nlen);
	free(input);
	free(st);
	var_list_free(&h);
	return (n_input);
}
