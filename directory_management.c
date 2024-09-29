#include "directory_management.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


int create_directory_if_not_exists(const char *path)
{
    struct stat st = {0};

    if(stat(path, &st) == -1)
    {

        if(mkdir(path, DIRECTORY_PERMISSIONS) == -1)
        {
            fprintf(stderr, "Error: Failed to create directory %s: %s\n", path, strerror(errno));
            return -1;
        }

    }

    return 0;
}

char *get_current_working_directory(void)
{
    char *current_dir = getcwd(NULL, 0);

    if(current_dir == NULL)
    {
        perror("getcwd");
        return NULL;
    }

    return current_dir;
}