#include <stdio.h>
#include <stdbool.h>
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

typedef struct arabicRomanPair {
	int 	arabic;
	char* 	roman;
	int 	romanLength;
} arabicRomanPair; 

arabicRomanPair roman_arabic_lookup[] = 	{
												{   3, 	ROMAN_III, sizeof(ROMAN_III) - 1},
												{   2, 	ROMAN_II , sizeof(ROMAN_II) - 1 },
												{   4, 	ROMAN_IV , sizeof(ROMAN_IV) - 1 },
												{   9, 	ROMAN_IX , sizeof(ROMAN_IX) - 1 },
												{  40, 	ROMAN_XL , sizeof(ROMAN_XL) - 1 },
												{  90, 	ROMAN_XC , sizeof(ROMAN_XC) - 1 },
												{ 400, 	ROMAN_CD , sizeof(ROMAN_CD) - 1 },
												{ 900, 	ROMAN_CM , sizeof(ROMAN_CM) - 1 },
												{   1, 	ROMAN_I  , sizeof(ROMAN_I) - 1  },
												{   5, 	ROMAN_V  , sizeof(ROMAN_V) - 1  },
												{  10, 	ROMAN_X  , sizeof(ROMAN_X) - 1  },
												{  50, 	ROMAN_L  , sizeof(ROMAN_L) - 1  },
												{ 100, 	ROMAN_C  , sizeof(ROMAN_C) - 1  },
												{ 500, 	ROMAN_D  , sizeof(ROMAN_D) - 1  },
												{1000, 	ROMAN_M  , sizeof(ROMAN_M) - 1  }
											};

arabicRomanPair arabic_roman_lookup[] = 	{
												{   1, 	ROMAN_I  , sizeof(ROMAN_I) - 1  },
												{   2, 	ROMAN_II , sizeof(ROMAN_II) - 1 },
												{   3, 	ROMAN_III, sizeof(ROMAN_III) - 1},
												{   4, 	ROMAN_IV , sizeof(ROMAN_IV) - 1 },
												{   5, 	ROMAN_V  , sizeof(ROMAN_V) - 1  },
												{   9, 	ROMAN_IX , sizeof(ROMAN_IX) - 1 },
												{  10, 	ROMAN_X  , sizeof(ROMAN_X) - 1  },
												{  40, 	ROMAN_XL , sizeof(ROMAN_XL) - 1 },
												{  50, 	ROMAN_L  , sizeof(ROMAN_L) - 1  },
												{  90, 	ROMAN_XC , sizeof(ROMAN_XC) - 1 },
												{ 100, 	ROMAN_C  , sizeof(ROMAN_C) - 1  },
												{ 400, 	ROMAN_CD , sizeof(ROMAN_CD) - 1 },
												{ 500, 	ROMAN_D  , sizeof(ROMAN_D) - 1  },
												{ 900, 	ROMAN_CM , sizeof(ROMAN_CM) - 1 },
												{1000, 	ROMAN_M  , sizeof(ROMAN_M) - 1  }	
											};

int convertRomanToArabic(char* romanNumeral){
	char* temp = romanNumeral;
	int accumulator = 0;

	while( strlen(temp) != 0 ) {
		arabicRomanPair* pair = roman_arabic_lookup;

		if(temp[0] == '+') break;

		while( pair < &roman_arabic_lookup[sizeof(roman_arabic_lookup)] ) {
			if(strncmp(temp, pair->roman, pair->romanLength) == 0) {
				accumulator += pair->arabic;
				break;
			}

			pair++;
		}
		
		temp += pair->romanLength;
	}

	return accumulator;
}

char romanNumeral[16];

char* convertArabicToRoman(int arabicNumber){
	int temp = arabicNumber;
	int lookup_entry_size =  sizeof(arabic_roman_lookup) / sizeof(arabicRomanPair);
	arabicRomanPair* lastEntry = &arabic_roman_lookup[lookup_entry_size - 1];

	memset(romanNumeral,0x00,sizeof(romanNumeral));
	
	while(temp > 0) {

		arabicRomanPair* pair = arabic_roman_lookup;

		while( pair <= lastEntry ){

			if( pair == lastEntry ) {
				strcat(romanNumeral, pair->roman);
				temp -= pair->arabic;
				break;
			}
	
			if(pair->arabic > temp) {
				arabicRomanPair* previousEntry = pair - 1;
				strcat(romanNumeral, previousEntry->roman);
				temp -= previousEntry->arabic;				
				pair++;
				break;
			}
			else {
				pair++;
			}
		}
	}

	return romanNumeral; 
}
