#include "main.h"

/**
 * displayCmdInfo - display help info about cmds
 * Return: void
 */
void displayCmdInfo(void)
{
	char *usage = "Usage: help [-dms] [pattern ...]\n";
    char *description1 = "Display information about built-in commands.\n";
    char *description2 = "Displays brief summaries of built-in commands.\n";

    write(STDOUT_FILENO, usage, _strlen(usage));
    write(STDOUT_FILENO, description1, _strlen(description1));
    write(STDOUT_FILENO, description2, _strlen(description2));
}
/**
 * displayAliasInfo - display informations about alias
 * Return: void
 */
void displayAliasInfo(void)
{
	char *usage = "Usage: alias [-p] [name[=value]...]\n";
    char *description = "Define or display aliases.\n";

    write(STDOUT_FILENO, usage, _strlen(usage));
    write(STDOUT_FILENO, description, _strlen(description));
}
/**
 * displayCdInfo - displays informations about Cd cmd uses
 * Return: void
 */
void displayCdInfo(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
