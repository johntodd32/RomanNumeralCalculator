#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "roman/calculator.h"
#include "roman/parse.h"

const char *input(const char *entry)
{
    errno = 0;
    char *result;
    unsigned int parse_result = parse_roman(entry);
    if (parse_result == 0 && errno != 0) {
        result = malloc(strlen("ERR") + 1);
        strcpy(result, "ERR");
    } else {
        result = malloc(strlen(entry) + 1);
        strcpy(result, entry);
    }
    return result;
}