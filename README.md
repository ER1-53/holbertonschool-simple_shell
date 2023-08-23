# PROJECT: SIMPLE SHELL



### Description



The shell is the Linux command line interpreter. It provides an interface between the user and the kernel and executes commands.

It consists in creating an interactive system for command line interpretation. Interpretation takes place in several
stages:
- a prompt for command lines
- option management
- and their execution, if the command exists.




### Build With



* [![langage.C]][c.url]




## File Descriptions



* [AUTHORS](AUTHORS) - It lists the contributors of this project

* [man_1_simple_shell](man_1_simple_shell) - The Manual describing usage of the simple_shell

* [main.h](main.h) - The header file used in this project





## Requirement



### General

- Allowed editors: vi, vim, emacs

- All files were compiled on Ubuntu 20.04 LTS using gcc, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`

- Betty coding style is followed.

- The simple shell has no known memory leaks



### Installation

Designed to run on `Ubuntu 20.04 LTS`, the simple_shell can be installed as follows:

* Clone the current repository with the command: ```git clone "https://github.com/stephenmakenziwaweru/simple_shell.git"```

*  `cd` in to the cloned directory: ```cd simple_shell```

* Create an executable using: ```gcc -Wall -Werror -Wextra -pedantic *.c -o hsh```

* Run the executable either in interative mode `./hsh` or non-interactive mode `echo "pwd" | ./hsh`




## Synopsis


**Step 1: Interactive Mode** Before launching our program, we have the possibility to interact with the interactive mode or not. If the interactive mode is launched, we move on to step 2. The non-interactive mode allows command execution without direct access to the shell.

![non-interactif](https://zupimages.net/up/23/34/06dn.png)

**Step 2: The Main Loop** Our shell starts with setting up a main loop. At each iteration of this loop, the shell displays a prompt (for example, "$ "), waits for the user’s input, and reads the command entered.

**Step 3: Order Analysis** The program implements a function to analyze the command entered by the user. This function divides the command line into tokens (words) based on spaces. The first token is usually the command name, and the following are the arguments.

**Step 4: Creating the Child Process** When a command is entered, the shell creates a new child process using the `fork()` system call. The child process will execute the command using the system call `execvp()`, while the parent process will wait for the child to complete. The associated commands allow the processing of several basic commands such as `ls', 'cat', 'echo', and their options

**Step 5: Managing Internal Orders** Some internal commands have been added to the shell, such as  'exit', to exit the shell. These internal commands are processed directly by the shell, without requiring the creation of a child process.


### Flowchart


![flowchart](https://zupimages.net/up/23/34/4yi8.jpeg)



## functions used



### main.c Function

#### *Interactive Mode*

  interactive

![interactif](https://zupimages.net/up/23/34/bsg1.png)

```c

# Usage

The `interactive` function start the shell in interactive mode.

```

#### *Non-interactive Mode*


non_interactive

![non-interactif](https://zupimages.net/up/23/34/06dn.png)

```c

# Usage

The `non_interactive` function is used when a command is run outside the shell interface.

```

### exec.c Function


parse_cmd

```c
void parse_cmd(char *buffer, char *name, int nb_cmd, char **env,
				 int *status)
{
	int i = 0;
	char *copy_cmd, **cmd, *token;

	cmd = malloc(sizeof(char *) * (strlen(buffer) + 1));
	token = strtok(buffer, " \n\t");

	while (token != NULL)
	{
		cmd[i++] = token;
		token = strtok(NULL, " \n\t");
	}

	cmd[i] = NULL;
	copy_cmd = strdup(cmd[0]);

	if (check_env(copy_cmd, env) != 0)
	{
		cmd[0] = _which(copy_cmd, env);
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

# Usage
The `parse_cmd` function separates the string into a sequence of elements.

```

exe_cmd

```c
void exe_cmd(char **cmd, char *name, char **env)
{

	if (fork() == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			perror(name);
			exit(0);
		}
	}
}

# Usage
The `exe_cmd` function execute the command entered the terminal .

```

cmd_null

```c

void cmd_null(char *name, char *str, char **cmd, char *copy_cmd, int nb_cmd,
			  int *status)
{
	int value = 0;

	if (strcmp(copy_cmd, "setenv") == 0)
		return;
	else if (strcmp(copy_cmd, "unsetenv") == 0)
		return;
	else if (strcmp(copy_cmd, "exit") == 0)
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
		printf("%s: %d: %s: not found\n", name, nb_cmd, copy_cmd);
		*status = 127;
	}
}


# Usage
The `cmd_null` function is used for compare if the command does not exist in the "PATH", or if it is different from the "exit" command.

```

exit_value

```c

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

# Usage
The `exit_value` function left the processus.

```

### built-in.c Function


_which

```c

char *_which(char *cmd, char **env)
{
	struct stat st;
	char *copy_path = strdup(_getenv("PATH", env)), *token;
	char path_cat[150];

	if (stat(cmd, &st) == 0)
	{
		free(copy_path);
		return (strdup(cmd));
	}
	token = strtok(copy_path, ":");

	do {
		strcpy(path_cat, token);
		strcat(path_cat, "/");
		strcat(path_cat, cmd);

		if (stat(path_cat, &st) == 0)
		{
			free(copy_path);
			return (strdup(path_cat));
		}
		else
			path_cat[0] = 0;

		token = strtok(NULL, ":");
	} while (token != NULL);

	free(copy_path);
	return (NULL);
}

# Usage
The `_which` function checks whether the command is executable or exists in the environment variables and returns

```

  #_getenv

```c

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

# Usage
The `_getenv` function searches the environment list to find the environment variable _name_, and returns a pointer to the corresponding _value_ string.

```




## main.h




It contains our structure and the various prototypes required to operate the function.

```c

#ifndef  MAIN_H
#define  MAIN_H

#include  <strings.h>
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <signal.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include  <sys/stat.h>

void  inter(char  *name, char  *buffer, size_t  bufsize, int  nb_cmd, char  **env, int  *status);
void  non_int(char  *name, char  *buffer, size_t  bufsize, int  nb_cmd, char  **env, int *status);
void  execute_cmd(char  *buffer, char  *name, int  nb_cmd, char  **env, int  *status);
void  exe_cmd(char  **cmd, char  *name, char  **env);
int  check_env(char  *copy_cmd, char  **env);
char  *_which(char  *cmd, char  **env);
char  *_getenv(const  char  *name, char  **env);
void  cmd_null(char  *name, char  *str, char  **cmd, char  *copy_cmd, int  nb_cmd, int  *status);
int  exit_value(char  *n);

#endif /* MAIN_H */


```





## Auteurs

* [AUTHORS](AUTHORS) - It lists the contributors of this project



[langage.C]:https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white

[c.url]:https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c
