#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "romancalctest.h"
#include "../src/romancalc.h"

START_TEST(test_NULL_plus_I_Returns_ROMAN_CALCULATOR_INVALID_FIRST_TERM) {
	char* result = NULL;
	ck_assert_int_eq(RomanCalculator(NULL, "+", "I", result), ROMAN_CALCULATOR_INVALID_FIRST_TERM);
}
END_TEST

START_TEST(test_I_plus_NULL_Returns_ROMAN_CALCULATOR_INVALID_SECOND_TERM) {
	char* result = NULL;
	ck_assert_int_eq(RomanCalculator("I", "+", NULL, result), ROMAN_CALCULATOR_INVALID_SECOND_TERM);
}
END_TEST

Suite* CalculatorSuite(void) {
	Suite* suite = suite_create("Roman Numeral Calculator Tests");
	TCase* inputs_case = tcase_create("Validate Arguments");

	tcase_add_test(inputs_case, test_NULL_plus_I_Returns_ROMAN_CALCULATOR_INVALID_FIRST_TERM);
	tcase_add_test(inputs_case, test_I_plus_NULL_Returns_ROMAN_CALCULATOR_INVALID_SECOND_TERM);
	suite_add_tcase(suite, inputs_case);

	return suite;
}
