#include "help_display.h"
#include "directory_management.h"

#include <stdio.h>
#include <stdlib.h>


void display_help(void)
{
    printf("Usage: ytdl [OPTION].... URL\n");
    printf("Download videos from youtube using yt-dlp\n\n");
    printf("Options:\n");
    printf(" -h, --help\t\t\tDisplay this help message\n");
    printf(" -o, --output PATH\t\tSpecify the output directory (default: "
            "current directory)\n");
}


void cleanup(Config *config)
{
    if(config->output_path !=NULL && config->output_path != get_current_working_directory())
    {
        free ((void *) config->output_path);
    }
}