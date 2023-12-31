#include "main.h"
/**
 * parse_cmd - parse the string and execute the command
 *
 * Desrciption: check if it's a environment variable 'env' or if is a variable
 * in a PATH.
 *
 * @name: name of command
 * @buffer: string pass in the buffer
 * @env: array of environement variable
 * @nb_cmd: number of command passed in the prompt
 * @status: status of function
 */
void parse_cmd(char *buffer, char *name, int nb_cmd, char **env,
			   int *status)
{
	int i = 0;
	char *copy_cmd, **cmd, *token;

	cmd = malloc(sizeof(char *) * 1024);
	token = strtok(buffer, " \n\t");

	while (token != NULL)
	{
		cmd[i++] = token;
		token = strtok(NULL, " \n\t");
	}

	cmd[i] = NULL; /* put a null pointer at the end */
	copy_cmd = strdup(cmd[0]);

	if (check_env(copy_cmd, env) != 0)
	{
		cmd[0] = _which(copy_cmd, env); /* check PATH */
		if (!cmd[0])
			cmd_null(name, buffer, cmd, copy_cmd, nb_cmd, status);
		else
		{
			exe_cmd(cmd, name, env);
			wait(status);
		}
		if (*status != 127)
			*status /= 256;
		free(cmd[0]);
	}
	free(cmd);
	free(token);
	free(copy_cmd);
}

/**
 * check_env - Check env command
 *
 * @copy_cmd: The command
 * @env: The environment variables
 * Return: 0 if success
 */

int check_env(char *copy_cmd, char **env)
{
	int i;

	if (strcmp(copy_cmd, "env") == 0)
	{
		for (i = 0; env[i]; i++)
			printf("%s\n", env[i]);
		return (0);
	}
	else
		return (1);
}
/**
 * exe_cmd - execute the command
 * @cmd: array of the command and arguments
 * @name: name of the executable
 * @env: environment variables
 */
void exe_cmd(char **cmd, char *name, char **env)
{
	if (fork() == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			perror(name);
			exit(-1);
		}
	}
}

/**
 * cmd_null - executed if a command isn't in PATH
 * @name: name of the executable
 * @str: original string of command typed
 * @cmd: the command to execute
 * @copy_cmd: copy of the command
 * @nb_cmd: number of command typed
 * @status: status of function
 */
void cmd_null(char *name, char *str, char **cmd, char *copy_cmd, int nb_cmd,
			  int *status)
{
	int value = 0;


	if (strcmp(copy_cmd, "exit") == 0)/*check exit command*/
	{
		value = exit_value(cmd[1]);
		if (value == -1)
		{
			*status = 512;
			printf("%s: %d: exit: Illegal number: %s\n", name, nb_cmd, cmd[1]);
		}
		else
		{
			free(cmd[0]);
			free(cmd);
			free(copy_cmd);
			if (str)
				free(str);
			if (value == -2)
				exit(*status);
			exit(value);
		}
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", name, nb_cmd, copy_cmd);
		*status = 127;
	}
}

/**
 * exit_value - calculate the exit value
 *
 * @n: supposed value of exit
 * Return: -1 for illegal numbers or a number between 0 and 255
 */
int exit_value(char *n)
{
	unsigned int nb = 0;

	if (!n)
		return (-2);

	for (; *n; n++)
	{
		if (*n < '0' || *n > '9')
			return (-1);

		nb = nb * 10 + (*n - '0');

		if (nb > 2147483648)
			return (-1);
	}

	while (nb > 255)
		nb -= 256;

	return (nb);
}
