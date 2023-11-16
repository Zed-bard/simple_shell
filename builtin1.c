#include "shell.h"
/**
 * shell_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * shell_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_history(info_t *info)
{
  print_list(info->history);
  return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
  char *p, c;
  int ret;

  p = _strchr(str, '=');
  if (!p)
    return (1);
  c = *p;
  *p = 0;
  ret = delete_node_at_index(&(info->alias),
    get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
  *p = c;
  return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
  char *p;

  p = _strchr(str, '=');
  if (!p)
    return (1);
  if (!*++p)
    return (unset_alias(info, str));

  unset_alias(info, str);
  return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
  char *p = NULL, *a = NULL;

  if (node)
  {
    p = _strchr(node->str, '=');
    for (a = node->str; a <= p; a++)
      _putchar(*a);
    _putchar('\'');
    _puts(p + 1);
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
int shell_alias(info_t *info)
{
  int i = 0;
  char *p = NULL;
  list_t *node = NULL;

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
      set_alias(info, info->argv[i]);
    else
      print_alias(node_starts_with(info->alias, info->argv[i], '='));
  }

  return (0);
}

