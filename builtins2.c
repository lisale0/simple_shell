#include "shell.h"

int exec_nl(__attribute__((unused))env_t **envlist,
	    __attribute__((unused))char *cmd, __attribute__((unused)) char **arg)
{
	printf("i am a newline");
	return (1);
}
