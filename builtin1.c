#include "shell.h"

/**
 * shell_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_history(infos *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unstate_alias - unstats an alias string
 * @info: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unstate_alias(infos *info, char *alias_str)
{
	char *equal_sign, temp;
	int ret;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);
	temp = *equal_sign;
	*equal_sign = '\0';
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*equal_sign = temp;
	return (ret);
}

/**
 * state_alias - states alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int state_alias(infos *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unstate_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_z *alias_node)
{
	char *equal_sign = NULL, *alias_value = NULL;

	if (alias_node)
	{
		equal_sign = _strchr(alias_node->str, '=');
		for (alias_value = alias_node->str; alias_value <= equal_sign; alias_value++)
			_putchar(*alias_value);
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int shell_alias(infos *info)
{
	int i = 0;
	char *p = NULL;
	list_z *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			state_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

