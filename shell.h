#ifndef _SHELL_HEADER
#define _SHELL_HEADER

/* LOADING MAIN LIBRARIES */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <stddef.h>

/*SIZES of buffers */
#define READ_BUF_SIZE 2048
#define WRITE_BUF_SIZE 2048
#define BUF_FLUSH -1

/* for read/write buffers */
#define READ_BUF_SIZE 2048
#define WRITE_BUF_SIZE 2048
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".shell history"
#define HIST_MAX	5120

/*of the macro #define */
#define INFO_INIT {NULL, NULL, NULL, NULL, 0, NULL, NULL, 0, NULL, 0, 0, 0}
/**
 * struct infos - Structure for shell information
 * @str:string - (malloc'ed string)
 * @readfd: File descriptor for reading
 * @line: Current command line
 * @args: Arguments of the command
 * @arg: arguments
 * @argc: Number of command-line arguments
 * @argv: argument vector from main()
 * @status: Exit status of the previous command
 * @pwd: Current working directory
 * @env: Environment variables
 * @line_count: count of commands executed
 * @linecount_flag: flag to indicate line count
 * @path: path to command
 * @err_num: error number
 */
typedef struct infos
{
	char *line;
	char *str;
	char **args;
	char **arg;
	int argc;
	char **argv;
	int status;
	char *pwd;
	char *env;
	int readfd;
	char *path;
	int err_num;
	size_t line_count;
	int linecount_flag;
} infos;
/* MANIN Function */
int main(int argc, char *argv[]);
void _eputs(const char *str);
void _eputchar(char c);
void populate_env_list(infos *info);
void read_history(infos *info);
/* Utilis prototype */
int Shell_state(infos *info);
int zed_delim(char c, char *delim);
int shell_isalpha(int c);
int run_atoi(char *s);
/**
 * struct builtin_table - struct for built-in commands and their functions
 * @type: the built-in command
 * @func: pointer to the function for the command
 */
typedef struct builtin_table
{
	char *type;
	int (*func)(infos *);
} builtin_table;

/*Loop.c Function prototype */
void zed(infos *info, char *av[]);
int search_builtin(infos *info);
void call_cmd(infos *info);
void fork_cmd(infos *info);
/*builtin.c Fuction prototype */
int shell_exit(infos *infos);
int shell_cd(infos *infos);
int shell_help(infos *infos);

/**
 * struct list_z - Structure representing a linked list node.
 * @str: Pointer to a string.
 * @next: Pointer to the next node in the linked list.
 * @alias: create custom shortcuts for often-used
 * @history: Linked list of command history
 * Description: This structure represents a node in a linked list.
 *		It containsa string pointer 'str' to store some
 *		data, and a 'next' pointer to point to the next
 *		node in the linked list.
 */
typedef struct list_z
{
	char *str;
	struct list_z *next;
	char *alias;
	struct list_z *history;

} list_z;
/*builtin1.c Fuction prototype */
int shell_history(infos *info);
int unstate_alias(infos *info, char *alias_str);
int state_alias(infos *info, char *str);
int print_alias(list_z *alias_node);
int shell_alias(infos *info);

/*environ.c Fuction prototype */
int shell_env(infos *info);
char *_getenv(infos *info, const char *name);
int shell_setenv(infos *info);
int shell_unsetenv(infos *info);
int read_env_vars(infos *info);
/*getevin.c  Fuction Prototype */
int _unset_env(infos *info, char *var);
int _set_env(infos *info, char *var, char *value);
/* readinfo.c Fuction Prototype */
void clear_info_structure(infos *info);
void set_info_structure(infos *info, char **av);
void free_info_structure(infos *info, int all);
/*output_utils.c function prototype */
char *zed_strcpy(char *dest, char *src);
char *zed_strdup(const char *str);
void zed_puts(char *str);
int zed_putchar(char c);
/*output_utils1.c Function prototype  */
int zed_strlen(char *s);
int zed_strcmp(char *s1, char *s2);
char *zed_with(const char *haystack, const char *needle);
char *zed_strcat(char *dest, char *src);
/* exit.c Function prototypes */
char *shell_strncpy(char *dest, char *src, int n);
char *shell_strncat(char *dest, char *src, int n);
char *shell_strchr(char *s, char c);
/*History.c fuction prototype */
char *history_file(infos *info);
int write_history(infos *info);
int read_history(infos *info);
int shell_list(infos *info, char *buf, int linecount);
int recount_history(infos *info);
#endif /*SHEEL_HEADER */
