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

	if (!isatty(STDIN_FILENO)) /* check interactive mode or not */
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
 * interactive - execute the simple shell in normal mode
 * and format string before execut.
 * @name: name of the executable
 * @lineptr: buffer receiving getline
 * @bufsize: size of the buffer
 * @nb_cmd: number of command executed
 * @env: environment variables
 * @status: status of function
 */

void interactive(char *name, char *lineptr, size_t bufsize, int nb_cmd,
				 char **env, int *status)
{
	int nb = 0, i = 0, check = 0;

	printf("$ ");
	nb = getline(&lineptr, &bufsize, stdin);
	if (nb == -1) /* getline fail*/
	{
		printf("\n");
		if (lineptr)
			free(lineptr);
		exit(*status);
	}
	if (nb > 0) /* getline not empty without null character */
		lineptr[nb - 1] = '\0'; /* add null character */
	if (*lineptr)
	{
		while (lineptr[i])
			i++;
		if (i == 0)
			lineptr[0] = '\0';
		for (i = 0; lineptr[i]; i++)
		{/* check if there are another character as space */
			if (lineptr[i] != ' ')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			parse_cmd(lineptr, name, nb_cmd, env, status);
	}
	if (lineptr)
	{
		free(lineptr);
		lineptr = NULL;
	}
}

/**
 * non_interactive - execute the simple shell in non interactive mode
 * @name: name of the executable
 * @buffer: buffer receiving getline
 * @bufsize: size of the buffer
 * @nb_cmd: number of command executed
 * @env: environment variables
 * @status: status of function
 */
void non_interactive(char *name, char *buffer, size_t bufsize, int nb_cmd,
					 char **env, int *status)
{
	int nb = 0, i = 0, check = 0;

	while ((nb = getline(&buffer, &bufsize, stdin)) >= 0)
	{
		if (nb > 0)
			buffer[nb - 1] = '\0';
		if (*buffer)
		{
			while (buffer[i])
				i++;
			if (i == 0)
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
				parse_cmd(buffer, name, nb_cmd, env, status);
		}
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}
