#include "main.h"

/**
 * checkIfEnvVariable - Verifies whether a variable is an environment variable.
 * @h: The head of the list.
 * @in: The input variable.
 * @data: Shell-related information.
 * Return: None.
 */
void checkIfEnvVariable(r_var **h, char *in, data_shell *data)
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
				lval = getStringLength(_envrn[rw] + ch + 1);
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

	appendVariableToEnd(h, i, NULL, 0);
}

/**
 * checkVariable - Verify if the provided variable is either "$$" or "$".
 * @h: The head of the list.
 * @in: The input variable.
 * @st: The shell's status.
 * @data: Shell-related information.
 * Return: None.
 */
int checkVariable(r_var **h, char *in, char *st, data_shell *data)
{
	int i, l_st, l_pid;

	l_st = getStringLength(st);
	l_pid = getStringLength(data->pid);
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				appendVariableToEnd(h, 2, st, l_st), i++;
			else if (in[i + 1] == '$')
				appendVariableToEnd(h, 2, data->pid, l_pid), i++;
			else if (in[i + 1] == '\n')
				appendVariableToEnd(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				appendVariableToEnd(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				appendVariableToEnd(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				appendVariableToEnd(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				appendVariableToEnd(h, 0, NULL, 0);
			else
				checkIfEnvVariable(h, in + i, data);
		}
	}
	return (i);
}

/**
 * convertToVariables - Converts the input string into variables.
 * @head: The head of the list.
 * @input: The input string.
 * @new_input: The string with replacements.
 * @nlen: The new length of the string.
 * Return: The modified string with variable substitutions.
 */
char *convertToVariables(r_var **head, char *input, char *new_input, int nlen)
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
 * replaceVariables - Replaces variables within an input string.
 * @input: The input string.
 * @datash: Shell-related information.
 * Return: The string with variables replaced.
 */
char *replaceVariables(char *input, data_shell *datash)
{
	r_var *h, *ind;
	char *st, *n_input;
	int olen, nlen;

	st = aux_itoa(datash->status);
	h = NULL;
	olen = checkVariable(&h, input, st, datash);
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
	n_input = convertToVariables(&h, input, n_input, nlen);
	free(input);
	free(st);
	freeVarList(&h);
	return (n_input);
}
