#include "shell.h"

/**
 * main - main function
 *
 * Return: Always 0 for success
 */
int main()
{
	/*adding structlist*/
        char **ep;
	env_t *envlist = NULL;

	/*envlist = NULL;*/
        for (ep = environ; *ep != NULL; ep++)
        {
                add_nodeenv_end(&envlist, *ep);
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

	prompt_user(&envlist);
	/*this frees what I want*/
	freeenvlist(&envlist);
	//free(structlist);
	return (0);
}

void prompt_user(env_t **envlist)
{
	char *line = NULL;
	size_t n;
	int retval = 1;
	char **arg;
	struct stat sb;
	int pipe = 0;

	if (fstat(STDIN_FILENO, &sb) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
        }

	/**
	 *determine if this is a non-interactive mode*/

	switch (sb.st_mode & S_IFMT)
	{
	case S_IFIFO:  pipe = 1;
		break;
	}
	if (pipe == 0)
		printf("$ ");
	while ((retval = getline(&line, &n, stdin)) != -1)
	{
		/**
		 * get the line
		 */
		/**
		 *if return value for getline fails return,
		 * do not continue on with the function
		 **/
		if (retval < 0)
			break;
		arg = split_line(line);
		execute_arg(envlist, arg);

		if (arg != NULL)
			freearg(arg);

		if (pipe == 0)
			printf("$ ");
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
	int size = TOKSIZE;
	char **tokens;
	char *token = "";
	char *delim = " \t\n";

	tokens = malloc(sizeof(char*) * size);

	if (tokens == NULL)
	{
		printf("failed to allocate meory for tokens\n");
		return NULL;
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		if (i >= size)
		{
			size += BUFSIZE;
			tokens = realloc(tokens, sizeof(char*) * 2);
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
 *
 */
int check_builtin(char **arg)
{
	int i;

	bt_t builtin[] = {
		{"cd", exec_cd},
		{"exit", exec_exit},
		{NULL, NULL}
	};

	for (i = 0; builtin[i].builtin != NULL; i++)
	{
		if (arg[0] && strcmp(arg[0], builtin[i].builtin) == 0)
			{
				builtin[i].f(arg[0], arg);
			}
		return (0);
	}

	return (1);
}
/**
 * execute_arg - execute the arguments passed in
 * @arg: arguments passed in
 *
 * Return: 1 if passed, otherwise -1 if failed
 */
// check if builtin

int execute_arg(env_t **envlist, char **arg)
{
	pid_t child_pid;
	int status, i;
	char **envptr;

	/**converting linked list to***/
	//envptr = envl_to_dptr(envlist);
	cmds_t cmd[] = {
		{"env", exec_env},{"setenv", exec_setenv},
		{NULL, NULL}
	};
//	cmd[0].f(envlist, arg[0], arg);
	child_pid = fork();
	for (i = 0; cmd[i].cmd != NULL; i++)
	{
		if (arg[0] && strcmp(arg[0],cmd[i].cmd) == 0)
		{
			cmd[i].f(envlist, arg[0], arg);
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
				if (execve(arg[0], arg, environ) == -1)
					perror("hsh error");
				exit(EXIT_FAILURE);
			}
			else
				wait(&status);
		}
	}

	//freeptrenv(envptr);
	return 1;
}
