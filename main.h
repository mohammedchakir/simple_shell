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

int cmpStrings(char str[], const char *delim)
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














int (*get_builtin(char *cmd))(data_shell *)
int gethelp(data_shell *datash)

int getlen(int n)
char *auxitoa(int n)
int atoi(char *s)

char *swapchar(char *input, int bool)
void addnodes(sep_list **head_s, line_list **head_l, char *input)
void nextcmdline(sep_list **list_s, line_list **list_l, data_shell *datash)
int cmdsplit(data_shell *datash, char *input)
char **tokenizeline(char *input)

int changedir(data_shell *datash)
void parcd(data_shell *datash)
void cdto(data_shell *datash)
void cdprev(data_shell *datash)
void cdhome(data_shell *datash)

int compenvnames(const char *nenv, const char *name)
char *getenv(const char *name, char **_environ)

int envprinter(data_shell *datash)
char *infocp(char *name, char *value)
void environset(char *name, char *value, data_shell *datash)
int setenv(data_shell *datash)
int unsetenv(data_shell *datash)

char *cdstrcat(data_shell *datash, char *message, char *err, char *str_var)
char *getcderr(data_shell *datash)
char *notfounderr(data_shell *datash)
char *exitshellerr(data_shell *datash)
char *enverr(data_shell *datash)
char *pathdeniederr(data_shell *datash)

int geterr(data_shell *datash, int eval)
int searchablecdir(char *path, int *i)
char *locatecmd(char *cmd, char **_environ)
int checkexecutable(data_shell *datash)
int checkcmderr(char *dir, data_shell *datash)
int execmd(data_shell *datash)
int executeline(data_shell *datash)

void helpenv(void)
void helpsetenv(void)
void helpunsetenv(void)
void helpgeneral(void)
void helpexit(void)
void help(void)
void helpalias(void)
void helpcd(void)












char *error_get_alias(char **args);

char *error_syntax(char **args);
char *error_permission(char **args);


#endif
