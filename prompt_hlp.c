#include "shell.h"

/**
 * check_exit - check if the command is an exit
 * @cmd: the command passed in to check against
 * @arg: the arguments passed in to free
 * @line: the line passed in to free
 *
 * Return: int, 1 if true, 0 if false
 */
int check_exit(char *cmd, char ***arg, char **line)
{
	if (_strcmp(cmd, "exit") == 0)
	{
		free(*arg);
		free(*line);
		return (1);
	}
	return (0);
}
/**
 * check_space - check if command is space
 * @cmd: the command passed in to check against
 *
 * Return: int, 1 if true, 0 if false
 */
int check_space(int cmd)
{
	if (cmd == 10)
	{
		write(1, "$ ", 2);
		return (1);
	}
	return (0);
}

/**
 * check_builtin - check if the command is a builtin
 * @arg: the arguments passed in from user
 * @envlist: the linked list with env variables
 * Return: 1 if builtin command, 0 otherwise
 */
int check_builtin(char ***arg, env_t **envlist)
{
	int i;

	bt_t builtin[] = {
                {"cd", exec_cd}, {"env", exec_env},
                {"exit", exec_exit}, {"setenv", exec_setenv},
                {"unsetenv", exec_unsetenv}, {"\n", exec_nl},
                {NULL, NULL}
        };
        for (i = 0; builtin[i].builtin != NULL; i++)
        {
                if ((*arg)[0] && _strcmp((*arg)[0], builtin[i].builtin) == 0)
                {
                        builtin[i].f(envlist, (*arg)[0], *arg);
			write(1, "$ ", 2);
			free(*arg);
                        return (1);
                }
        }
        return (0);
}

int execute_cmd(env_t **envlist, char **arg, char *cmd)
{
	/**if executable and not ./ in cwd**/
	if (access(cmd, X_OK) == 0 && (cmd[0] != '.' && cmd[1] != '/'))
	{
		
	}
}
