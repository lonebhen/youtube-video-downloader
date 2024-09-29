#include "command_execution.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


pid_t fork_process(void)
{
    pid_t pid = fork();

    if(pid == -1)
    {
        perror("fork");
    }

    return pid;
}

int setup_pipes(int pipefd[2])
{
    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }

    return 0;

}

int redirect_stdout(int pipefd)
{
    if (dup2(pipefd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        return -1;
    }

    return 0;
}


char *read_from_pipe(int pipefd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    size_t output_size = 0;
    char *output = malloc(1);

    if (output == NULL)
    {
        perror("malloc");
        return NULL;
    }

    output[0] = '\0';

    while ((bytes_read = read(pipefd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        size_t new_size = output_size + bytes_read + 1;
        char *new_output = realloc(output, new_size);


        if(new_output == NULL)
        {
            perror("realloc");
            free(output);
            return NULL;
        }

        output = new_output;
        memcpy (output + output_size, buffer, bytes_read + 1);
        output_size += bytes_read;
    }

    if(bytes_read == -1)
    {
        perror("read");
        free(output);
        return NULL;
    }

    return output;
    
}



char *
execute_command_with_output (const char *command, char *const argv[])
{
  int pipefd[2];
  if (setup_pipes (pipefd) == -1)
  {
    return NULL;
  }

  pid_t pid = fork_process ();
  if (pid == -1)
  {
    close (pipefd[READ_END]);
    close (pipefd[WRITE_END]);
    return NULL;
  }
  else if (pid == 0)
  {
    close (pipefd[READ_END]);

    if (redirect_stdout (pipefd[WRITE_END]) == -1)
    {
      close (pipefd[1]);
      exit (EXIT_FAILURE);
    }
    close (pipefd[WRITE_END]);

    execvp (command, argv);

    perror ("execvp");
    exit (EXIT_FAILURE);
  }
  else
  {
    close (pipefd[WRITE_END]);

    char *output = read_from_pipe (pipefd[0]);
    close (pipefd[READ_END]);

    int status;
    if (waitpid (pid, &status, 0) == -1)
    {
      perror ("waitpid");
      free (output);
      return NULL;
    }

    if (WIFEXITED (status))
    {
      int exit_status = WEXITSTATUS (status);
      if (exit_status != 0)
      {
    fprintf (stderr, "Error: Command exited with status %d\n", exit_status);
    free (output);
    return NULL;
      }
    }
    else
    {
      fprintf (stderr, "Error: Child process did not exit normally\n");
      free (output);
      return NULL;
    }

    return output;
  }
}

int
execute_command_without_output (const char *command, char *const argv[])
{
  pid_t pid = fork_process ();
  if (pid == -1)
  {
    return -1;
  }
  else if (pid == 0)
  {
    execvp (command, argv);

    perror ("execvp");
    exit (EXIT_FAILURE);
  }
  else
  {
    int status;
    if (waitpid (pid, &status, 0) == -1)
    {
      perror ("waitpid");
      return -1;
    }

    if (WIFEXITED (status))
    {
      return WEXITSTATUS (status);
    }
    else
    {
      fprintf (stderr, "Error: Child process did not exit normally\n");
      return -1;
    }
  }

}