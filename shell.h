#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 2048
#define WRITE_BUF_SIZE 2048
#define BUF_FLUSH '\0'

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_FILE	"shell_history"
#define HIST_MAX	3072

extern char **environ;
/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 */
typedef struct builtin
{
	char *type;
} builtin_table;
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@status: the return status of the last exec'd command
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{ \
	.arg = NULL, \
	.argv = NULL, \
	.path = NULL, \
	.argc = 0, \
	.line_count = 0, \
	.err_num = 0, \
	.linecount_flag = 0, \
	.fname = NULL, \
	.env = NULL, \
	.history = NULL, \
	.alias = NULL, \
	.environ = NULL, \
	.env_changed = 0, \
	.status = 0, \
	.cmd_buf = NULL, \
	.cmd_buf_type = 0, \
	.readfd = 0, \
	.histcount = 0 \
}
/* shell_errors.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
/*shell_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* shell_builtin.c */
int shell_exit(info_t *info);
int shell_cd(info_t *info);
int shell_help(info_t *info);
/*shell fun. prototype */
void print_error(info_t *info, char *estr);
/* shell_builtin1.c */
int shell_history(info_t *);
int shell_alias(info_t *);
int shell_history(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int shell_alias(info_t *info);
/*shell_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* shell_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
/* shell_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* shell_shloop.c */
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
/* shell_parser.c */
int zed_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*shell_exits.c */
char *shell_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* shell_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);
/* shell_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* shell_memory.c */
int bfree(void **);

/* shell_alias.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int conv_atoi(char *);
/* shell_information.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* shell_environ.c */
char *_getenv(info_t *, const char *);
int shell_env(info_t *);
int shell_setenv(info_t *);
int shell_unsetenv(info_t *);

/* shell_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* shell_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* shell_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* shell_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* shell_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
/* shell_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


#endif

