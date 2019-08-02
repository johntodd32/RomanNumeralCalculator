#include <errno.h>
#include <stdlib.h>
#include <check.h>
#include "roman/calculator.h"

START_TEST(test_parses_numerals)
{
    char *result;

    result = input("XX");
    ck_assert_str_eq("XX", result);
    free(result);
}
END_TEST

START_TEST(test_displays_err_if_input_invalid)
{
    unsigned int prev_errno = errno;
    char *result;

    errno = 0;
    result = input("Z");
    ck_assert_str_eq(error_message, result);
    ck_assert_uint_ne(0, errno);
    free(result);

    errno = prev_errno;
}
END_TEST

START_TEST(test_performs_calculations)
{
    char *result;

    result = input("XX");
    ck_assert_str_eq("XX", result);
    free(result);

    result = input("II");
    ck_assert_str_eq("II", result);
    free(result);

    result = input("+");
    ck_assert_str_eq("XXII", result);
    free(result);

    result = input("XX"); free(result);
    result = input("XX"); free(result);
    result = input("-");
    ck_assert_str_eq("", result);
    free(result);

    result = input("XVI"); free(result);
    result = input("III"); free(result);
    result = input("*");
    ck_assert_str_eq("XLVIII", result);
    free(result);

    result = input("XX"); free(result);
    result = input("XX"); free(result);
    result = input("/");
    ck_assert_str_eq("I", result);
    free(result);

    // Example from https://en.wikipedia.org/wiki/Reverse_Polish_notation
    // ((15 ÷ (7 − (1 + 1))) × 3) − (2 + (1 + 1))
    // 15 7 1 1 + − ÷ 3 × 2 1 1 + + −
    result = input("XV"); free(result);
    result = input("VII"); free(result);
    result = input("I"); free(result);
    result = input("I"); free(result);
    result = input("+"); free(result);
    result = input("-"); free(result);
    result = input("/"); free(result);
    result = input("III"); free(result);
    result = input("*"); free(result);
    result = input("II"); free(result);
    result = input("I"); free(result);
    result = input("I"); free(result);
    result = input("+"); free(result);
    result = input("+"); free(result);
    result = input("-");
    ck_assert_str_eq("V", result);
    free(result);

    result = input("MMXIX"); free(result);
    result = input("MDCCLXXVI"); free(result);
    result = input("-");
    ck_assert_str_eq("CCXLIII", result);
    free(result);
}
END_TEST

START_TEST(test_gives_error_for_divide_by_zero)
{
    unsigned int prev_errno = errno;
    char *result;

    result = input("V"); free(result);
    result = input("I"); free(result);
    result = input("I"); free(result);
    result = input("-"); free(result);
    result = input("/");
    ck_assert_str_eq(error_message, result);
    ck_assert_int_eq(ERANGE, errno);
    free(result);

    errno = prev_errno;
}
END_TEST

START_TEST(test_fails_if_unrecognized_operator_is_given)
{
    unsigned int prev_errno = errno;
    char *result;

    errno = 0;
    result = input("M"); free(result);
    result = input("D"); free(result);
    result = input("^");
    ck_assert_str_eq(error_message, result);
    ck_assert_int_ne(0, errno);
    free(result);

    errno = prev_errno;
}
END_TEST

START_TEST(test_fails_if_stack_is_invalid_when_operator_is_given)
{
    unsigned int prev_errno = errno;
    char *result;

    errno = 0;
    result = input("+");
    ck_assert_str_eq(error_message, result);
    ck_assert_int_ne(0, errno);
    free(result);

    errno = 0;
    result = input("D"); free(result);
    result = input("+");
    ck_assert_str_eq(error_message, result);
    ck_assert_int_ne(0, errno);
    free(result);

    errno = prev_errno;
}
END_TEST

START_TEST(test_fails_if_stack_gets_full)
{
    unsigned int prev_errno = errno;
    char *result;

    for (int i = 0; i < 10; ++i) {
        result = input("I"); free(result);
    }
    result = input("I");
    ck_assert_str_eq(error_message, result);
    ck_assert_int_ne(0, errno);
    free(result);

    errno = prev_errno;
}
END_TEST

START_TEST(test_can_clear_calculation)
{
    unsigned int prev_errno = errno;
    char *result;

    errno = 0;
    result = input("MDCCLXXV"); free(result);
    result = clear();
    ck_assert_str_eq(clear_message, result);
    free(result);
    for (int i = 0; i < 10; ++i) {
        result = input("I");
        ck_assert_str_eq("I", result);
        ck_assert_int_eq(0, errno);
        free(result);
    }

    errno = prev_errno;
}
END_TEST

Suite *parse_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Calculator");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_parses_numerals);
    tcase_add_test(tc_core, test_displays_err_if_input_invalid);
    tcase_add_test(tc_core, test_performs_calculations);
    tcase_add_test(tc_core, test_gives_error_for_divide_by_zero);
    tcase_add_test(tc_core, test_fails_if_unrecognized_operator_is_given);
    tcase_add_test(tc_core, test_fails_if_stack_is_invalid_when_operator_is_given);
    tcase_add_test(tc_core, test_fails_if_stack_gets_full);
    tcase_add_test(tc_core, test_can_clear_calculation);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    s = parse_suite();
    sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}