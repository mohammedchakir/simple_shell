#include "main.h"

/**
 * helpenv - Displays information about the environment.
 * Return: None.
 */
void helpenv(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, getStringLength(help));

}

/**
 * helpsetenv - Provides information about the setenv command.
 * Return: None.
 */
void helpsetenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, getStringLength(help));
}

/**
 * helpunsetenv - Provides information about the unsetenv command.
 * Return: None.
 */
void helpunsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, getStringLength(help));
}

/**
 * helpgeneral - Provides general help information.
 * Return: None.
 */
void helpgeneral(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = " alias: alias [name=['string']]\n  cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "[dir]\n  exit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, getStringLength(help));
}

/**
 * helpexit - Provides information about the exit command.
 * Return: None.
 */
void helpexit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, getStringLength(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, getStringLength(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, getStringLength(help));
}
