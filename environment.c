#include "shell.h"

/**
 * print_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_env(info_t_v2 *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t_v2 *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = start_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * init_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int init_setenv(info_t_v2 *info)
{
	if (info->argc != 3)
	{
		_eputs("Invalid number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rm_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int rm_unsetenv(info_t_v2 *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		format_setenv(info, info->argv[i]);

	return (0);
}

/**
 * load_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int load_env_list(info_t_v2 *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		ad_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

