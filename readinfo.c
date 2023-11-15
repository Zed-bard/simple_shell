#include "shell.h"

/**
 * clear_info_structure - initializes infos struct
 * @info: struct address
 */
void clear_info_structure(infos *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info_structure - initializes infos struct
 * @info: struct address
 * @av: argument vector
 */
void set_info_structure(infos *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

		info->argv = malloc(sizeof(char *) * 2);
		if (info->argv)
		{
		info->argv[0] = _strdup(info->arg);
		info->argv[1] = NULL;
		}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info_structure - frees infos struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info_structure(infos *info, int all)
{
	free(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
	free(info->arg);
	free_list(&(info->env));
	free_list(&(info->history));
	free_list(&(info->alias));
	free(info->environ);
	free(info->cmd_buf);

	if (info->readfd > 2)
		{
		close(info->readfd);
		}

	_putchar(BUF_FLUSH);
	}
}


