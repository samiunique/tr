#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define BUFFER_SIZE_R 1024
#define BUFFER_SIZE_W 1024
#define MAX_WORD_C 100
#define NEG_ONE -1
#define REG_F 0
#define OR_F 1
#define AND_F 2
#define CHAIN_F 3
#define BAS_CHANGE_L 1
#define BAS_CHANGE_U 2
#define USING_GETLINE 0
#define USING_STRTOK 0
#define HISTORY_FILE_NAME ".ss_history"
#define HISTORY_SIZE_MAX 4096
#define SET_INFORMATION							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

extern char **environ;

/**
 * struct List_Node - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct List_Node
{
	int num;
	char *str;
	struct List_Node *next;
} list_stru;

/**
 * struct InfoNode - contains simulated arguments for a function pointer,
 *					 allowing for a consistent function prototype
 * @arg: a string generated from getline that holds arguments
 * @argv: an array of strings generated from @arg
 * @path: the path string for the current command
 * @argc: the number of arguments
 * @lines: the number of errors encountered
 * @error_code: the exit() error code
 * @lc_flag: a flag indicating whether this line of input should be counted
 * @prog_name: the name of the program's file
 * @env: a linked list representing a local copy of the environ variables
 * @environ: a custom-modified copy of the environ from the linked list env
 * @history: the node for the command history
 * @alias: the node for the command alias
 * @env_changed: a flag that indicates whether environ has been changed
 * @status: the return status of the most recent executed command
 * @sep_buff: the address of the pointer to sep_buff, used for chaining
 * @sep_buff_kind: the type of command buffer (CMD_type ||, &&, ;)
 * @fd_read: the file descriptor used for reading line input
 * @hist_lines: the number of lines in the history
 */

typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_stru *env;
	list_stru *history;
	list_stru *alias;
	char **environ;
	int env_changed;
	int status;

	char **sep_buff;
	int sep_buff_kind;
	int fd_read;
	int hist_lines;
} in_formations;

/**
 * struct built_in - contains a built_in string and related function
 * @type: the built_in command flag
 * @func: the function
 */

typedef struct built_in
{
	char *type;
	int (*func)(in_formations *);
} builtin_commands;

int shell_main(in_formations *info, char **av);
int write_char(char c, int fd);
int write_chars(char *str, int fd);
int my_string_length(char *s);
int compare_strinds(char *s1, char *s2);
int putchar_err(char);
int put_char(char);
int _isalpha(int);
int _atoi(char *);
int err_num(char *);
int handle_exit(in_formations *);
int handle_cd(in_formations *);
int handle_help(in_formations *);
int handle_history(in_formations *);
int handle_alias(in_formations *);
int scanit(in_formations *, char **, size_t *);
int _printenv(in_formations *);
int check_setenv(in_formations *);
int check_unsetenv(in_formations *);
int _unsetenv(in_formations *, char *);
int _setenv(in_formations *, char *, char *);
void puts_err(char *);
void _puts(char *);
char *link_strings(char *, char *);
char *copy_strings(char *, char *);
char *duplicate_strings(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *char_strings(char *, char);
char *_memset(char *, char, unsigned int);
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(in_formations *, const char *);
char *check_starting(const char *, const char *);
char *dup_chars(char *, int, int);
char *check_file_in_path(in_formations *info, char *pathstr, char *cmd);
char *change_base(long int, int, int);
char *read_hist(in_formations *info);
char **get_environ(in_formations *);
char **into_two(char *, char *);
char **list_to_vector(list_stru *);
void check_command(in_formations *);
void create_process(in_formations *);
void handle_sigint(int);
void clear_info(in_formations *);
void set_info(in_formations *, char **);
void free_info(in_formations *, int);
void free_vector(char **);
void print_error(in_formations *, char *);
void handle_comments(char *);
void free_list(list_stru **);
void check_chain(in_formations *info, char *buf, size_t *p, size_t i, size_t len);
int handle_built_in(in_formations *);
bool is_executable(in_formations *, char *);
int loophsh(char **);
int b_free(void **);
int from_terminal(in_formations *);
int print_dec(int, int);
int gather_env(in_formations *);
int create_history(in_formations *info);
int read_history(in_formations *info);
int update_history(in_formations *info, char *buf, int linecount);
int renumber_history(in_formations *info);
int delete_node_at_index(list_stru **, unsigned int);
bool is_chain(in_formations *, char *, size_t *);
int change_alias(in_formations *);
int change_v(in_formations *);
int change_string(char **, char *);
list_stru *add_node_start(list_stru **head, const char *str, int num);
list_stru *add_node_end(list_stru **head, const char *str, int num);
list_stru *node_str_start(list_stru *, char *, char);
size_t print_list_strutr(const list_stru *);
size_t list_len(const list_stru *);
size_t print_list(const list_stru *);
ssize_t get_input(in_formations *);
ssize_t get_node_index(list_stru *, list_stru *);
char **string_split(char *str, char *separators, size_t *word_count);
int count_words(char *str, char *separators, unsigned int *arr);
void set_zero(unsigned int *arr, size_t size);
void set_null(char *arr, size_t size);
bool is_delimit(char c, char *delimiters);

#endif
