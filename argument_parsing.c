#include "argument_parsing.h"
#include "help_display.h"
#include "directory_management.h"


#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


static char *my_strdup(const char *s)
{

    assert (s !=NULL);

    size_t len = strlen(s) + 1;

    char *new_str = malloc(len);

    if(new_str == NULL)
        return NULL;
    return memcpy(new_str, s, len);


}


int parse_arguments(int argc, char *argv[], Config *config){

    struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                    {"output", required_argument, 0, 'o'},
                                    {0, 0, 0, 0}                                    
                                    };

    
    int opt;

    while ((opt = getopt_long(argc, argv, "ho:", long_options, NULL)) != -1)
    {

        switch (opt)
        {
            case 'h':
                display_help();
                exit (EXIT_SUCCESS);

            case 'o':
                config->output_path = my_strdup(optarg);
                if(config->output_path == NULL)
                {
                    fprintf(stderr, "Error: Memory allocation failed for output path \n");
                    return EXIT_FAILURE;
                }
            break;
        }
        
    }

    if(optind < argc)
    {
        config->url = argv[optind];
    }
    else
    {
        fprintf(stderr, "Error: URL is required \n");
        display_help();
        return EXIT_FAILURE;

    }
    
    return 0;

}

int initialize_output_path(Config *config)
{
    if(config->output_path == NULL)
    {
        char *allocated_path = get_current_working_directory();

        if(allocated_path == NULL)
        {
            return EXIT_FAILURE;
        }
        config->output_path = allocated_path;
    }
    else
    {
        if(create_directory_if_not_exists(config->output_path) == -1)
        {
            return EXIT_FAILURE;
        }
    }

    return 0;
}