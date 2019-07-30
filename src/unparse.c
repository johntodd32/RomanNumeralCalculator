#include <stdlib.h>
#include <string.h>
#include "roman/unparse.h"

char *unparse_roman(const unsigned int arabic)
{
    char *result = malloc(sizeof(char) * 2);
    if (arabic == 1000) {
        strcpy(result, "M");
    } else if (arabic == 500) {
        strcpy(result, "D");
    } else if (arabic == 100) {
        strcpy(result, "C");
    } else if (arabic == 50) {
        strcpy(result, "L");
    } else if (arabic == 10) {
        strcpy(result, "X");
    } else if (arabic == 5) {
        strcpy(result, "V");
    } else if (arabic == 1) {
        strcpy(result, "I");
    }
    return result;
}