#include "main.h"

/**
 * check_env - the checks if the typed variable is an env variable.
 * @h: the head of linked list.
 * @in: the input string.
 * @data: the data structure.
 * Return: no return printed.
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, m, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (m = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, m, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[m] == _envr[row][chr])
				m++;
			else
				break;
		}
	}

	for (m = 0; in[m]; m++)
	{
		if (in[m] == ' ' || in[m] == '\t' || in[m] == ';' || in[m] == '\n')
			break;
	}

	add_rvar_node(h, m, NULL, 0);
}

/**
 * check_vars - function check if the typed variable is $$ or $.
 * @h: the head of the linked list.
 * @in: the input string.
 * @st: the last status of the shell.
 * @data: the data structure.
 * Return: no return printed.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int n, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (n = 0; in[n]; n++)
	{
		if (in[n] == '$')
		{
			if (in[n + 1] == '?')
				add_rvar_node(h, 2, st, lst), n++;
			else if (in[n + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), n++;
			else if (in[n + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + n, data);
		}
	}

	return (n);
}

/**
 * replaced_input - function replaces string into variables.
 * @head: the head of the linked list.
 * @input: the input string.
 * @new_input: new input string.
 * @nlen: the new length.
 * Return: the replaced string.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int n, m, l;

	indx = *head;
	for (m = n = 0; n < nlen; n++)
	{
		if (input[m] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[n] = input[m];
				m++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (l = 0; l < indx->len_var; l++)
					m++;
				n--;
			}
			else
			{
				for (l = 0; l < indx->len_val; l++)
				{
					new_input[n] = indx->val[l];
					n++;
				}
				m += (indx->len_var);
				n--;
			}
			indx = indx->next;
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
 * rep_var - function calls functions to replace string into vars.
 * @input: the input string.
 * @datash: the data structure.
 * Return: the replaced string.
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
