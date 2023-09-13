#include "main.h"

/**
 * help - Displays general help information.
 * Return: None.
 */
void help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, getStringLength(help));
}

/**
 * helpalias - Provides information about the alias command.
 * Return: None.
 */
void helpalias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
}

/**
 * helpcd - Provides information about the cd (change directory) command.
 * Return: None.
 */
void helpcd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
}
