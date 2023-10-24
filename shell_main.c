#include "main.h"

/**
 * free_data - function frees the data structure.
 * @datash: the data structure.
 * Return: no return printed.
 */
void free_data(data_shell *datash)
{
	unsigned int n;

	for (n = 0; datash->_environ[n]; n++)
	{
		free(datash->_environ[n]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - function initialize the data structure.
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int n;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (n = 0; environ[n]; n++)
		;

	datash->_environ = malloc(sizeof(char *) * (n + 1));

	for (n = 0; environ[n]; n++)
	{
		datash->_environ[n] = _strdup(environ[n]);
	}

	datash->_environ[n] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - the entry of point.
 * @ac: the argument count.
 * @av: the argument vector.
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
