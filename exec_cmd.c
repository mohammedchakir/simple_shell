#include "main.h"

/**
 * is_cdir - function checks ":" if is in the current directory.
 * @path: the type char pointer character.
 * @n: the type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *n)
{
	if (path[*n] == ':')
		return (1);

	while (path[*n] != ':' && path[*n])
	{
		*n += 1;
	}

	if (path[*n])
		*n += 1;

	return (0);
}

/**
 * _which - function locates a command.
 * @cmd: the command identification.
 * @_environ: the environment variable.
 * Return: the location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *directory;
	int len_dir, len_cmd, n;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		n = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &n))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			directory = malloc(len_dir + len_cmd + 2);
			_strcpy(directory, token_path);
			_strcat(directory, "/");
			_strcat(directory, cmd);
			_strcat(directory, "\0");
			if (stat(directory, &st) == 0)
			{
				free(ptr_path);
				return (directory);
			}
			free(directory);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
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
 * is_executable - function determines if is an executable.
 * @datash: the data structure.
 * Return: 0 if is not an executable, other number if it does.
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int n;
	char *input;

	input = datash->args[0];
	for (n = 0; input[n]; n++)
	{
		if (input[n] == '.')
		{
			if (input[n + 1] == '.')
				return (0);
			if (input[n + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[n] == '/' && n != 0)
		{
			if (input[n + 1] == '.')
				continue;
			n++;
			break;
		}
		else
			break;
	}
	if (n == 0)
		return (0);

	if (stat(input + n, &st) == 0)
	{
		return (n);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - function verifies if user has permissions to access.
 * @dir: the destination directory.
 * @datash: the data structure.
 * Return: 1 if there is an error, 0 if not.
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - the executes command lines.
 * @datash: the data relevant (args and input).
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
