#ifndef MAIN_H
#define MAIN_H

#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void inter(char *name, char *buffer, size_t bufsize, int nb_cmd, char **env,
		   int *status);
void non_int(char *name, char *buffer, size_t bufsize, int nb_cmd, char **env,
			 int *status);
void execute_cmd(char *buffer, char *name, int nb_cmd, char **env,
				 int *status);
void exe_cmd(char **cmd, char *name, char **env);
int check_env(char *copy_cmd, char **env);
void print_env(char **env);
char *_which(char *cmd, char **env);
char *_getenv(const char *name, char **env);
void cmd_null(char *name, char *str, char **cmd, char *copy_cmd, int nb_cmd,
			  int *status);
int exit_value(char *n);
void sigintHandler(int sig);
#endif /* MAIN_H */
