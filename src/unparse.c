#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "roman/unparse.h"

// Longest possible Roman number:
// MMMDMCCCLCXXXVIII
// which is 17 characters
#define MAX_ROMAN_LENGTH 17
#define MAX_ROMAN_VALUE  3999
#define NUM_ROMAN_NUMERALS 7

typedef struct RomanNumeral {
    unsigned int value;
    char *digits;
} RomanNumeral;

static RomanNumeral ordinary_digits[] = {
    {1000, "M"},
    {500,  "D"},
    {100,  "C"},
    {50,   "L"},
    {10,   "X"},
    {5,    "V"},
    {1,    "I"}
};

static RomanNumeral subtractive_digits[] = {
    {900,     "CM"},
    {INT_MAX, "ZZ"},
    {90,      "XC"},
    {40,      "XL"},
    {9,       "IX"},
    {4,       "IV"},
    {INT_MAX, "ZZ"},
    {INT_MAX, "ZZ"}
};

static void append_and_subtract(unsigned int *current, char **ptr, const RomanNumeral numeral)
{
    while (*current >= numeral.value) {
        strcpy(*ptr, numeral.digits);
        *ptr += strlen(numeral.digits);
        *current -= numeral.value;
    }
}

char *unparse_roman(unsigned int arabic)
{
    char buffer[MAX_ROMAN_LENGTH + 1];
    char *result;

    if (arabic > MAX_ROMAN_VALUE) {
        errno = EDOM;
        result = NULL;
    } else {
        char *ptr = buffer;
        unsigned int current = arabic;
        for (int i = 0; i < NUM_ROMAN_NUMERALS; ++i) {
            append_and_subtract(&current, &ptr, ordinary_digits[i]);
            append_and_subtract(&current, &ptr, subtractive_digits[i]);
        }
        *ptr = '\0';
        result = malloc(strlen(buffer) + 1);
        strcpy(result, buffer);
    }

    return result;
}