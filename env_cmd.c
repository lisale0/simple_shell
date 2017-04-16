#include "shell.h"
/**
 * _getenv - get an environment variable
 *
 * Return: returns a pointer to the value in the  environment,
 * or NULL if there is no match.
 */
env_t *_getenv(env_t *envlist, char *name)
{
	env_t *temp;

	temp = envlist;
	while(temp != NULL)
	{
		if (_strcmp(temp->key, name) == 0)
			return (temp);
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
int _setenv(env_t **envlist, char *name, char *value)
{
	env_t *temp;
	int found = 0, len;
	char *env;

	len = _strlen(name) + _strlen(value) + 3;
	env = malloc(sizeof(char) * len);
	if (env == NULL)
		return (-1);
	temp = *envlist;
	/**Find is this key exists currently in the environment*/
       while(temp != NULL)
        {
		if (_strcmp(temp->key, name) == 0)
		{
			temp->value = _strdup(value);
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
                add_nodeenv_end(envlist, env);
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
int _unsetenv(env_t **envlist, char *name)
{
	env_t *deleteNode, *temp;

	if (*envlist == NULL)
		return (-1);
	temp = *envlist;
	while (temp != NULL)
	{
		if (_strcmp((temp->key), name) == 0)
		{
			deleteNode = temp;
			temp = deleteNode->next;
			free(deleteNode);
			return (1);
		}
		if (temp->next == NULL)
		{
			perror("env does not exist");
			return (-1);
		}
		if (_strcmp((temp->next)->key, name) == 0)
		{
			deleteNode = temp->next;
			temp->next = deleteNode->next;
			free(deleteNode);
			return (1);
		}
		temp = temp->next;
	}
	perror("Path name does not exist");
	return (-1);
}
