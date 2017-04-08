#include "shell.h"
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

size_t print_listenv(const structlist_t *structlist)
{
        int i;
	env_t *temp;
        i = 0;

	temp = structlist->envlist;
	while (temp != NULL)
        {
                printf("Key: %s = ", temp->key);
                printf("Value: %s\n", temp->value);
                temp = temp->next;
                i++;
	}
        return (i);
}
