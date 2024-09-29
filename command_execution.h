#ifndef COMMAND_EXECUTION_H
#define COMMAND_EXECUTION_H

#include "ytdl.h"

pid_t fork_process(void);
int setup_pipes(int pipefd[2]);
int redirect_stdout(int pipefd);
char *read_from_pipe(int pipefd);
char *execute_command_with_output(const char *command, char *const argv[]);
int execute_command_without_output(const char *command, char *const argv[]);

#endif