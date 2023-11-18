#include "shell.h"

/**
 * zsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int zsh(info_t_v2 *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		swipe_info(info);
		if (sys_interact(info))
			_puts("$ ");
		w_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			mark_info(info, av);
			builtin_ret = search_builtin(info);
			if (builtin_ret == -1)
				search_cmd(info);
		}
		else if (sys_interact(info))
			_putchar('\n');
		release_info(info, 0);
	}
	read_history(info);
	release_info(info, 1);
	if (!sys_interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * search_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_builtin(info_t_v2 *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{"help", chpwd_help},
		{"history", display_history},
		{"setenv", init_setenv},
		{"unsetenv", rm_unsetenv},
		{"cd", sys_cd},
		{"alias", man_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * search_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void search_cmd(info_t_v2 *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!char_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		copy_cmd(info);
	}
	else
	{
		if ((sys_interact(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && zed_cmd(info, info->argv[0]))
			copy_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * copy_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void copy_cmd(info_t_v2 *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, back_environ(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

