#include <stdio.h>
#include <string.h>
#include "romancalc.h"

int convertRomanToArabic(char * romanNumeral);
char* convertArabicToRoman(int arabicNumber);

int RomanCalculator(char *first, char* operator, char* second, char* result) {

	if( first == NULL )
		return ROMAN_CALCULATOR_MISSING_FIRST_TERM;

	if( second == NULL )
		return ROMAN_CALCULATOR_MISSING_SECOND_TERM;

	if( operator == NULL )
		return ROMAN_CALCULATOR_MISSING_OPERATOR;

	if( result == NULL )
		return ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER;

	if( strcmp(operator, "+") && strcmp(operator, "-" ) ) {
		return ROMAN_CALCULATOR_INVALID_OPERATOR;
	}

	int firstInArabic;
	int secondInArabic;

	firstInArabic = convertRomanToArabic(first);
	secondInArabic = convertRomanToArabic(second);
	strcpy(result, convertArabicToRoman(firstInArabic + secondInArabic));

	printf("\nfirst = %s, second=%s, result=%s, firstInArabic=%i, secondInArabic=%i", first, second, result, firstInArabic, secondInArabic);
	return ROMAN_CALCULATOR_SUCCESS;
}

int convertRomanToArabic(char* romanNumeral){

	printf("\n\tromanNumeral=%s", romanNumeral);

	if( strcmp(romanNumeral, "I") == 0 )
		return 1;

	if( strcmp(romanNumeral, "II") == 0 )
		return 2;

	return 3;
}

char* convertArabicToRoman(int arabicNumber){
	printf("\n\tarabicNumber=%i", arabicNumber);

	if(arabicNumber == 1)
		return "I";

	if(arabicNumber == 2)
		return "II";

	return "III";
}
