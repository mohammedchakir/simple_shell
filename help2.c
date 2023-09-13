#include "main.h"

/**
 * _help - help info
 * Return: Non
 */
void _help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, getStringLength(help));
}
/**
 * _help_alias - alias info
 * Return: Non
 */
void _help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
}
/**
 * _help_cd - cd info
 * Return: Non
 */
void _help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
}
