#include <errno.h>
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

START_TEST(test_fails_for_unrecognized_digits)
{
    int prev_errno = errno;
    unsigned int result;

    errno = 0;
    result = parse_roman("A");
    ck_assert_int_eq(result, 0);
    ck_assert_str_eq(strerror(errno), strerror(EINVAL));

    errno = 0;
    result = parse_roman("AI");
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(errno, EINVAL);

    errno = prev_errno;
}
END_TEST

START_TEST(test_subtracts_leading_smaller_digit_from_trailing_larger_digit) {
    unsigned int result;

    result = parse_roman("IV");
    ck_assert_int_eq(result, 4);

    result = parse_roman("IX");
    ck_assert_int_eq(result, 9);

    result = parse_roman("CM");
    ck_assert_int_eq(result, 900);

    result = parse_roman("XIV");
    ck_assert_int_eq(result, 14);

    result = parse_roman("MCM");
    ck_assert_int_eq(result, 1900);
}
END_TEST

START_TEST(test_leading_smaller_digits_cant_repeat) {
    int prev_errno = errno;
    unsigned int result;

    errno = 0;
    result = parse_roman("IIV");
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(errno, EINVAL);

    errno = 0;
    result = parse_roman("CCM");
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(errno, EINVAL);

    errno = prev_errno;
}
END_TEST

START_TEST(test_repeat_rules_are_followed) {
    int prev_errno = errno;
    unsigned int result;

    errno = 0;
    result = parse_roman("IIII");
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(errno, EINVAL);

    errno = 0;
    result = parse_roman("VV");
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(errno, EINVAL);

    errno = prev_errno;
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
    tcase_add_test(tc_core, test_fails_for_unrecognized_digits);
    tcase_add_test(tc_core, test_subtracts_leading_smaller_digit_from_trailing_larger_digit);
    tcase_add_test(tc_core, test_leading_smaller_digits_cant_repeat);
    tcase_add_test(tc_core, test_repeat_rules_are_followed);
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