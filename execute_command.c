#include "main.h"

/**
 * searchable_cdir - checks if is searchable.
 * @path: path to check
 * @i: pointer of index.
 * Return: 1 or 0
 */
int searchable_cdir(char *path, int *i)
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
 * locate_cmd - look for a command
 * @cmd: the cmd
 * @_environ: environment
 * Return: location of the cmd.
 */
char *locate_cmd(char *cmd, char **_environ)
{
	char *_path, *path_ptr, *path_token, *dir;
	int dir_len, cmd_len, i;
	struct stat st;

	_path = _getenv("PATH", _environ);
	if (_path)
	{
		path_ptr = _strdup(_path);
		cmd_len = _strlen(cmd);
		path_token = _strtok(path_ptr, ":");
		i = 0;
		while (path_token != NULL)
		{
			if (searchable_cdir(_path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			dir_len = _strlen(path_token);
			dir = malloc(dir_len + cmd_len + 2);
			_strcpy(dir, path_token);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_ptr);
				return (dir);
			}
			free(dir);
			path_token = _strtok(NULL, ":");
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
 * check_executable - checks if it is executable
 * @datash: shell info
 * Return: 0 if is not or others if it is
 */
int check_executable(data_shell *datash)
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
	err_get(datash, 127);
	return (-1);
}

/**
 * check_cmd_err - verifies if user has access
 * @dir: destination directory
 * @datash: shell info
 * Return: 1 or 0
 */
int check_cmd_err(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		err_get(datash, 127);
		return (1);
	}
	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			err_get(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			err_get(datash, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * exe_cmd- executes command
 * @datash: shell info
 * Return: 1 when successfull.
 */
int exe_cmd(data_shell *datash)
{
	pid_t pid;
	pid_t wpid;
	int state, execute;
	char *dir;
	(void) wpid;

	execute = check_executable(datash);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		dir = locate_cmd(datash->args[0], datash->_environ);
		if (check_cmd_err(dir, datash) == 1)
			return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execute == 0)
			dir = locate_cmd(datash->args[0], datash->_environ);
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
