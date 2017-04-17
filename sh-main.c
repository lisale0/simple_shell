#include "shell.h"

/**
 * main - main function
 *
 * Return: Always 0 for success
 */
int main(void)
{
	char **ep;
	env_t *envlist = NULL;
	char **patharr;

	for (ep = environ; *ep != NULL; ep++)
	{
		add_nodeenv_end(&envlist, *ep);
	}
	patharr = parse_path(envlist);
	prompt_user(&envlist, patharr);
	free_dblechar(patharr);
	freeenvlist(&envlist);
	return (0);
}

/**
 * prompt_user - prompts the user for command or pipe in commands to file
 * @envlist: linkedlist of environment vars
 * @patharr: an array of path tokenized
 *
 * Return: none
 */
void prompt_user(env_t **envlist, char **patharr)
{
	size_t n;
	int retval = 1, pipe = 0;
	char *path;
	char *line = NULL;
	char **arg;
	struct stat sb;

	if (fstat(STDIN_FILENO, &sb) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	/**
	 *determine if this is a non-interactive mode
	 */
	switch (sb.st_mode & S_IFMT)
	{
	case S_IFIFO:
		pipe = 1;
		break;
	}
	if (pipe == 0)
		printf("$ ");
	while ((retval = getline(&line, &n, stdin)) != -1)
	{
		if (line[0] == 10)
		{
			write(1, "$ ", 2);
			continue;
		}
		if (retval < 0)
			break;
		arg = split_line(line);
		/*
		if (access(arg[0], X_OK) == 0 && !(build_path(arg[0], patharr, &path)))
		*/
		if (access(arg[0], X_OK) == 0)
		{
			path = _strdup(arg[0]);
		}
		else
			build_path(arg[0], patharr, &path);
		execute_arg(envlist, arg, path);
		if (arg != NULL)
		{
			freearg(arg);
		}
		if (pipe == 0)
			write(1, "$ ", 2);
		free(path);
	}
	free(line);
}

/**
 * split_line - splitting the input line into 2D array, set up for execvp
 * @line: the line passed in for parsing
 *
 * Return: 2D array, array of strings
 */
char **split_line(char *line)
{
	int i = 0;
	int size = TOKSIZE, oldsize;
	char **tokens;
	char *token;
	char *delim = " \t\n\r\"";

	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
	{
		perror("failed to allocate memory for tokens\n");
		return (NULL);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		if (i >= size)
		{
			oldsize = size;
			size += BUFSIZE;
			tokens = _realloc(tokens, oldsize, sizeof(char *) * size);
			if (tokens == NULL)
			{
				perror("tokenize fail");
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
/**
 * check_builtin - check if the command is a builtin
 * @arg: the arguments passed in from user
 *
 * Return: 1 if builtin command, 0 otherwise
 */
int check_builtin(char **arg, env_t **envlist)
{
	int i;

	bt_t builtin[] = {
		{"cd", exec_cd},
		{"env", exec_env},
		{"exit", exec_exit},
		{"setenv", exec_setenv},
		{"unsetenv", exec_unsetenv},
		{"\n", exec_nl},
		{NULL, NULL}
	};
	for (i = 0; builtin[i].builtin != NULL; i++)
	{
		if (arg[0] && _strcmp(arg[0], builtin[i].builtin) == 0)
		{
			builtin[i].f(envlist, arg[0], arg);
			return (1);
		}
	}
	return (0);
}
/**
 * execute_arg - execute the arguments passed in
 * @envlist: linkedlist envlist
 * @arg: arguments passed in
 * @path: the path that command is part of
 *
 * Return: 1 if passed, otherwise -1 if failed
 */

int execute_arg(env_t **envlist, char **arg, char *path)
{
	pid_t child_pid;
	int status;
	int checkretval;

	checkretval = check_builtin(arg, envlist);
	if (checkretval == 1)
		return (1);
	/**converting linked list to*/
	/**envptr = envl_to_dptr(envlist);*/
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("hsh error - child is -1");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(path, arg, environ) == -1)
		{
			perror("hsh execve fail");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	return (1);
}
