#include "main.h"

/**
 * displayhelp - Display the current shell environment
 * Return: void
 */
void displayhelp(void)
{
	char *usage = "Usage: env [options] [name=value] [command [args]]\n";
    char *description = "Display the current shell environment.\n";
    
    write(STDOUT_FILENO, usage, _strlen(usage));
    write(STDOUT_FILENO, description, _strlen(description));

}
/**
 * displayEnvInfo - display set env info
 * Return: void
 */
void displayEnvInfo(void)
{

	char *usage = "Usage: setenv (const char *name, const char *value, int replace)\n";
    char *description = "Add a new definition to the environment.\n";
    
    write(STDOUT_FILENO, usage, _strlen(usage));
    write(STDOUT_FILENO, description, _strlen(description));
}
/**
 * isplayUnsetenvInfo - display unset env info
 * Return: void
 */
void displayUnsetenvInfo(void)
{
	char *usage = "Usage: unsetenv (const char *name)\n";
    char *description = "Remove an entry completely from the environment.\n";
    
    write(STDOUT_FILENO, usage, _strlen(usage));
    write(STDOUT_FILENO, description, _strlen(description));
}


/**
 * displayAll - display general info
 * Return: void
 */
void displayAll(void)
{
	char *versionInfo = "^-^ MyShell, version 1.0\n";
    char *introMessage = "These commands are defined internally. Type 'help' to see the list.\n";
    char *commandList = "Type 'help <command>' to find out more about a specific command.\n\n";
    char *availableCommands = 
        "Available commands:\n"
        "  alias: alias [name=['string']]\n"
        "  cd: cd [-L|[-P [-e]] [-@]] [dir]\n"
        "  exit: exit [n]\n"
        "  env: env [option] [name=value] [command [args]]\n"
        "  setenv: setenv [variable] [value]\n"
        "  unsetenv: unsetenv [variable]\n";
    
    write(STDOUT_FILENO, versionInfo, _strlen(versionInfo));
    write(STDOUT_FILENO, introMessage, _strlen(introMessage));
    write(STDOUT_FILENO, commandList, _strlen(commandList));
    write(STDOUT_FILENO, availableCommands, _strlen(availableCommands));
}
/**
 * displayExit - display exit info
 * Return: void
 */
void displayExit(void)
{
	char *usage = "Usage: exit [n]\n";
    char *description1 = "Exit the shell.\n";
    char *description2 = "Exits the shell with a status of N. If N is omitted, the exit status is that of the last command executed.\n";
    
    write(STDOUT_FILENO, usage, _strlen(usage));
    write(STDOUT_FILENO, description1, _strlen(description1));
    write(STDOUT_FILENO, description2, _strlen(description2));
}
