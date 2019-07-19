#include <stdlib.h>
#include <check.h>
#include "roman/parse.h"

START_TEST(test_parse_one_digit)
{
    ck_assert_int_eq(parse_roman("I"), 1);
    ck_assert_int_eq(parse_roman("i"), 1);
    ck_assert_int_eq(parse_roman("V"), 5);
    ck_assert_int_eq(parse_roman("v"), 5);
    ck_assert_int_eq(parse_roman("X"), 10);
    ck_assert_int_eq(parse_roman("x"), 10);
    ck_assert_int_eq(parse_roman("L"), 50);
    ck_assert_int_eq(parse_roman("l"), 50);
    ck_assert_int_eq(parse_roman("C"), 100);
    ck_assert_int_eq(parse_roman("c"), 100);
    ck_assert_int_eq(parse_roman("D"), 500);
    ck_assert_int_eq(parse_roman("d"), 500);
    ck_assert_int_eq(parse_roman("M"), 1000);
    ck_assert_int_eq(parse_roman("m"), 1000);
}
END_TEST

START_TEST(test_parse_multiple_digits)
{
    ck_assert_int_eq(parse_roman("II"), 2);
    ck_assert_int_eq(parse_roman("MMXVII"), 2017);
}
END_TEST

Suite *parse_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Parse");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_parse_one_digit);
    tcase_add_test(tc_core, test_parse_multiple_digits);
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