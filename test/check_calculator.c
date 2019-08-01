#include <errno.h>
#include <stdlib.h>
#include <check.h>
#include "roman/calculator.h"

START_TEST(test_parses_numerals)
{
    char *result;

    result = (char *) input("XX");
    ck_assert_str_eq("XX", result);
    free(result);
}
END_TEST

START_TEST(test_performs_calculations)
{
    char *result;

    result = (char *) input("XX");
    ck_assert_str_eq("XX", result);
    free(result);

    result = (char *) input("II");
    ck_assert_str_eq("II", result);
    free(result);

    result = (char *) input("+");
    ck_assert_str_eq("XXII", result);
    free(result);
}
END_TEST

Suite *parse_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Calculator");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_parses_numerals);
    tcase_add_test(tc_core, test_performs_calculations);

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