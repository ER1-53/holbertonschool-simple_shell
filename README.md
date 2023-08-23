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
 ![screen non-int](https://ibb.co/6Ncf390)

**Step 2: The Main Loop** Our shell starts with setting up a main loop. At each iteration of this loop, the shell displays a prompt (for example, "$ "), waits for the user’s input, and reads the command entered.

**Step 3: Order Analysis** The program implements a function to analyze the command entered by the user. This function divides the command line into tokens (words) based on spaces. The first token is usually the command name, and the following are the arguments.

**Step 4: Creating the Child Process** When a command is entered, the shell creates a new child process using the `fork()` system call. The child process will execute the command using the system call `execvp()`, while the parent process will wait for the child to complete. The associated commands allow the processing of several basic commands such as `ls', 'cat', 'echo', and their options

**Step 5: Managing Internal Orders** Some internal commands have been added to the shell, such as  'exit', to exit the shell. These internal commands are processed directly by the shell, without requiring the creation of a child process.


### Flowchart


![flowchart](https://lucid.app/lucidchart/7db4513e-8889-456b-b01f-caecd82a8a64/edit?viewport_loc=-1344%2C-331%2C2631%2C1200%2C0_0&invitationId=inv_a38e9a8d-5809-45c9-822a-fd5203628281)



## functions used



### main.c Function

#### *Interactive Mode*

  interactive

```c

# Usage

The `interactive` function start the shell in interactive mode.

```

#### *Non-interactive Mode*


non_interactive

  ![screen non-int](https://ibb.co/6Ncf390)

```c

# Usage

The `non_interactive` function is used when a command is run outside the shell interface.

```

### exec.c Function


parse_cmd
```c

# Usage
The `parse_cmd` function separates the string into a sequence of elements.

```

exe_cmd

```c

# Usage
The `exe_cmd` function execute the command entered the terminal .

```

cmd_null

```c

# Usage
The `cmd_null` function is used for compare if the command does not exist in the "PATH", or if it is different from the "exit" command.

```

exit_value
```c

# Usage
The `exit_value` function left the processus.

```

### built-in.c Function


_which
```c

# Usage
The `_which` function checks whether the command is executable or exists in the environment variables and returns

```

  #_getenv
```c

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



[Kevin Pellissard](https://github.com/PellissardKevin?tab=repositories) C21 HolbertonSchool

[Erwan Cremey](https://github.com/ER1-53) C21 HolbertonSchool





[langage.C]:https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white

[c.url]:https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c
