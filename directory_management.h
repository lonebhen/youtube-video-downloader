#ifndef DIRECTORY_MANAGEMENT_H
#define DIRECTORY_MANAGEMENT_H

#include "ytdl.h"

int create_directory_if_not_exists(const char *path);
char *get_current_working_directory(void);

#endif