#include "main.h"
/**
 * exec_cmd - execute the command if it exist
 *
 * @av: array of arguments.
 *
 * Return: void
 */
void exec_cmd(char **av)
{
	int j = 0;
	struct stat st;

	while (av[j])
	{
		if (stat(av[j], &st) == 0)
		{
			if (execve(av[j], av, NULL) == -1)
			{
				perror("execve");
				exit(99);
			}
		}
		else
			printf("Command doesn't exist\n");
		j++;
	}
}
