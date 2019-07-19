#include <string.h>
#include "roman/parse.h"

static unsigned int parse_roman_digit(char digit)
{
    if (digit == 'I' || digit == 'i') {
        return 1;
    } else if (digit == 'V' || digit == 'v') {
        return 5;
    } else if (digit == 'X' || digit == 'x') {
        return 10;
    } else if (digit == 'L' || digit == 'l') {
        return 50;
    } else if (digit == 'C' || digit == 'c') {
        return 100;
    } else if (digit == 'D' || digit == 'd') {
        return 500;
    } else if (digit == 'M' || digit == 'm') {
        return 1000;
    } else {
        return 0;
    }
}

unsigned int parse_roman(const char *number)
{
    int digits = strlen(number);
    int sum = 0;

    for (int i = 0; i < digits; ++i) {
        sum += parse_roman_digit(number[i]);
    }

    return sum;
}