#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "roman/calculator.h"
#include "roman/parse.h"
#include "roman/unparse.h"

#define MAX_STACK_HEIGHT 10
#define PLUS 1
#define MINUS 2
#define TIMES 3
#define DIVIDED_BY 4

unsigned int stack[MAX_STACK_HEIGHT];
unsigned int *stack_pos = stack;

static unsigned int is_operator(const char *entry)
{
    if (strcmp("+", entry) == 0) {
        return PLUS;
    } else if (strcmp("-", entry) == 0) {
        return MINUS;
    } else if (strcmp("*", entry) == 0) {
        return TIMES;
    } else if (strcmp("/", entry) == 0) {
        return DIVIDED_BY;
    } else {
        return 0;
    }
}

static unsigned int operate(const unsigned int operation, const unsigned int operand1, const unsigned int operand2)
{
    if (operation == PLUS) {
        return operand1 + operand2;
    } else if (operation == MINUS) {
        return operand2 - operand1;
    } else if (operation == TIMES) {
        return operand1 * operand2;
    } else if (operation == DIVIDED_BY) {
        return operand2 / operand1;
    } else {
        errno = EPERM;
        return 0;
    }
}

const char *input(const char *entry)
{
    errno = 0;
    unsigned int op;
    char *result;

    if ((op = is_operator(entry))) {
        if (stack_pos - stack < 2) {
            result = malloc(strlen("ERR") + 1);
            strcpy(result, "ERR");
        } else {
            --stack_pos;
            unsigned int op1 = *stack_pos;
            --stack_pos;
            unsigned int op2 = *stack_pos;
            unsigned int arabic_result = operate(op, op1, op2);
            if (arabic_result == 0 && errno == EPERM) {
                result = malloc(strlen("ERR") + 1);
                strcpy(result, "ERR");
            } else {
                result = unparse_roman(arabic_result);
            }
        }
    } else {
        unsigned int parse_result = parse_roman(entry);
        if (parse_result == 0 && errno != 0) {
            result = malloc(strlen("ERR") + 1);
            strcpy(result, "ERR");
        } else if (stack_pos - stack == MAX_STACK_HEIGHT) {
            result = malloc(strlen("ERR") + 1);
            strcpy(result, "ERR");
        } else {
            *stack_pos = parse_result;
            ++stack_pos;
            result = malloc(strlen(entry) + 1);
            strcpy(result, entry);
        }
    }
    return result;
}