#include "main.h"

/**
 * executeline - Processes commands and built-ins.
 * @datash: Shell information.
 * Return: 1 upon successful execution.
 */
int executeline(data_shell *datash)
{
	int (*built_in)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	built_in = get_builtin(datash->args[0]);

	if (built_in != NULL)
		return (built_in(datash));

	return (execmd(datash));
}
