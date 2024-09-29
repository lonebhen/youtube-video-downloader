#include "argument_parsing.h"
#include "command_execution.h"
#include "directory_management.h"
#include "download_helpers.h"
#include "format_parsing.h"
#include "help_display.h"
#include "user_interaction.h"
#include "video_info.h"
#include "ytdl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    Config config = {0};

    int init_result = 0;


    init_result = parse_arguments(argc, argv, &config);

    if(init_result !=0)
    {
        cleanup(&config);
        return init_result;
    }

    printf("Download URL: %s\n", config.url);
    printf("Output path: %s\n", config.output_path);

    char *json_str = get_video_info(config.url);

    if(json_str == NULL)
    {
        fprintf(stderr, "Error: Failed to get video info\n");
        cleanup(&config);

        return EXIT_FAILURE;
    }

    json_t *formats = parse_formats(json_str);

    free(json_str);

    if(formats == NULL)
    {
        cleanup(&config);
        return EXIT_FAILURE;
    }

    display_formats(formats);

    char *format_code = prompt_for_format();

    if(format_code == NULL)
    {
        cleanup(&config);
        return EXIT_FAILURE;
    }

    if(download_video(&config, format_code) !=0)
    {
        fprintf(stderr, "Error: Download failed\n");
        free(format_code);

        cleanup(&config);
        return EXIT_FAILURE;
    }

    free (format_code);
    cleanup(&config);

    return EXIT_SUCCESS;


}
