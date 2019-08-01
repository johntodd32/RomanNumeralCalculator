#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "roman/calculator.h"
#include "roman/parse.h"
#include "roman/unparse.h"

#define MAX_STACK_HEIGHT 10

const unsigned int num_ops = 5;
enum Op{None, Plus, Minus, Times, DividedBy};
typedef struct Operation {
    enum Op operator;
    char *symbol;
} Operation;
Operation ops[] = {
    {None, ""},
    {Plus, "+"},
    {Minus, "-"},
    {Times, "*"},
    {DividedBy, "/"}
};

unsigned int stack[MAX_STACK_HEIGHT];
unsigned int *stack_pos = stack;

static char *copy_message(const char *outgoing_message)
{
    char *result = malloc(strlen(outgoing_message) + 1);
    strcpy(result, outgoing_message);
    return result;
}

static unsigned int is_operator(const char *entry)
{
    for (int i = 1; i < num_ops; ++i) {
        if (strcmp(ops[i].symbol, entry) == 0) {
            return ops[i].operator;
        }
    }
    return None;
}

static unsigned int operate(const unsigned int operation, const unsigned int operand1, const unsigned int operand2)
{
    switch(operation) {
        case Plus:
            return operand1 + operand2;
            break;
        case Minus:
            return operand2 - operand1;
            break;
        case Times:
            return operand1 * operand2;
            break;
        case DividedBy:
            return operand2 / operand1;
            break;
        default:
            errno = EPERM;
            return 0;
    }
}

const char *input(const char *entry)
{
    errno = 0;
    enum Op op;
    char *result;

    if ((op = is_operator(entry))) {
        if (stack_pos - stack < 2) {
            errno = EOVERFLOW;
            result = copy_message("ERR");
        } else {
            --stack_pos;
            unsigned int op1 = *stack_pos;
            --stack_pos;
            unsigned int op2 = *stack_pos;
            unsigned int arabic_result = operate(op, op1, op2);
            if (arabic_result == 0 && errno == EPERM) {
                result = copy_message("ERR");
            } else {
                *stack_pos = arabic_result;
                ++stack_pos;
                result = unparse_roman(arabic_result);
            }
        }
    } else {
        unsigned int parse_result = parse_roman(entry);
        if (parse_result == 0 && errno != 0) {
            result = copy_message("ERR");
        } else if (stack_pos - stack == MAX_STACK_HEIGHT) {
            errno = EOVERFLOW;
            result = copy_message("ERR");
        } else {
            *stack_pos = parse_result;
            ++stack_pos;
            result = copy_message(entry);
        }
    }
    return result;
}

const char *clear(void)
{
    stack_pos = stack;
    return copy_message("CLR");
}