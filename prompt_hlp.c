#include "shell.h"

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
int check_space(char *cmd)
{
	if (cmd == 10)
	{
		write(1, "$ ", 2);
		return (1);
	}
	return (0);
}
