#include "main.h"

/**
 * _which - find the path of a command
 * @cmd: command
 * @env: environment variables
 * Return: string of the path
 */
char *_which(char *cmd, char **env)
{
	struct stat st;
	char *s = strdup(_getenv("PATH", env)), *p;
	char t[150];

	if (cmd[0] == '/' || (cmd[0] == '.'))
	{
		if (stat(cmd, &st) == 0)
		{
			free(s);
			return (strdup(cmd));
		}
	}
	p = strtok(s, ":");

	do {
		strcpy(t, p);
		strcat(t, "/");
		strcat(t, cmd);

		if (stat(t, &st) == 0)
		{
			free(s);
			return (strdup(t));
		}
		else
			t[0] = 0;

		p = strtok(NULL, ":");
	} while (p != NULL);
	free(s);
	return (NULL);
}
/**
 * _getenv - find the environment variable
 * @name: environment variable
 * @env: array of environment variables
 * Return: pointer to the content of the environment variable
 */
char *_getenv(const char *name, char **env)
{
	int i, j;

	for (i = 0; env[i]; i++)
	{
		for (j = 0; env[i][j]; j++)
		{
			if (env[i][j] == name[j])
				continue;
			else if (env[i][j] == '=' && name[j] == '\0')
			{
				return (&env[i][j + 1]);
			}
			else
				break;
		}
	}
	return (NULL);
}
