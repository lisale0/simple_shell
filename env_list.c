#include "shell.h"
/**
 * add_nodeenv_end - adding an environment variable to the end of the
 * linked list
 * @structlist: struct pointer to struct env_t
 * @env: contains environment information to break down
 *
 * Return:none
 */
void add_nodeenv_end(structlist_t **structlist, char *env)
{
        env_t *newNode;
        char *key, *value;
        env_t *temp;

	if ( env == NULL)
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
        newNode->key = strdup(key);
	newNode->value = strdup(value);

        if ((*structlist)->envlist == NULL)
	{
                (*structlist)->envlist = newNode;
                newNode->next = NULL;
                return;
	}
        temp = (*structlist)->envlist;
	while (temp->next != NULL)
        {
                temp = temp->next;
	}
        temp->next = newNode;
	newNode->next = NULL;
	return;
}
/**
 * print_listenv - function to print the linked list of environment variables
 * @structlist: struct pointer to struct env_t
 *
 * Return:size_t, number of nodes in the list
 */
size_t print_listenv(structlist_t *structlist)
{
        int i;
	env_t *temp;
        i = 0;

	temp = structlist->envlist;
	while (temp != NULL)
        {
                printf("%s", temp->key);
                printf("=%s\n", temp->value);
                temp = temp->next;
                i++;
	}
        return (i);
}
