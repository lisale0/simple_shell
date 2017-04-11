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
	//printf("%d", (structlist->envlist)->count);
	/**
	 * having issues with this call
	 */
	//_unsetenv(&structlist, "PATH");
	/**
	 * print_listenv is used to test is nodes are getting added correctly
	 */
	//print_listenv(structlist);
	/**
	   _setenvtest(&structlist);*/
	/**print_listenv(structlist);*/
	prompt_user(&structlist);
	freeenvlist(&structlist);
	return (0);
}

/**
 * prompt_user - prompts the user for input
 * Return: none
 */
void prompt_user(structlist_t **structlist)
{
	char *line = NULL;
	size_t n;
	int retval;
	char **arg;
	struct stat sb;
	int fifo = 0;

	if (fstat(STDIN_FILENO, &sb) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
        }

	/**
	 *determine if this is a non-interactive mode*/
	switch (sb.st_mode & S_IFMT)
	{
	case S_IFIFO:  fifo = 1;
		break;
	}
	while (1)
	{
		/**
		 * get the line
		 */
		if (fifo == 0)
			printf("$ ");
        	retval = getline(&line, &n, stdin);
		/**
		 *if return value for getline fails return,
		 * do not continue on with the function
		 **/
		if (retval < 0)
			return;
		arg = split_line(line);
		execute_arg(structlist, arg);
	}
	free(line);
	freearg(&arg);
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
	int size = TOKSIZE;
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
 	/**
	 *making the last one null, set for execvp
	 */
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_arg - execute the arguments passed in
 * @arg: arguments passed in
 *
 * Return: 1 if passed, otherwise -1 if failed
 */
int execute_arg(structlist_t **structlist, char **arg)
{
	pid_t child_pid;
	int status, i;

	cmds_t cmd[] = {
		{"cd", exec_cd},{"env", exec_env},{"setenv", exec_setenv},
		{NULL, NULL}
	};
	child_pid = fork();
	for (i = 0; cmd[i].cmd != NULL; i++)
	{
		if (strcmp(arg[0],cmd[i].cmd) == 0)
		{
			cmd[i].f(structlist, arg[0], arg);
		}
		else
		{
        		if (child_pid == -1)
			{
				perror("hsh error");
				return (-1);
			}
			if (child_pid == 0)
			{
				if (execvp(arg[0], arg) == -1)
					perror("hsh error");
				exit(EXIT_FAILURE);
			}
			else
				wait(&status);
		}
	}
	return 1;
}
