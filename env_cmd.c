#include "shell.h"
void _setenvtest();
/**
 * _getenv - get an environment variable
 *
 * Return: returns a pointer to the value in the  environment,
 * or NULL if there is no match.
 */
char *_getenv(const structlist_t *structlist, const char *name)
{
	env_t *temp;

	temp = structlist->envlist;
	while(temp != NULL)
	{
		if (strcmp(temp->key, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * _setenv - change or add if it does exist;
 * @name: the key of the environemental variable
 * @value: the new value
 *
 * Return: int, 1 if success, -1 if failed
 */
int _setenv(structlist_t **structlist, const char *name, const char *value)
{
	env_t *temp;
	int found = 0, len;
	char *env;

	len = _strlen(name) + _strlen(value) + 3;
	printf("%d", len);
	env = malloc(sizeof(char) * len);
	if (env == NULL)
		return (-1);
	temp = (*structlist)->envlist;
	/**Find is this key exists currently in the environment*/
       while(temp != NULL)
        {
		if (strcmp(temp->key, name) == 0)
		{
			temp->value = strdup(value);
			found = 1;
			break;
		}
		temp = temp->next;
        }
	if (found == 1)
	{
		return (1);
	}
	else
	{
		env = strcpy(env, name);
		env = _strcat(env, "=");
		env = _strcat(env, value);
                add_nodeenv_end(structlist, env);
		free(env);
	}
	return (-1);
}
/**
 * _unsetenv - removing an environment variables, specified by name
 * @name: the key to delete
 *
 * Return: 1 if successful delete, -1 if unsuccessful
 */
int _unsetenv(structlist_t **structlist, const char *name)
{
	env_t *deleteNode, *temp;

	if ((*structlist)->envlist == NULL)
		return (-1);
	temp = (*structlist)->envlist;
	while (temp != NULL)
	{
		if (strcmp((temp->next)->key, name) == 0)
		{
			printf("found key: %s name: %s\n", temp->key, name);
			deleteNode = temp->next;
			temp->next = deleteNode->next;
			free(deleteNode);
			return (1);
		}
		temp = temp->next;
	}
	return (-1);
}
