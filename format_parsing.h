#ifndef FORMAT_PASSING_H
#define FORMAT_PASSING_H

#include "ytdl.h"

json_t *parse_formats(const char *json_str);
void display_formats(const json_t *formats);

#endif