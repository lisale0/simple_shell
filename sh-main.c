#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>
#define BUFSIZE 1024
#define DELIM " \t\n"
void prompt_user();
char **split_line(char *line);
int execute_arg(char **arg);
int main()
{
	prompt_user();
	return (0);
}

void prompt_user()
{
	char *line = NULL;
	size_t n;
	char **arg;
	/**size_t retval;*/
	while (1)
	{
		/**get the line*/
		printf("$ ");
        	getline(&line, &n, stdin);
		arg = split_line(line);
		execute_arg(arg);
	}

}
char **split_line(char *line)
{
	int i = 0;
	int size = BUFSIZE;
	char **tokens;
	char *token;
	char delim[3] = " \t\n";

	tokens = malloc(sizeof(char*) * size);
	if (tokens == NULL)
		printf("failed to allocate meory for tokens\n");
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		/**printf("%d %s\n", i, tokens[i]);*/
		i++;
		if (i >= size)
		{
			size += BUFSIZE;
			tokens = realloc(tokens, sizeof(char*) * size);
			if (tokens == NULL)
			{
				printf("failed to allocate meory for tokens\n");
			}
		}
		/**Move onto the next token*/
		token = strtok(NULL, delim);
	}
	/**making the last one null*/
	tokens[i] = NULL;
	/*(printf("%s", tokens[i]);*/
	return (tokens);
}
int execute_arg(char **arg)
{
	pid_t child_pid;
	int status;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		/**child process was created successfully*/
		if (execvp(arg[0], arg) == -1)
		{
			perror("hsh error:");
		}
		exit(EXIT_FAILURE);

	}
	else
	{
		wait(&status);
		/*
		do
		{
			wpid = waitpid(child_pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		*/
		/**
		 *WIFEXITED - This macro returns a nonzero
		 * value if the child process terminated normally
		 * with exit or _exit.
		 */

		/**
		 * WIFSIGNALED
		 * This macro returns a nonzero value if the child process
		 * terminated because it received a signal that was not handled.
		 *See Signal Handling.
		 */

	}
	return 1;
}
