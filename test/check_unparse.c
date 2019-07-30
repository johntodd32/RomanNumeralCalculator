#include <stdlib.h>
#include <check.h>
#include "roman/unparse.h"

START_TEST(test_unparse_one_digit)
{
    char *result;

    result = unparse_roman(1);
    ck_assert_str_eq(result, "I");
    free(result);

    result = unparse_roman(5);
    ck_assert_str_eq(result, "V");
    free(result);

    result = unparse_roman(10);
    ck_assert_str_eq(result, "X");
    free(result);

    result = unparse_roman(50);
    ck_assert_str_eq(result, "L");
    free(result);

    result = unparse_roman(100);
    ck_assert_str_eq(result, "C");
    free(result);

    result = unparse_roman(500);
    ck_assert_str_eq(result, "D");
    free(result);

    result = unparse_roman(1000);
    ck_assert_str_eq(result, "M");
    free(result);
}
END_TEST

Suite *unparse_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Unparse");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_unparse_one_digit);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = unparse_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}