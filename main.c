#include "main.h"

/**
 * main - simple shell
 * @ac: number of arguments
 * @av: array of arguments
 * @env: array of environment variables
 * Return: 0, 1, 2 or exit value
 */
int main(int ac, char **av, char **env)
{
	size_t bufsize = 0;
	char *buffer = NULL;
	int nb_cmd = 1, status = 0;

	if (signal(SIGINT, sigintHandler) == SIG_ERR)
		return (1);

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		non_interactive(av[0], buffer, bufsize, nb_cmd, env, &status);
		return (status);
	}

	while (1)
	{
		interactive(av[0], buffer, bufsize, nb_cmd, env, &status);
		nb_cmd++;
	}
	(void)ac;
	return (0);
}

/**
 * inter - execute the simple shell in normal mode
 * @name: name of the executable
 * @buffer: buffer receiving getline
 * @bufsize: size of the buffer
 * @nb_cmd: number of command executed
 * @env: environment variables
 * @status: status of function
 */
void interactive(char *name, char *buffer, size_t bufsize, int nb_cmd, char **env,
			int *status)
{
	int prompt_line = 0, i = 0, check = 0;

	printf("$ ");
	prompt_line = getline(&buffer, &bufsize, stdin);
	if (prompt_line == -1)
	{
		printf("\n");
		if (buffer)
			free(buffer);
		exit(*status);
	}
	if (prompt_line > 0)
		buffer[prompt_line - 1] = '\0';
	if (*buffer)
	{
		while (buffer[i])
			i++;
		if (i > 0)
		{
			if (buffer[i - 1] == ' ')
				buffer[i] = '\0';
		}
		else
			buffer[0] = '\0';
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] != ' ')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			execute_cmd(buffer, name, nb_cmd, env, status);
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

/**
 * non_int - execute the simple shell in non interactive mode
 * @name: name of the executable
 * @buffer: buffer receiving getline
 * @bufsize: size of the buffer
 * @nb_cmd: number of command executed
 * @env: environment variables
 * @status: status of function
 */
void non_interactive(char *name, char *buffer, size_t bufsize, int nb_cmd, char **env,
				int *status)
{
	int prompt_line = 0, i = 0, check = 0;

	while ((prompt_line = getline(&buffer, &bufsize, stdin)) >= 0)
	{
		if (prompt_line > 0)
			buffer[prompt_line - 1] = '\0';
	if (*buffer)
	{
		while (buffer[i])
			i++;
		if (i > 0)
		{
			if (buffer[i - 1] == ' ')
				buffer[i] = '\0';
		}
		else
			buffer[0] = '\0';

		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] != ' ')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			execute_cmd(buffer, name, nb_cmd, env, status);
	}
		free(buffer);
		buffer = NULL;
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

/**
 * sigintHandler - if Ctrl+C is pressed
 * @sig: signal sent to the function
 */
void sigintHandler(int sig)
{
	printf("\n");
	printf("$ ");
	(void)sig;
}
