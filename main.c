#include "main.h"
/**
 * main - basic shell
 *
 * @ac: numbers of arguments
 * @av: list of arguments
 * Return: 0 if success
 */
int main(int ac, char **av)
{
	char *lineptr, *token, *delim = " \n";
	int i, status;
	pid_t child_pid;
	ssize_t prompt_line;
	size_t n = 0;
	(void)ac;

	while (1)
	{
		printf("$ ");
		prompt_line = getline(&lineptr, &n, stdin);
		if (prompt_line == -1)
		{
			printf("EXIT...\n");
			exit(99);
		}
		token = strtok(lineptr, delim);

		i = 0;
		while (token != NULL)
		{
			av[i++] = token;
			token = strtok(NULL, delim);
		}
		child_pid = fork();

		if (child_pid == 0)
		{
			if (av)
				exec_cmd(av);

			exit(0);
		}
		else
			wait(&status);
	}
	free(lineptr);
	return (0);
}
