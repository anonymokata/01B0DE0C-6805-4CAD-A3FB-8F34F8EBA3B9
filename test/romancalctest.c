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

START_TEST(test_IXC_plus_I_Returns_ROMAN_CALCULATOR_INVALID_FIRST_TERM) {
	ck_assert_int_eq(RomanCalculator("IXC", "+", "I", result), ROMAN_CALCULATOR_INVALID_FIRST_TERM);
}
END_TEST

START_TEST(test_IC_plus_I_Returns_ROMAN_CALCULATOR_INVALID_FIRST_TERM) {
	ck_assert_int_eq(RomanCalculator("IC", "+", "I", result), ROMAN_CALCULATOR_INVALID_FIRST_TERM);
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

START_TEST(test_MMMM_plus_I_returns_ROMAN_CALCULATOR_FIRST_TERM_OVERFLOW){
    ck_assert_int_eq( RomanCalculator("MMMM","+","I", result), ROMAN_CALCULATOR_FIRST_TERM_OVERFLOW);
}
END_TEST

START_TEST(test_I_plus_MMMM_returns_ROMAN_CALCULATOR_SECOND_TERM_OVERFLOW){
    ck_assert_int_eq( RomanCalculator("I","+","MMMM", result), ROMAN_CALCULATOR_SECOND_TERM_OVERFLOW);
}
END_TEST

START_TEST(test_MMM_plus_MMM_returns_ROMAN_CALCULATOR_RESULT_OVERFLOW){
    ck_assert_int_eq( RomanCalculator("MMM","+","MMM", result), ROMAN_CALCULATOR_RESULT_OVERFLOW);
}
END_TEST

START_TEST(test_all_values_returns_correct_result){
    
    for( int i = 1 ; i < (MAX_ARABIC_VALUE - 1) ; i++ ){
        char term1[16];
        int j = (MAX_ARABIC_VALUE - 1) - i;
        char term2[16];
        char result[16];

        memset(term1, 0x00, sizeof(term1));
        memset(term2, 0x00, sizeof(term2));
        memset(result, 0x00, sizeof(result));
        
        strcat(term1, convertArabicToRoman(i));
        strcat(term2, convertArabicToRoman(j));

        ck_assert_int_eq(RomanCalculator(term1, "+", term2, result), ROMAN_CALCULATOR_SUCCESS);
    }
}
END_TEST

START_TEST(test_II_minus_I_returns_I){
    RomanCalculator("II", "-", "I", result);
    ck_assert_str_eq( result, "I");
}
END_TEST

START_TEST(test_I_minus_I_returns_ROMAN_CALCULATOR_RESULT_UNDERFLOW){
    ck_assert_int_eq(RomanCalculator("I", "-", "I", result), ROMAN_CALCULATOR_RESULT_UNDERFLOW);
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
	tcase_add_test(inputs_case, test_IXC_plus_I_Returns_ROMAN_CALCULATOR_INVALID_FIRST_TERM);
	tcase_add_test(inputs_case, test_IC_plus_I_Returns_ROMAN_CALCULATOR_INVALID_FIRST_TERM);
	suite_add_tcase(suite, inputs_case);
	TCase* adding_case = tcase_create("Addition tests");

	tcase_add_checked_fixture(adding_case, setup, NULL);
	tcase_add_test(adding_case, test_I_plus_I_Returns_II);
	tcase_add_test(adding_case, test_I_plus_II_Returns_III);
	tcase_add_test(adding_case, test_I_plus_III_Returns_IV);
	tcase_add_test(adding_case, test_I_plus_V_Returns_VI);
	tcase_add_test(adding_case, test_LIII_plus_DCDLIX_returns_MXII);
	tcase_add_test(adding_case, test_XLIX_plus_I_returns_L);
    tcase_add_test(adding_case, test_MMMM_plus_I_returns_ROMAN_CALCULATOR_FIRST_TERM_OVERFLOW);
    tcase_add_test(adding_case, test_I_plus_MMMM_returns_ROMAN_CALCULATOR_SECOND_TERM_OVERFLOW);
    tcase_add_test(adding_case, test_MMM_plus_MMM_returns_ROMAN_CALCULATOR_RESULT_OVERFLOW);
    tcase_add_test(adding_case, test_all_values_returns_correct_result);
	suite_add_tcase(suite, adding_case);
    
    TCase* subtraction_case = tcase_create("Subtraction tests");
    tcase_add_test(subtraction_case, test_II_minus_I_returns_I);
    tcase_add_test(subtraction_case, test_I_minus_I_returns_ROMAN_CALCULATOR_RESULT_UNDERFLOW);

    suite_add_tcase(suite, subtraction_case);
	return suite;
}
