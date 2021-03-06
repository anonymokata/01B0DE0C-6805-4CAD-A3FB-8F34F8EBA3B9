#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "romancalctest.h"
#include "../src/romancalc.h"

char result[BUFFER_SIZE];

void setup(void) {
	memset(result, 0x00, sizeof(result));
}

void teardown(void) {

}

START_TEST(test_NULL_plus_I_Returns_FirstTermMissing) {
	ck_assert_int_eq(RomanCalculator(NULL, "+", "I", result), FirstTermMissing);
}
END_TEST

START_TEST(test_IIIIIIIIIIIIIIIII_plus_I_Returns_FirstTermInvalid) {
	ck_assert_int_eq(RomanCalculator("IIIIIIIIIIIIIIIII", "+","I", result), FirstTermInvalid);
}
END_TEST

START_TEST(test_I_plus_NULL_Returns_SecondTermMissing) {
	ck_assert_int_eq(RomanCalculator("I", "+", NULL, result), SecondTermMissing);
}
END_TEST

START_TEST(test_I_plus_IIIIIIIIIIIIIIIII_Returns_SecondTermInvalid) {
	ck_assert_int_eq(RomanCalculator("I", "+","IIIIIIIIIIIIIIIII", result), SecondTermInvalid);
}
END_TEST

START_TEST(test_I_NULL_I_Returns_OperatorMissing ) {
	ck_assert_int_eq(RomanCalculator("I", NULL, "I", result), OperatorMissing);
}
END_TEST

START_TEST(test_I_plus_I_With_No_Result_Buffer_Returns_OutputBufferMissing) {
	ck_assert_int_eq(RomanCalculator("I", "+", "I", NULL), OutputBufferMissing);
}
END_TEST

START_TEST(test_I_invalidOperator_I_Returns_OperatorInvalid) {
	ck_assert_int_eq(RomanCalculator("I", "*", "I", result), OperatorInvalid);
}
END_TEST

START_TEST(test_IXC_plus_I_Returns_FirstTermInvalid) {
	ck_assert_int_eq(RomanCalculator("IXC", "+", "I", result), FirstTermInvalid);
}
END_TEST

START_TEST(test_IC_plus_I_Returns_FirstTermInvalid) {
	ck_assert_int_eq(RomanCalculator("IC", "+", "I", result), FirstTermInvalid);
}
END_TEST

START_TEST(test_DM_plus_I_Returns_FirstTermInvalid) {
	ck_assert_int_eq(RomanCalculator("DM", "+", "I", result), FirstTermInvalid);
}
END_TEST

START_TEST(test_I_plus_DM_Returns_SecondTermInvalid) {
	ck_assert_int_eq(RomanCalculator("I", "+", "DM", result), SecondTermInvalid);
}
END_TEST

START_TEST(test_W_plus_I_Returns_FirstTermInvalid) {
	ck_assert_int_eq(RomanCalculator("W", "+", "I", result), FirstTermInvalid);
}
END_TEST

START_TEST(test_I_plus_W_Returns_SecondTermInvalid) {
	ck_assert_int_eq(RomanCalculator("I", "+", "W", result), SecondTermInvalid);
}
END_TEST

START_TEST(test_I_plus_I_Returns_II){
	RomanCalculator("I", "+", "I", result);
	ck_assert_str_eq(result, "II");
}
END_TEST

START_TEST(test_i_plus_I_Returns_II){
	RomanCalculator("i", "+", "I", result);
	ck_assert_str_eq(result, "II");
}
END_TEST

