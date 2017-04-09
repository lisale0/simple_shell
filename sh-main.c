#include "shell.h"

/**
 * main - main function
 *
 * Return: Always 0 for success
 */
int main()
{
	/*adding structlist*/
	structlist_t *structlist;
        char **ep;
	structlist->envlist = NULL;

        for (ep = environ; *ep != NULL; ep++)
        {
                add_nodeenv_end(&structlist, *ep);
        }

	/**
	 * having issues with this call
	 */
	/**_setenv(&structlist, "HELLLO", "WOOORRRLLDDD"); */
	/**
	 * print_listenv is used to test is nodes are getting added correctly
	 */
	/**print_listenv(structlist);*/
	prompt_user();
	return (0);
}

/**
 * prompt_user - prompts the user for input
 * Return: none
 */
void prompt_user()
{
	char *line = NULL;
	size_t n;
	char **arg;
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
		token = strtok(NULL, delim);
	}
 	/**making the last one null*/
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_arg - execute the arguments passed in
 * @arg: arguments passed in
 *
 * Return: 1 if passed, otherwise -1 if failed
 */
int execute_arg(char **arg)
{
	pid_t child_pid;
	int status;


	if (strcmp(arg[0], "cd") == 0)
	{
		if (chdir(arg[1]) != 0)
		{
			perror("hsh error");
		}
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("hsh error");
			return (-1);
		}
		if (child_pid == 0)
		{
			if (execvp(arg[0], arg) == -1)
			{
				perror("hsh error");
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	return 1;
}
