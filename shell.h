#ifndef _SHELL_HEADER
#define _SHELL_HEADER
/* LOADING MAIN LIBRARIES */

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

/* write buffers */
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

#define HIST_FILE	"shell_history"
#define HIST_MAX	5120


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
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t_v2;

int subst_alias(info_t_v2 *info);
extern char **environ;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t_v2 *);
} builtin_table;

/* shell_pro_shloop.c */
int zsh(info_t_v2 *, char **);
int search_builtin(info_t_v2 *);
void search_cmd(info_t_v2 *);
void copy_cmd(info_t_v2 *);

/* shell_pro_parser.c */
int zed_cmd(info_t_v2*, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t_v2*, char *, char *);

/* shell_pro_errors.c */
void _eputs(char *);
int w_eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* shell_pro_string.c */
int str_leng(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);

/* shell_pro_string1.c */
char *cpy_str(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* shell_pro_exits.c */
char *_strncopy(char *, char *, int);
char *_strnconca(char *, char *, int);
char *l_strchr(char *, char);

/* shell_pro_tokenizer.c */
char **strtoword(char *, char *);
char **strtow2(char *, char);

/* shell_pro_realloc.c */
char *f_memset(char *, char, unsigned int);
void ffree(char **);
void *bfm_alloc(void *, unsigned int, unsigned int);

/* shell_pro_memory.c */
int freepointer(void **);

/* shell_pro_atoi.c */
int sys_interact(info_t_v2 *);
int char_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* shell_pro_errors1.c */
int conv_atoi(char *);
void print_error(info_t_v2 *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* shell_pro_builtin.c */
int shell_exit(info_t_v2 *);
int sys_cd(info_t_v2 *);
int chpwd_help(info_t_v2 *);

/* shell_pro_builtin1.c */
int display_history(info_t_v2 *);
int man_alias(info_t_v2 *);


/*shell_pro_getline.c */
ssize_t get_input(info_t_v2 *);
int get_line(info_t_v2 *, char **, size_t *);
void sigintHandler(int);

/* shell_pro_getinfo.c */
void swipe_info(info_t_v2 *);
void mark_info(info_t_v2 *, char **);
void release_info(info_t_v2 *, int);
int test_chain(info_t_v2 *info, char *buf, size_t *j);

/* shell_pro_environ.c */
char *_getenv(info_t_v2 *, const char *);
int print_env(info_t_v2 *);
int init_setenv(info_t_v2 *);
int rm_unsetenv(info_t_v2 *);
int load_env_list(info_t_v2 *);

/* shell_pro_findenv.c */
char **back_environ(info_t_v2 *);
int format_setenv(info_t_v2 *, char *);
int _setenv(info_t_v2 *, char *, char *);

/* shell_pro_history.c */
char *get_history_file(info_t_v2 *info);
int write_history(info_t_v2 *info);
int read_history(info_t_v2 *info);
int add_history_list(info_t_v2 *info, char *buf, int linecount);
int renumber_history(info_t_v2 *info);

/* shell_pro_lists.c */
list_t *ad_node(list_t **, const char *, int);
list_t *ad_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* shell_pro_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* shell_pro_vars.c */
int char_chain(info_t_v2 *, char *, size_t *);
void check_chain(info_t_v2 *, char *, size_t *, size_t, size_t);
int replace_vars(info_t_v2 *);
int replac_string(char **old, char *new);
/* shell history.c */
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
void build_history_list(info_t_v2 *info, const char *buf, int linecount);
int write_history(info_t_v2 *info);
int read_history(info_t_v2 *info);
int renumber_history(info_t_v2 *info);

#endif /* MAIN_HEADER */

