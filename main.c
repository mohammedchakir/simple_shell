#include "main.h"

/**
 * freeData - Deallocates memory used by data.
 * @datash: Shell information.
 * Return: None.
 */
void freeData(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
		free(datash->_environ[i]);
	free(datash->_environ);
	free(datash->pid);
}

/**
 * initializeData - Initialize shell data.
 *
 * @datash: Shell information.
 * @av: Arguments.
 * Return: None.
 */
void initializeData(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;
	for (i = 0; environ[i]; i++)
		;
	datash->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}
	datash->_environ[i] = NULL;
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
	initializeData(&datash, av);
	shellLoop(&datash);
	freeData(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
