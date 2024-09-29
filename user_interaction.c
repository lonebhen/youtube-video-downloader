#include "user_interaction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *prompt_for_format(void)
{

    char *format_code = malloc(FORMAT_CODE_LENGTH * sizeof(char));

    if (format_code == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for format code\n");
        return NULL;
    }


    printf("Enter the format code (leave blank for best quality): ");

    if(fgets(format_code, FORMAT_CODE_LENGTH, stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read format code \n");
        free (format_code);

        return NULL;
    }

    format_code[strcspn (format_code, "\n")] = 0;

    return format_code;

}