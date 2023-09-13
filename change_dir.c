#include "main.h"

/**
 * par_cd - change to parent directory
 * @datash: shell info
 * Return: Non.
 */
void par_cd(data_shell *datash)
{
	char _pwd[PATH_MAX];
	char *dir, *cpy_pwd, *cpy_strtok_pwd;

	getcwd(_pwd, sizeof(_pwd));
	cpy_pwd = _strdup(_pwd);
	environ_set("OLDPWD", cpy_pwd, datash);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	{
		environ_set("PWD", cpy_pwd, datash);
		free(cpy_pwd);
		return;
	}
	if (_strcmp("/", cpy_pwd) == 0)
	{
		free(cpy_pwd);
		return;
	}
	cpy_strtok_pwd = cpy_pwd;
	rev_string(cpy_strtok_pwd);
	cpy_strtok_pwd = _strtok(cpy_strtok_pwd, "/");
	if (cpy_strtok_pwd != NULL)
	{
		cpy_strtok_pwd = _strtok(NULL, "\0");

		if (cpy_strtok_pwd != NULL)
			rev_string(cpy_strtok_pwd);
	}
	if (cpy_strtok_pwd != NULL)
	{
		chdir(cpy_strtok_pwd);
		environ_set("PWD", cpy_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		environ_set("PWD", "/", datash);
	}
	datash->status = 0;
	free(cpy_pwd);
}

/**
 * cd_to - change directory
 * @datash: shell info
 * Return: Non
 */
void cd_to(data_shell *datash)
{
	char _pwd[PATH_MAX];
	char *dir, *cpy_pwd, *cpy_dir;

	getcwd(_pwd, sizeof(_pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		err_get(datash, 2);
		return;
	}
	cpy_pwd = _strdup(_pwd);
	environ_set("OLDPWD", cpy_pwd, datash);
	cpy_dir = _strdup(dir);
	environ_set("PWD", cpy_dir, datash);
	free(cpy_pwd);
	free(cpy_dir);
	datash->status = 0;
	chdir(dir);
}

/**
 * cd_prev - move to previous directory
 * @datash: shell info
 * Return: Non
 */
void cd_prev(data_shell *datash)
{
	char _pwd[PATH_MAX];
	char *p_c_pwd, *p_old_pwd, *cpy_pwd, *cpy_oldpwd;

	getcwd(_pwd, sizeof(_pwd));
	cpy_pwd = _strdup(_pwd);
	p_old_pwd = _getenv("OLDPWD", datash->_environ);
	if (p_old_pwd == NULL)
		cpy_oldpwd = cpy_pwd;
	else
		cpy_oldpwd = _strdup(p_old_pwd);
	environ_set("OLDPWD", cpy_pwd, datash);
	if (chdir(cpy_oldpwd) == -1)
		environ_set("PWD", cpy_pwd, datash);
	else
		environ_set("PWD", cpy_oldpwd, datash);
	p_c_pwd = _getenv("PWD", datash->_environ);
	write(STDOUT_FILENO, p_c_pwd, _strlen(p_c_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cpy_pwd);
	if (p_old_pwd)
		free(cpy_oldpwd);
	datash->status = 0;
	chdir(p_c_pwd);
}

/**
 * cd_home - move to home
 * @datash: shell info
 * Return: Non
 */
void cd_home(data_shell *datash)
{
	char *p_c_pwd, *hom;
	char _pwd[PATH_MAX];

	getcwd(_pwd, sizeof(_pwd));
	p_c_pwd = _strdup(_pwd);
	hom = _getenv("HOME", datash->_environ);
	if (hom == NULL)
	{
		environ_set("OLDPWD", p_c_pwd, datash);
		free(p_c_pwd);
		return;
	}
	if (chdir(hom) == -1)
	{
		err_get(datash, 2);
		free(p_c_pwd);
		return;
	}
	environ_set("OLDPWD", p_c_pwd, datash);
	environ_set("PWD", hom, datash);
	free(p_c_pwd);
	datash->status = 0;
}
