#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "romancalctest.h"
#include "../src/romancalc.h"


START_TEST(test_NULL_plus_I_Returns_ROMAN_CALCULATOR_MISSING_FIRST_TERM) {
	char result[16];
	memset(result,'\0',sizeof(result));
	ck_assert_int_eq(RomanCalculator(NULL, "+", "I", result), ROMAN_CALCULATOR_MISSING_FIRST_TERM);
}
END_TEST

START_TEST(test_I_plus_NULL_Returns_ROMAN_CALCULATOR_MISSING_SECOND_TERM) {
	char result[16];
	memset(result,'\0',sizeof(result));
	ck_assert_int_eq(RomanCalculator("I", "+", NULL, result), ROMAN_CALCULATOR_MISSING_SECOND_TERM);
}
END_TEST

START_TEST(test_I_NULL_I_Returns_ROMAN_CALCULATOR_MISSING_OPERATOR ) {
	char result[16];
	memset(result,'\0',sizeof(result));
	ck_assert_int_eq(RomanCalculator("I", NULL, "I", result), ROMAN_CALCULATOR_MISSING_OPERATOR);
}
END_TEST

START_TEST(test_I_plus_I_With_No_Result_Buffer_Returns_ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER) {
	ck_assert_int_eq(RomanCalculator("I", "+", "I", NULL), ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER);
}
END_TEST


Suite* CalculatorSuite(void) {
	Suite* suite = suite_create("Roman Numeral Calculator Tests");
	TCase* inputs_case = tcase_create("Validate Arguments");

	tcase_add_test(inputs_case, test_NULL_plus_I_Returns_ROMAN_CALCULATOR_MISSING_FIRST_TERM);
	tcase_add_test(inputs_case, test_I_plus_NULL_Returns_ROMAN_CALCULATOR_MISSING_SECOND_TERM);
	tcase_add_test(inputs_case, test_I_NULL_I_Returns_ROMAN_CALCULATOR_MISSING_OPERATOR);
	tcase_add_test(inputs_case, test_I_plus_I_With_No_Result_Buffer_Returns_ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER);
	suite_add_tcase(suite, inputs_case);

	return suite;
}
