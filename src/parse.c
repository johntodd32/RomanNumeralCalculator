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
        return 0;
    }
}

static unsigned int set_error()
{
    errno = EINVAL;
    return 0;
}

unsigned int parse_roman(const char *number)
{
    errno = 0;
    int digits = strlen(number);
    unsigned int sum, digit_val, prev_digit_val, second_prev_digit_val, repeats;

    sum = 0;
    prev_digit_val = 9999;
    second_prev_digit_val = 9999;
    repeats = 0;
    for (int i = 0; i < digits; ++i) {
        digit_val = parse_roman_digit(number[i]);
        if (digit_val == 0) {
            sum = set_error();
            break;
        } else if (prev_digit_val < digit_val && second_prev_digit_val <= prev_digit_val) {
            sum = set_error();
            break;
        } else if (prev_digit_val < digit_val) {
            sum -= 2 * prev_digit_val;
        }
        if (prev_digit_val == digit_val) {
            ++repeats;
        } else {
            repeats = 1;
        }
        if ((digit_val == 1 || digit_val == 10 || digit_val == 100) && repeats > 3) {
            sum = set_error();
            break;
        } else if ((digit_val == 5 || digit_val == 50 || digit_val == 500) && repeats > 1) {
            sum = set_error();
            break;
        }
        sum += digit_val;
        second_prev_digit_val = prev_digit_val;
        prev_digit_val = digit_val;
    }

    return sum;
}
