#include <errno.h>
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
        errno = EINVAL;
        return 0;
    }
}

unsigned int parse_roman(const char *number)
{
    errno = 0;
    int digits = strlen(number);
    unsigned int sum = 0;
    unsigned int digit_val;

    for (int i = 0; i < digits; ++i) {
        digit_val = parse_roman_digit(number[i]);
        if (digit_val == 0 && errno != 0) {
            sum = 0;
            break;
        } else {
            sum += digit_val;
        }
    }

    return sum;
}