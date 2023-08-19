#include "main.h"
/**
 * main - basic shell
 *
 * @ac: numbers of arguments
 * @av: list of arguments
 * @env: list of environement variable
 * Return: 0 if success
 */
int main(int ac, char **av, char **env)
{
	char *lineptr = NULL, *token;
	ssize_t prompt_line;
	int i, nb_cmd = 1, status = 0;
	size_t n = 0;
	(void)ac;

	while (1)
	{
		if (signal(SIGINT, sigintHandler) == SIG_ERR)
			return (1);

		if (isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
			printf("$ ");

		prompt_line = getline(&lineptr, &n, stdin);
		if (prompt_line == -1)
		{
			if (lineptr)
				free(lineptr);
			exit(status);
		}
		token = strtok(lineptr, " \r\n\t");

		i = 0;
		while (token != NULL)
		{
			av[i++] = token;
			token = strtok(NULL, " \r\n\t");
		}

		if (av)
		{
			execute_cmd(av[0], *av, env, nb_cmd, &status);
			nb_cmd++;
		}
	}
	free(token);
	free(lineptr);
	return (0);
}

/**
 * sigintHandler - if Ctrl+C is pressed
 * @sig: signal sent to the function
 */
void sigintHandler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "$ ", 2);
	(void)sig;
}
