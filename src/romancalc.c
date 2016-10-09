#include "romancalc.h"

extern char first_parm[16];
extern char second_parm[16];

#define additionOperation()  strcmp(operator, "+" ) == 0

enum CalculatorStatus RomanCalculator(char *first, char* operator, char* second, char* result) {

	int returnCode;

	if( ( returnCode = validateInputParameters(first, operator, second, result) ) != Success ) {
		return returnCode;
    }

	int first_in_arabic;
	int second_in_arabic;

	first_in_arabic = convertRomanToArabic(first_parm);

    if( first_in_arabic > MAX_ARABIC_VALUE ) {
        return FirstTermOverflow;
    }

	second_in_arabic = convertRomanToArabic(second_parm);

    if( second_in_arabic  > MAX_ARABIC_VALUE ) {
        return SecondTermOverflow;
    }

    if(additionOperation()) {
        int sum = first_in_arabic + second_in_arabic;

        if( sum > MAX_ARABIC_VALUE ) {
            return ResultOverflow;
        }

	    strcpy(result, convertArabicToRoman(sum));
    }
    else {
        int difference = first_in_arabic - second_in_arabic;

        if( difference < 1 ) {
            return ResultUnderflow;
        }

        strcpy(result, convertArabicToRoman(difference));
    }

	return Success;
}