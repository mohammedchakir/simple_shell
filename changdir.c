#include "main.h"

/**
 * cd_dot - function changes to the parent directory.
 * @datash: the data relevant (environ).
 * Return: no return printed.
 */
void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	directory = datash->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - function changes forward a directory given
 * by the user.
 * @datash: the data relevant (directories).
 * Return: no return printed.
 */
void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *directory, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	directory = datash->args[1];
	if (chdir(directory) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(directory);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(directory);
}

/**
 * cd_previous - function changes to the previous directory.
 * @datash: the data relevant (environ).
 * Return: no return printed.
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - function changes to home directory.
 * @datash: the data relevant (environ).
 * Return: no return printed.
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
