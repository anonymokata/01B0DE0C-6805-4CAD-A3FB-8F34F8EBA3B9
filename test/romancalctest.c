#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "romancalctest.h"
#include "../src/romancalc.h"

char result[16];

void setup(void) {
	memset(result, 0x00, sizeof(result));
}

void teardown(void) {

}

START_TEST(test_NULL_plus_I_Returns_ROMAN_CALCULATOR_MISSING_FIRST_TERM) {
	ck_assert_int_eq(RomanCalculator(NULL, "+", "I", result), ROMAN_CALCULATOR_MISSING_FIRST_TERM);
}
END_TEST

START_TEST(test_I_plus_NULL_Returns_ROMAN_CALCULATOR_MISSING_SECOND_TERM) {
	ck_assert_int_eq(RomanCalculator("I", "+", NULL, result), ROMAN_CALCULATOR_MISSING_SECOND_TERM);
}
END_TEST

START_TEST(test_I_NULL_I_Returns_ROMAN_CALCULATOR_MISSING_OPERATOR ) {
	ck_assert_int_eq(RomanCalculator("I", NULL, "I", result), ROMAN_CALCULATOR_MISSING_OPERATOR);
}
END_TEST

START_TEST(test_I_plus_I_With_No_Result_Buffer_Returns_ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER) {
	ck_assert_int_eq(RomanCalculator("I", "+", "I", NULL), ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER);
}
END_TEST

START_TEST(test_I_invalidOperator_I_Returns_ROMAN_CALCULATOR_INVALID_OPERATOR) {
	ck_assert_int_eq(RomanCalculator("I", "*", "I", result), ROMAN_CALCULATOR_INVALID_OPERATOR);
}
END_TEST

START_TEST(test_I_plus_I_Returns_II){
	RomanCalculator("I", "+", "I", result);
	ck_assert_str_eq(result, "II");
}
END_TEST

START_TEST(test_I_plus_II_Returns_III){
	RomanCalculator("I", "+", "II", result);
	ck_assert_str_eq(result, "III");
}
END_TEST

START_TEST(test_I_plus_III_Returns_IV){
	RomanCalculator("I", "+", "III", result);
	ck_assert_str_eq(result, "IV");
}
END_TEST

START_TEST(test_I_plus_V_Returns_VI){
	RomanCalculator("I", "+", "V", result);
	ck_assert_str_eq(result, "VI");
}
END_TEST

START_TEST(test_LIII_plus_DCDLIX_returns_MXII){
	RomanCalculator("LIII", "+", "DCDLIX", result);
	ck_assert_str_eq(result, "MXII");
}
END_TEST

START_TEST(test_XLIX_plus_I_returns_L){
	RomanCalculator("XLIX", "+", "I", result);
	ck_assert_str_eq(result, "L");
}
END_TEST

Suite* CalculatorSuite(void) {
	Suite* suite = suite_create("Roman Numeral Calculator Tests");
	TCase* inputs_case = tcase_create("Validate Input Arguments");

	tcase_add_checked_fixture(inputs_case, setup, NULL);

	tcase_add_test(inputs_case, test_NULL_plus_I_Returns_ROMAN_CALCULATOR_MISSING_FIRST_TERM);
	tcase_add_test(inputs_case, test_I_plus_NULL_Returns_ROMAN_CALCULATOR_MISSING_SECOND_TERM);
	tcase_add_test(inputs_case, test_I_NULL_I_Returns_ROMAN_CALCULATOR_MISSING_OPERATOR);
	tcase_add_test(inputs_case, test_I_plus_I_With_No_Result_Buffer_Returns_ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER);
	tcase_add_test(inputs_case, test_I_invalidOperator_I_Returns_ROMAN_CALCULATOR_INVALID_OPERATOR);
	suite_add_tcase(suite, inputs_case);
	TCase* adding_case = tcase_create("Addition tests");

	tcase_add_checked_fixture(adding_case, setup, NULL);
	tcase_add_test(adding_case, test_I_plus_I_Returns_II);
	tcase_add_test(adding_case, test_I_plus_II_Returns_III);
	tcase_add_test(adding_case, test_I_plus_III_Returns_IV);
	tcase_add_test(adding_case, test_I_plus_V_Returns_VI);
	tcase_add_test(adding_case, test_LIII_plus_DCDLIX_returns_MXII);
	tcase_add_test(adding_case, test_XLIX_plus_I_returns_L);
	suite_add_tcase(suite, adding_case);
	return suite;
}
