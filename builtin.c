#include "shell.h"
/**
 * shell_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int shell_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);

	if (!s)
	_puts("TODO: >> directory failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
	if (!dir)
	chdir_ret = /* TODO: what should this be? */
	chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
	else
	chdir_ret = chdir(dir);
	}
	else if (com_strcmp(info->argv[1], "-") == 0)
	{
	if (!_getenv(info, "OLDPWD="))
	{
	_puts(s);
	_putchar('\n');
	return (1);
	}
	_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
	chdir_ret = /* TODO: what should this be? */
	chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
	print_error(info, "unable cd to ");
	_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));
	}
return (0);
}

/**
 * shell_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int shell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;

	_puts("the system yet under development \n");
	if (0)
	_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

