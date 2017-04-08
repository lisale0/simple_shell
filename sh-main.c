#include "shell.h"

extern char **environ;

int main( __attribute__((unused)) int argc,
__attribute__((unused))char **argv, __attribute__((unused)) char **env)
{
        char **ep;

	env_t *envlist = NULL;

        for (ep = environ; *ep != NULL; ep++)
        {
                add_nodeenv_end(&envlist, *ep);
        }
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
			return (1);
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
