#include "shell.h"
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
		{
			return (temp->value);
		}
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
	int found = 0;
	char *env;

	temp = (*structlist)->envlist;
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
		/**
		env = _strcat(env, name);
		env = _strcat(env, "=");
		env = _strcat(env, value);
		*/

		/**
		 * Problem: seg faulting here with add_nodeenv_end
		 * outside of this add_nodeenv_end works
		 */
		/*
		env ="HELLO=World";
		printf("%s", env);
		add_nodeenv_end(structlist, env);
		*/
	}
	return (-1);
}
