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
	char *copy_path = _getenv("PATH", env), *token;
	char copy_cmd[150];

	if (cmd[0] == '/' || (cmd[0] == '.'))
	{
		if (stat(cmd, &st) == 0)
		{
			free(copy_path);
			return (strdup(cmd));
		}
	}
	token = strtok(copy_path, ":");
	do
	{
		strcpy(copy_cmd, token);
		strcat(copy_cmd, "/");
		strcat(copy_cmd, cmd);

		if (stat(copy_cmd, &st) == 0)
		{
			free(copy_path);
			return (strdup(copy_cmd));
		}
		else
			copy_cmd[0] = 0;

		token = strtok(NULL, ":");
	} while (token != NULL);
	free(copy_path);
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
