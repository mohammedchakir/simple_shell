#include "main.h"

/**
 * env_checker - checks if the variable is an env variable
 * @h: head of list
 * @in: input
 * @data: shell info
 * Return: Non.
 */
void env_checker(r_var **h, char *in, data_shell *data)
{
	int rw, ch, i, lval;
	char **_envrn;

	_envrn = data->_environ;
	for (rw = 0; _envrn[rw]; rw++)
	{
		for (i = 1, ch = 0; _envrn[rw][ch]; ch++)
		{
			if (_envrn[rw][ch] == '=')
			{
				lval = _strlen(_envrn[rw] + ch + 1);
				add_var_end(h, i, _envrn[rw] + ch + 1, lval);
				return;
			}

			if (in[i] == _envrn[rw][ch])
				i++;
			else
				break;
		}
	}
	for (i = 0; in[i]; i++)
	{
		if (in[i] == ' ' || in[i] == '\t' || in[i] == ';' || in[i] == '\n')
			break;
	}

	add_var_end(h, i, NULL, 0);
}

/**
 * var_checker - check if the typed variable is either $$ or $.
 * @h: head of the list
 * @in: input.
 * @st: status of shell
 * @data: shell info
 * Return: Non.
 */
int var_checker(r_var **h, char *in, char *st, data_shell *data)
{
	int i, l_st, l_pid;

	l_st = _strlen(st);
	l_pid = _strlen(data->pid);
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_end(h, 2, st, l_st), i++;
			else if (in[i + 1] == '$')
				add_var_end(h, 2, data->pid, l_pid), i++;
			else if (in[i + 1] == '\n')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_end(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_end(h, 0, NULL, 0);
			else
				env_checker(h, in + i, data);
		}
	}
	return (i);
}

/**
 * var_input - changes the input string into variables
 * @head: head of the list
 * @input: input
 * @new_input: replaced string
 * @nlen: new length
 * Return: new replaced string
 */
char *var_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *ind;
	int i, j, k;

	ind = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(ind->len_var) && !(ind->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (ind->len_var && !(ind->len_val))
			{
				for (k = 0; k < ind->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < ind->len_val; k++)
				{
					new_input[i] = ind->val[k];
					i++;
				}
				j += (ind->len_var);
				i--;
			}
			ind = ind->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}
	return (new_input);
}

/**
 * replace_var -replaced string into vars
 * @input: input
 * @datash: shell info
 * Return: replaced string
 */
char *replace_var(char *input, data_shell *datash)
{
	r_var *h, *ind;
	char *st, *n_input;
	int olen, nlen;

	st = aux_itoa(datash->status);
	h = NULL;
	olen = var_checker(&h, input, st, datash);
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
	nlen += olen;
	n_input = malloc(sizeof(char) * (nlen + 1));
	n_input[nlen] = '\0';
	n_input = var_input(&h, input, n_input, nlen);
	free(input);
	free(st);
	var_list_free(&h);
	return (n_input);
}
