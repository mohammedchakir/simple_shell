#include "main.h"

/**
 * parcd - Change to the parent directory.
 * @datash: Shell information.
 * Return: None.
 */
void parcd(data_shell *datash)
{
	char _pwd[PATH_MAX];
	char *dir, *cpy_pwd, *cpy_strtok_pwd;

	getcwd(_pwd, sizeof(_pwd));
	cpy_pwd = duplicateString(_pwd);
	environ_set("OLDPWD", cpy_pwd, datash);
	dir = datash->args[1];
	if (compareStrings(".", dir) == 0)
	{
		environset("PWD", cpy_pwd, datash);
		free(cpy_pwd);
		return;
	}
	if (compareStrings("/", cpy_pwd) == 0)
	{
		free(cpy_pwd);
		return;
	}
	cpy_strtok_pwd = cpy_pwd;
	reverseString(cpy_strtok_pwd);
	cpy_strtok_pwd = tokenizeString(cpy_strtok_pwd, "/");
	if (cpy_strtok_pwd != NULL)
	{
		cpy_strtok_pwd = tokenizeString(NULL, "\0");

		if (cpy_strtok_pwd != NULL)
			reverseString(cpy_strtok_pwd);
	}
	if (cpy_strtok_pwd != NULL)
	{
		chdir(cpy_strtok_pwd);
		environset("PWD", cpy_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		environset("PWD", "/", datash);
	}
	datash->status = 0;
	free(cpy_pwd);
}

/**
 * cdto - Change the current directory.
 * @datash: Shell information.
 * Return: None.
 */
void cdto(data_shell *datash)
{
	char _pwd[PATH_MAX];
	char *dir, *cpy_pwd, *cpy_dir;

	getcwd(_pwd, sizeof(_pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		geterr(datash, 2);
		return;
	}
	cpy_pwd = duplicateString(_pwd);
	environset("OLDPWD", cpy_pwd, datash);
	cpy_dir = duplicateString(dir);
	environset("PWD", cpy_dir, datash);
	free(cpy_pwd);
	free(cpy_dir);
	datash->status = 0;
	chdir(dir);
}

/**
 * cdprev - Navigate to the previous directory.
 * @datash: Shell information.
 * Return: None.
 */
void cdprev(data_shell *datash)
{
	char _pwd[PATH_MAX];
	char *p_c_pwd, *p_old_pwd, *cpy_pwd, *cpy_oldpwd;

	getcwd(_pwd, sizeof(_pwd));
	cpy_pwd = duplicateString(_pwd);
	p_old_pwd = getenv("OLDPWD", datash->_environ);
	if (p_old_pwd == NULL)
		cpy_oldpwd = cpy_pwd;
	else
		cpy_oldpwd = duplicateString(p_old_pwd);
	environset("OLDPWD", cpy_pwd, datash);
	if (chdir(cpy_oldpwd) == -1)
		environset("PWD", cpy_pwd, datash);
	else
		environset("PWD", cpy_oldpwd, datash);
	p_c_pwd = getenv("PWD", datash->_environ);
	write(STDOUT_FILENO, p_c_pwd, getStringLength(p_c_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cpy_pwd);
	if (p_old_pwd)
		free(cpy_oldpwd);
	datash->status = 0;
	chdir(p_c_pwd);
}

/**
 * cdhome - Change to the home directory.
 * @datash: Shell information.
 * Return: None.
 */
void cdhome(data_shell *datash)
{
	char *p_c_pwd, *hom;
	char _pwd[PATH_MAX];

	getcwd(_pwd, sizeof(_pwd));
	p_c_pwd = duplicateString(_pwd);
	hom = getenv("HOME", datash->_environ);
	if (hom == NULL)
	{
		environset("OLDPWD", p_c_pwd, datash);
		free(p_c_pwd);
		return;
	}
	if (chdir(hom) == -1)
	{
		geterr(datash, 2);
		free(p_c_pwd);
		return;
	}
	environset("OLDPWD", p_c_pwd, datash);
	environset("PWD", hom, datash);
	free(p_c_pwd);
	datash->status = 0;
}
