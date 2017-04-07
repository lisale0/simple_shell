#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#define BUFSIZE 1024
#define DELIM " \t\n"
void prompt_user();
char **split_line(char *line);
int execute_arg(char **arg);
int main(int argc, char **argv, char **envp)
{
	size_t i;
	int status;

	prompt_user();
	return (0);
}

void prompt_user()
{
	char *line;
	size_t n = (size_t )BUFSIZE;
	char **arg;
	ssize_t linesize;
	int stat;
	do
	{
		printf("$");
		//get the line
		line = _getline();
		arg = split_line(line);
		stat = execute_arg(arg);
	}while (stat);

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
		//printf("%d %s\n", i, tokens[i]);
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
		/*Move onto the next token*/
		token = strtok(NULL, delim);;
	}
	/*making the last one null*/
	tokens[i] = NULL;
	//printf("%s", tokens[i]);
	return (tokens);
}
int execute_arg(char **arg)
{
	pid_t child_pid, wpid;
	int status;
	pid_t tpid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		/*child process was created successfully*/
		execvp(arg[0], arg);
		/*have something to handle error*/
		printf("known command\n");
//		exit(0);
	}
	else
	{
		/*this portion is runned by parent*/
/*
		do
		{
			tpid = wait(&status);
			if (tpid != child_pid)
				process_terminated(tpid);
		}while(tpid != child_pid);
//		return (status);
*/
	}
	return 1;
}
