#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "roman/unparse.h"

// Longest possible Roman number:
// MMMDMCCCLCXXXVIII
// which is 17 characters
#define MAX_LENGTH 17
#define MAX_VALUE  3999

static unsigned int num_roman_characters = 7;
static char *roman_characters[] = {"M", "D", "C", "L", "X", "V", "I"};
static unsigned int roman_character_values[] = {1000, 500, 100, 50, 10, 5, 1};

static void append_chars_while_current_greater_than_value(unsigned int *current, const int value, char **ptr, const char *text)
{
    size_t text_len = strlen(text);
    while (*current >= value) {
        strcpy(*ptr, text);
        *ptr += text_len;
        *current -= value;
    }
}

char *unparse_roman(unsigned int arabic)
{
    char buffer[MAX_LENGTH + 1];
    char *result;

    if (arabic > MAX_VALUE) {
        errno = EDOM;
        result = NULL;
    } else if (arabic == 0) {
        result = malloc(sizeof(char));
        result[0] = '\0';
    } else {
        char *ptr = buffer;
        unsigned int current = arabic;
        for (int i = 0; i < num_roman_characters; ++i) {
            append_chars_while_current_greater_than_value(&current, roman_character_values[i], &ptr, roman_characters[i]);
        }
        *ptr = '\0';
        result = malloc(strlen(buffer) + 1);
        strcpy(result, buffer);
    }

    return result;
}