#include "video_info.h"
#include "command_execution.h"

#include <stdio.h>

char *get_video_info(const char *url)
{
    printf("Fetching video info... \n");

    char *const argv[] = {"yt-dlp", "-j", (char *) url, NULL};
    return execute_command_with_output("yt-dlp", argv);
}
