#include "download_helpers.h"
#include "command_execution.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char **build_download_command_args(const char *format_code, const char *output_path, const char *url)
{

    int arg_count = 5;

    if(format_code && strlen(format_code) > 0)
    {
        arg_count = 6;
    }


    char **args = malloc(sizeof(char *) * (arg_count + 1));

    if(args == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for command arguments\n");
        return NULL;
    }

    args[0] = "yt-dlp";
    int idx = 1;

    if(format_code && strlen(format_code) > 0)
    {
        args[idx++] = "-f";
        args[idx++] = (char *) format_code;
    }
    else
    {
        args[idx++] = "-f";
        args[idx++] = "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best[ext=mp4]/best";

    }

    args[idx++] = "-o";

    char *output_template = malloc(MAX_PATH_LENGTH);

    if(output_template == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for output template\n");
        free(args);
        return NULL;
    }

    snprintf(output_template, MAX_PATH_LENGTH, "%s/%%(title)s.%%(ext)s", output_path);
    args[idx++] = output_template;
    args[idx++] = (char *) url;
    args[idx] = NULL;

    return args;

}

void free_command_args(char **args)
{
    if(args == NULL)
        return;

    if(args[4] != NULL)
    {
        free(args[4]);
    }

    free(args);
}

int download_video(const Config *config, const char *format_code)
{
    printf("Downloading....\n");


    char **args = build_download_command_args(format_code, config->output_path, config->url);

    if(args == NULL)
    {
        fprintf(stderr, "Error: Failed to build download command arguments\n");
        return -1;
    }

    int result = execute_command_without_output("yt-dlp", args);

    if(result == 0){
        printf("Download complete! Saved to: %s\n", config->output_path);

    }
    else
    {
        fprintf(stderr, "Error: Download failed\n");
    }

    free_command_args(args);
    return result;
}