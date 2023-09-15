#include "main.h"

/**
 * free_dt - Frees allocated data memory.
 * @datash: Shell information.
 * Return: None.
 */
void free_dt(data_shell *datash)
{
	unsigned int n;

	for (n = 0; datash->_environ[n]; n++)
		free(datash->_environ[n]);
	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_dt - Initializes data.
 * @datash: Shell information.
 * @av: Arguments.
 * Return: None.
 */
void set_dt(data_shell *datash, char **av)
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
 * main - Entry point of the program.
 * @ac: Argument count.
 * @av: Argument vector.
 * Return: 0 on successful execution.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, _sigint);
	set_dt(&datash, av);
	loop_shell(&datash);
	free_dt(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
