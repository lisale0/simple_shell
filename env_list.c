#include "shell.h"
void add_nodeenv(env_t **envlist, char *env)
{
        env_t *newNode;
        char *key, *value;
        env_t *temp;

	if (envlist == NULL || env == NULL)
                return;

        newNode = malloc(sizeof(env_t));
        if (newNode == NULL)
                return;

	key = strtok(env, "=");
        value = strtok(NULL, "=");
        newNode->key = strdup(key);
	newNode->value = strdup(value);

        if (*envlist == NULL)
	{
                *envlist = newNode;
                newNode->next = NULL;
                return;
	}
        temp = *envlist;
	while (temp->next != NULL)
        {
                temp = temp->next;
	}
        temp->next = newNode;
	newNode->next = NULL;
	return;
}

size_t print_listenv(const env_t *h)
{
        int i;

        i = 0;
	while (h != NULL)
        {
                printf("Key: %s\n", h->key);
                printf("Value: %s\n", h->value);
                h = h->next;
                i++;
	}
        return (i);
}
