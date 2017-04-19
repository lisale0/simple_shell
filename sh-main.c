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
	int retval = 1, pipe = 0, buildret = 0;
	char *path, *line = NULL;
	char **arg;
	struct stat sb;

	if (fstat(STDIN_FILENO, &sb) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
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
		if (check_space(line[0]) == 1)
			continue;
		if (retval < 0)
			break;
		arg = split_line(line);
		if (check_exit(arg[0], &arg, &line) == 1)
			return;
		if (check_builtin(&arg, envlist) == 1)
			continue;

		
		if (access(arg[0], F_OK) == 0)
		{
                        execute_arg(envlist, arg, arg[0]); write(1, "$ ", 2);
			free(arg);
			continue;
		}
		else
			buildret = build_path(arg[0], patharr, &path);

		if (buildret == 1)
			execute_arg(envlist, arg, path);
		else
		{
			write(1, "$ ", 2);
			continue;
		}
		if (pipe == 0)
			write(1, "$ ", 2);
		free(arg); free(path);
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
 * execute_arg - execute the arguments passed in
 * @envlist: linkedlist envlist
 * @arg: arguments passed in
 * @path: the path that command is part of
 *
 * Return: 1 if passed, otherwise -1 if failed
 */

int execute_arg(__attribute__((unused))env_t **envlist, char **arg, char *path)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("hsh error - child is -1");
		exit(-1);
	}
	if (child_pid == 0)
	{
		if((execve(path, arg, environ)) == -1)
		{
			perror("hsh");
			exit(EXIT_FAILURE);
			return (0);
		}
	}
	else
		wait(&status);
	return (1);
}
