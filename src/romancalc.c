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

	int first_in_arabic;
	int second_in_arabic;

	first_in_arabic = convertRomanToArabic(first);
	second_in_arabic = convertRomanToArabic(second);
	strcpy(result, convertArabicToRoman(first_in_arabic + second_in_arabic));

	return ROMAN_CALCULATOR_SUCCESS;
}

typedef struct arabicRomanPairs {
	int 	arabic;
	char* 	roman;
} arabicRomanPairs; 

arabicRomanPairs arabic_roman_lookup[] = 	{
												{   1, 	"I"  },
												{   2, 	"II" },
												{   3, 	"III"},
												{   4, 	"IV" },
												{   5, 	"V"  },
												{   9, 	"IX" },
												{  10, 	"X"  },
												{  40, 	"XL" },
												{  50, 	"L"  },
												{  90, 	"XC" },
												{ 100, 	"C"  },
												{ 400, 	"CD" },
												{ 500, 	"D"  },
												{ 900, 	"CM" },
												{1000, 	"M"  }
											};

int convertRomanToArabic(char* romanNumeral){

	arabicRomanPairs* pairs = arabic_roman_lookup;

	while( pairs < &arabic_roman_lookup[sizeof(arabic_roman_lookup)] ) {
		if(strcmp(romanNumeral, pairs->roman) == 0)
			break;
		pairs++;
	}

	return pairs->arabic;
}

char* convertArabicToRoman(int arabicNumber){

	arabicRomanPairs* pairs = arabic_roman_lookup;

	while( pairs < &arabic_roman_lookup[sizeof(arabic_roman_lookup)] ){
		if(pairs->arabic == arabicNumber)
			break;

		pairs++;
	}

	return pairs->roman; 
}
