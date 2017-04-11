#include "shell.h"
#include <stdio.h>
void exec_cd(structlist_t **structlist, char *cmd, char **arg)
{
	chdir(arg[1]);
}
void exec_env(structlist_t **structlist,
__attribute__((unused))char *cmd, __attribute__((unused))char **arg)
{
	print_listenv(*structlist);
}
