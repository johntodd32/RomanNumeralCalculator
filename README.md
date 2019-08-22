# RomanNumeralCalculator
My implementation of the Roman Numeral Calculator

The library implements a Roman Numeral Calculator using Reverse Polish Notation. For example:

```c
char *result;
result = input("V"); free(result);
result = input("I"); free(result);
result = input("+");
ck_assert_str_eq(result, "VI");
```

Mistakes and the entire stack can be cleared with the `clear` method:

```c
char *result;
result = input("V"); free(result);
result = clear(); free(result);
result = input("X"); free(result);
result = input("I"); free(result);
result = input("+"); free(result);
ck_assert_str_eq(result, "XI");
```

Each input operation returns a dynamically-allocated string that needs to be freed.

## To build:
- `$ mkdir build`
- `$ cd build`
- `$ cmake ..`
- `$ make`
- `$ make test`

## Assumptions:

- The library sets the `errno` global variable for several error conditions:
  - Error parsing an input operand: `EINVAL`
  - Unparsing a number greater than the max in the kata description: `EDOM`
  - Unrecognized operator: `EPERM`
  - Divide by zero: `ERANGE`
  - Operator without at least two operands: `EOVERFLOW`
  - Overflowing the stack with operands: `EOVERFLOW`
- The kata description mentions that the Romans had no numeral for zero, so this library returns an empty string for a zero integer argument. This means the calculator produces confusing output for a zero result, namely, the empty string.
