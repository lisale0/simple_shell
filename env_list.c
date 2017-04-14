#include "shell.h"
/**
 * add_nodeenv_end - adding an environment variable to the end of the
 * linked list
 * @structlist: struct pointer to struct env_t
 * @env: contains environment information to break down
 *
 * Return:none
 */
void add_nodeenv_end(env_t **envlist, char *env)
{
        env_t *newNode;
        char *key, *value;
        env_t *temp;

	if (env == NULL)
	{
                return;
	}
        newNode = malloc(sizeof(env_t));
        if (newNode == NULL)
                return;
	key = strtok(env, "=");
	/**
	 * need to fix this, there is a more elegant way to do this
	 */
	if (strcmp(key, "LS_COLORS") == 0)
		value = strtok(NULL, "");
	else
		value = strtok(NULL, "=");

        newNode->key =  strdup(key);
	newNode->value = strdup(value);
        if (*envlist == NULL)
	{
                *envlist = newNode;
                newNode->next = NULL;
		(*envlist)->count += 1;
                return;
	}
        temp = *envlist;
	while (temp->next != NULL)
        {
                temp = temp->next;
	}
        temp->next = newNode;
	newNode->next = NULL;
	(*envlist)->count += 1;
	return;
}
/**
 * print_listenv - function to print the linked list of environment variables
 * @structlist: struct pointer to struct env_t
 *
 * Return:size_t, number of nodes in the list
 */
size_t print_listenv(env_t *envlist)
{
        int i;
	env_t *temp;
	char *buff = "";
	int slen = 0;
	int listcount;

	i = 0;
	temp = envlist;
	listcount = temp->count;
	while (temp != NULL)
        {
		slen += _strlen(temp->key) + _strlen(temp->value) + 20;
		temp = temp->next;
	}
	buff = malloc(slen * sizeof(char));
	if (buff == NULL)
	{
		printf("broken\n");
		return (-1);
	}
	temp = envlist;
        while (temp != NULL)
	{
		/*
		printf("printinf buff %s\n", buff);
		*/
                buff = strcat(buff, temp->key);
                buff = strcat(buff, "=");

                buff = strcat(buff, temp->value);

		if (i != listcount)
			buff = strcat(buff, "\n");


		printf("----------\n");
		printf("i: %d ", i);
		printf("temp->count %d\n", listcount);

		/*
		printf("%s\n", buff);
		printf("-------------------------------\n");
		*/
                i++;
		temp = temp->next;
	}

	buff = strcat(buff, "\0");

	printf("%s", buff);
/*
	write(1, buff, 4000);
*/
/*
	printf("strlen of buff %d\n", _strlen(buff));
	printf("buff test with printf %s\n", buff);
*/
/*
	write(1, buff, slen);
*/
	free(buff);
        return (i);
}
