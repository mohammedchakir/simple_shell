#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;
/**
 * struct data - the shell struct contains informations.
 * @av: the arg vector.
 * @input: the string input from user.
 * @args: the tokens of commands.
 * @status: update on status.
 * @counter: the current line count.
 * @_environ: the environ variable.
 * @pid: pid the shell process.
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - singly-linked-list.
 * @separator: the separator.
 * @next: the proceedig node.
 * Description: the stores separators.
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - singly-linked-list.
 * @line: the cmd line.
 * @next: the proceeding node.
 * Description: the stores cmd line.
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - singly-linked-list.
 * @len_var: the length of the variable.
 * @val: the value of the variable.
 * @len_val: the length of the value.
 * @next: the proceeding node.
 * Description: the singly-linked-list to store variables.
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - struct cointaing cmd arguments.
 * @name: the abriviation of built-n cmd.
 * @f: pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


sep_list *addSeparatorAtEnd(sep_list **head, char sep)
void freeSeparatorList(sep_list **head)
line_list *appendLineToEnd(line_list **head, char *line)
void freeLineList(line_list **head)

r_var *appendVariableToEnd(r_var **head, int lvar, char *val, int lval)
void freeVarList(r_var **head)
char *readInput(int *i_eof)

void shellLoop(data_shell *datash)
char *removeComments(char *in)
void freeData(data_shell *datash)
void initializeData(data_shell *datash, char **av)
int main(int ac, char **av)

void copyData(void *newptr, const void *ptr, unsigned int size)
void *resizeMemory(void *ptr, unsigned int oldSize, unsigned int newSize)
char **resizeDblePtrMem(char **ptr, unsigned int oldSize, unsigned int newSize)
int exitShell(data_shell *datash)
void handleCtrlC(int sig)

char *concatenateStrings(char *dest, const char *src)
char *copyString(char *dest, char *src)
int compareStrings(char *s1, char *s2)
char *findCharacter(char *s, char c)
int countAcceptedBytes(char *s, char *accept)
char *duplicateString(const char *s)
int getStringLength(const char *s)

int compareStrings(char str[], const char *delim)
char *tokenizeString(char str[], const char *delim)
int isDigit(const char *s)

void reverseString(char *s)
int charRepetitions(char *input, int i)
int syntaxErrorPosition(char *input, int i, char last)
int firstChar(char *input, int *i)

void printSyntaxError(data_shell *datash, char *input, int i, int bool)
int checkSyntaxError(data_shell *datash, char *input)
void checkIfEnvVariable(r_var **h, char *in, data_shell *data)
int checkVariable(r_var **h, char *in, char *st, data_shell *data)
char *convertToVariables(r_var **head, char *input, char *new_input, int nlen)
char *replaceVariables(char *input, data_shell *datash)













second part:

char *char_swap(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void next_cmd_line(sep_list **list_s, line_list **list_l, data_shell *datash);
int command_split(data_shell *datash, char *input);
char **tokenize_line(char *input);

int execute_line(data_shell *datash);

int searchable_cdir(char *path, int *i);
char *locate_cmd(char *cmd, char **_environ);
int check_executable(data_shell *datash);
int check_cmd_err(char *dir, data_shell *datash);
int exe_cmd(data_shell *datash);

int comp_env_names(const char *nenv, const char *name);
char *_getenv(const char *name, char **_environ);
int env_printer(data_shell *datash);

char *info_cp(char *name, char *value);
void environ_set(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

void par_cd(data_shell *datash);
void cd_to(data_shell *datash);
void cd_prev(data_shell *datash);
void cd_home(data_shell *datash);

int change_dir(data_shell *datash);
int (*get_built_in(char *cmd))(data_shell *datash);


int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

char *cd_strcat(data_shell *, char *, char *, char *);
char *get_cd_err(data_shell *datash);
char *not_found_err(data_shell *datash);
char *exit_shell_err(data_shell *datash);

char *error_get_alias(char **args);
char *env_err(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *path_denied_err(data_shell *datash);

int err_get(data_shell *datash, int eval);



void _help_env(void);
void _help_setenv(void);
void _help_unsetenv(void);
void _help_general(void);
void _help_exit(void);

void _help(void);
void _help_alias(void);
void _help_cd(void);

int help_get(data_shell *datash);

#endif
