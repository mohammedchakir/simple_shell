#include "main.h"

/**
 * searchablecdir - Checks if a path is searchable.
 * @path: The path to check.
 * @i: Pointer to an index.
 * Return: 1 if searchable, 0 otherwise.
 */
int searchablecdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);
	while (path[*i] != ':' && path[*i])
		*i += 1;
	if (path[*i])
		*i += 1;
	return (0);
}

/**
 * locatecmd - Searches for the location of a command.
 * @cmd: The command to locate.
 * @_environ: The environment.
 * Return: The path to the command if found, or NULL if not found.
 */
char *locatecmd(char *cmd, char **_environ)
{
	char *_path, *path_ptr, *path_token, *dir;
	int dir_len, cmd_len, i;
	struct stat st;

	_path = getenv("PATH", _environ);
	if (_path)
	{
		path_ptr = duplicateString(_path);
		cmd_len = getStringLength(cmd);
		path_token = tokenizeString(path_ptr, ":");
		i = 0;
		while (path_token != NULL)
		{
			if (searchablecdir(_path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			dir_len = getStringLength(path_token);
			dir = malloc(dir_len + cmd_len + 2);
			copyString(dir, path_token);
			concatenateStrings(dir, "/");
			concatenateStrings(dir, cmd);
			concatenateStrings(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_ptr);
				return (dir);
			}
			free(dir);
			path_token = tokenizeString(NULL, ":");
		}
		free(path_ptr);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * checkexecutable - Determines if a file is executable.
 * @datash: Shell information.
 * Return: 0 if it's not executable, or a non-zero value if it is.
 */
int checkexecutable(data_shell *datash)
{
	struct stat st;
	int i;
	char *inp;

	inp = datash->args[0];
	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '.')
		{
			if (inp[i + 1] == '.')
				return (0);
			if (inp[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (inp[i] == '/' && i != 0)
		{
			if (inp[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
	{
		return (0);
	}
	if (stat(inp + i, &st) == 0)
	{
		return (i);
	}
	geterr(datash, 127);
	return (-1);
}

/**
 * checkcmderr - Checks if the user has access to a destination directory.
 * @dir: The destination directory.
 * @datash: Shell information.
 * Return: 1 if the user has access, 0 otherwise.
 */
int checkcmderr(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		geterr(datash, 127);
		return (1);
	}
	if (compareStrings(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			geterr(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			geterr(datash, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * execmd - Executes a command.
 * @datash: Shell information.
 * Return: 1 on successful execution.
 */
int execmd(data_shell *datash)
{
	pid_t pid;
	pid_t wpid;
	int state, execute;
	char *dir;
	(void) wpid;

	execute = checkexecutable(datash);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		dir = locatecmd(datash->args[0], datash->_environ);
		if (checkcmderr(dir, datash) == 1)
			return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execute == 0)
			dir = locatecmd(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + execute, datash->args, datash->_environ);
	}
	else if (pid < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
