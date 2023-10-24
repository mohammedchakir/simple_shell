#include "main.h"

/**
 * get_sigint - the handle the crtl + c call in prompt.
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
