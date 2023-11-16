#include "shell.h"

/**
 * shell_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shell_env(info_t *info)
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
char *_getenv(info_t *info, const char *name)
{
  list_t *node = info->env;
  char *p;

  while (node)
  {
    p = starts_with(node->str, name);
    if (p && *p)
      return (p);
    node = node->next;
  }
  return (NULL);
}

/**
 * shell_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_setenv(info_t *info)
{
  if (info->argc != 3)
  {
    _eputs("Incorrect number of arguements\n");
    return (1);
  }
  if (_setenv(info, info->argv[1], info->argv[2]))
    return (0);
  return (1);
}

/**
 * shell_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_unsetenv(info_t *info)
{
  int i;

  if (info->argc == 1)
  {
    _eputs("Too few arguements.\n");
    return (1);
  }
  for (i = 1; i <= info->argc; i++)
    _unsetenv(info, info->argv[i]);

  return (0);
}



