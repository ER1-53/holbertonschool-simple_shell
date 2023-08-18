#ifndef MAIN_H
#define MAIN_H

#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void execute_cmd(char *name, char *buffer, char **env, int nb_cmd);
void exe_cmd(char **cmd, char *name, char **env);
int check_env(char *copy_cmd, char **env);
void print_env(char **env);
char *_which(char *cmd, char **env);
char *_getenv(const char *name, char **env);
void cmd_null(char *name, char *str, char **cmd, char *copy_cmd, int nb_cmd,
				int *status);
int exit_value(char *n);
#endif /* MAIN_H */
