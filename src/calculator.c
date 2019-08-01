#include <stdlib.h>
#include <string.h>
#include "roman/calculator.h"

const char *input(const char *entry)
{
    char *result = malloc(strlen(entry) + 1);
    strcpy(result, entry);
    return result;
}