START_TEST(test_I_plus_i_Returns_II){
	RomanCalculator("I", "+", "i", result);
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

START_TEST(test_MMMM_plus_I_returns_FirstTermOverflow){
    ck_assert_int_eq( RomanCalculator("MMMM","+","I", result), FirstTermOverflow);
}
END_TEST

START_TEST(test_I_plus_MMMM_returns_SecondTermOverflow){
    ck_assert_int_eq( RomanCalculator("I","+","MMMM", result), SecondTermOverflow);
}
END_TEST

START_TEST(test_MMM_plus_MMM_returns_ResultOverflow){
    ck_assert_int_eq( RomanCalculator("MMM","+","MMM", result), ResultOverflow);
}
END_TEST

START_TEST(test_all_values_returns_correct_results){
    for( int i = 1 ; i < (MAX_ARABIC_VALUE - 1) ; i++ ){
        char term1[BUFFER_SIZE];
        int j = (MAX_ARABIC_VALUE - 1) - i;
        char term2[BUFFER_SIZE];
		char romanNumeral[BUFFER_SIZE];
        char result[BUFFER_SIZE];

        memset(term1, 0x00, sizeof(term1));
        memset(term2, 0x00, sizeof(term2));
        memset(result, 0x00, sizeof(result));
        memset(romanNumeral,0x00,sizeof(romanNumeral));

        strcat(term1, convertArabicToRoman(i, romanNumeral));

        memset(romanNumeral,0x00,sizeof(romanNumeral));
        strcat(term2, convertArabicToRoman(j, romanNumeral));

        ck_assert_int_eq(RomanCalculator(term1, "+", term2, result), Success);
    }
    
    ck_assert_int_eq(0,0);
}
END_TEST

START_TEST(test_II_minus_I_returns_I){
    RomanCalculator("II", "-", "I", result);
    ck_assert_str_eq( result, "I");
}
END_TEST

START_TEST(test_I_minus_I_returns_ResultUnderflow){
    ck_assert_int_eq(RomanCalculator("I", "-", "I", result), ResultUnderflow);
}
END_TEST

Suite* CalculatorSuite(void) {
	Suite* suite = suite_create("Roman Numeral Calculator Tests");
	TCase* inputs_case = tcase_create("Validate Input Arguments");

	tcase_add_checked_fixture(inputs_case, setup, NULL);

	tcase_add_test(inputs_case, test_NULL_plus_I_Returns_FirstTermMissing);
	tcase_add_test(inputs_case, test_IIIIIIIIIIIIIIIII_plus_I_Returns_FirstTermInvalid);
	tcase_add_test(inputs_case, test_I_plus_NULL_Returns_SecondTermMissing);
	tcase_add_test(inputs_case, test_I_plus_IIIIIIIIIIIIIIIII_Returns_SecondTermInvalid);
	tcase_add_test(inputs_case, test_I_NULL_I_Returns_OperatorMissing);
	tcase_add_test(inputs_case, test_I_plus_I_With_No_Result_Buffer_Returns_OutputBufferMissing);
	tcase_add_test(inputs_case, test_I_invalidOperator_I_Returns_OperatorInvalid);
	tcase_add_test(inputs_case, test_IXC_plus_I_Returns_FirstTermInvalid);
	tcase_add_test(inputs_case, test_IC_plus_I_Returns_FirstTermInvalid);
	tcase_add_test(inputs_case, test_DM_plus_I_Returns_FirstTermInvalid);
	tcase_add_test(inputs_case, test_I_plus_DM_Returns_SecondTermInvalid);

	suite_add_tcase(suite, inputs_case);

    TCase* invalid_numeral_case = tcase_create("Check for Invalid Characters");

    tcase_add_test(invalid_numeral_case, test_W_plus_I_Returns_FirstTermInvalid);
    tcase_add_test(invalid_numeral_case, test_I_plus_W_Returns_SecondTermInvalid);

    suite_add_tcase(suite, invalid_numeral_case);

    TCase* case_insensitive_case = tcase_create("Allow Case Insensitive Terms");
    
    tcase_add_test(case_insensitive_case, test_i_plus_I_Returns_II);
    tcase_add_test(case_insensitive_case, test_I_plus_i_Returns_II);
    
    suite_add_tcase(suite, case_insensitive_case);
	
    TCase* adding_case = tcase_create("Addition tests");

	tcase_add_checked_fixture(adding_case, setup, NULL);
	tcase_add_test(adding_case, test_I_plus_I_Returns_II);
	tcase_add_test(adding_case, test_I_plus_II_Returns_III);
	tcase_add_test(adding_case, test_I_plus_III_Returns_IV);
	tcase_add_test(adding_case, test_I_plus_V_Returns_VI);
	tcase_add_test(adding_case, test_LIII_plus_DCDLIX_returns_MXII);
	tcase_add_test(adding_case, test_XLIX_plus_I_returns_L);
    tcase_add_test(adding_case, test_MMMM_plus_I_returns_FirstTermOverflow);
    tcase_add_test(adding_case, test_I_plus_MMMM_returns_SecondTermOverflow);
    tcase_add_test(adding_case, test_MMM_plus_MMM_returns_ResultOverflow);
    tcase_add_test(adding_case, test_all_values_returns_correct_results); 
	suite_add_tcase(suite, adding_case);
    
    TCase* subtraction_case = tcase_create("Subtraction tests");
    tcase_add_test(subtraction_case, test_II_minus_I_returns_I);
    tcase_add_test(subtraction_case, test_I_minus_I_returns_ResultUnderflow);

    suite_add_tcase(suite, subtraction_case);
	return suite;
}
