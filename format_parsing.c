#include "format_parsing.h"

#include <stdio.h>
#include <jansson.h>


json_t *parse_formats(const char *json_str)
{
    json_error_t error;

    json_t *root = json_loads(json_str, 0, &error);

    if(!root)
    {
        fprintf(stderr, "Error: JSON parsing failed on line %d: %s\n", error.line, error.text);
        return NULL;
    }

    json_t *formats = json_object_get(root, "formats");

    if(!json_is_array(formats))
    {
        fprintf(stderr, "Error: 'formats' is not an array in JSON data\n");
        json_decref(root);

        return NULL;
    }

    json_incref(formats);
    json_incref(root);

    return formats;


}


void display_formats(const json_t *formats)
{
    printf("Available formats:\n");
    size_t index;
    json_t *format;
    json_array_foreach (formats, index, format)
    {

        const char *format_id = json_string_value(json_object_get(format, "format_id"));

        const char *resolution = json_string_value(json_object_get(format, "resolution"));

        const char *ext = json_string_value(json_object_get(format, "ext"));

        json_int_t filesize = json_integer_value(json_object_get(format, "filesize"));


        printf("Format code: %-5s Resolution: %-10s Extension: %-4s Filesize: "
                "%8lld bytes\n", format_id ? format_id : "N/A", resolution ? resolution: "N/A", ext ? ext: "N/A", (long long) filesize
                );

    }
}