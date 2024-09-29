#ifndef ARGUMENT_PARSING_H
#define ARGUMENT_PARSING_H

#include "ytdl.h"

int parse_arguments(int argc, char *argv[], Config *config);
int initialize_output_path(Config *config);

#endif