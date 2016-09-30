#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "romancalc.h"

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


arabicRomanPair* lastRomanArabicLookupEntry = &roman_arabic_lookup[sizeof(roman_arabic_lookup) / 
                                                sizeof(arabicRomanPair) - 1];

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

arabicRomanPair* lastArabicRomanLookupEntry = &arabic_roman_lookup[sizeof(roman_arabic_lookup) / 
                                                sizeof(arabicRomanPair) - 1];

int convertRomanToArabic(char* romanNumeral){
	char* position_in_roman_numeral = romanNumeral;
	int accumulator = 0;

	while( strlen(position_in_roman_numeral) != 0 ) {
		arabicRomanPair* pair = roman_arabic_lookup;

		while( pair <= lastRomanArabicLookupEntry ) {
			if(strncmp(position_in_roman_numeral, pair->roman, pair->romanLength) == 0) {
				accumulator += pair->arabic;
				break;
			}

			pair++;
		}
		
		position_in_roman_numeral += pair->romanLength;
	}

	return accumulator;
}

char romanNumeral[16];

char* convertArabicToRoman(int arabic_number){
	int decremented_value = arabic_number;

	memset(romanNumeral,0x00,sizeof(romanNumeral));
	
	while(decremented_value > 0) {
		arabicRomanPair* pair = arabic_roman_lookup;

		do {
            if( pair == lastArabicRomanLookupEntry && pair->arabic <= decremented_value) {
				strcat(romanNumeral, pair->roman);
				decremented_value -= pair->arabic;
				break;
			}
	
			if(pair->arabic > decremented_value) {
				strcat(romanNumeral, (pair - 1)->roman);
				decremented_value -= (pair - 1)->arabic;
				break;
			}
            else if (pair->arabic == decremented_value) {
                strcat(romanNumeral, pair->roman);
                decremented_value -= pair->arabic;
                break;
            }

			pair++;
		} while( pair <= lastArabicRomanLookupEntry && decremented_value > 0);
	}

	return romanNumeral; 
}

_Bool validateRomanNumeral(char *romanNumeral) {

	int arabic_current_value = 0;
	int arabic_previous_value = 0;
	int current_index = strlen(romanNumeral);
	_Bool valid_term;

	while( current_index > 0 ) {
		valid_term = false;

		for( arabicRomanPair* pair = roman_arabic_lookup ; pair <= lastRomanArabicLookupEntry ; pair++ ) {
			if(memcmp(&romanNumeral[current_index - pair->romanLength], pair->roman, pair->romanLength) == 0) {
				current_index -= pair->romanLength;
				arabic_current_value = pair->arabic;
				valid_term = true;
				break;
			}
		}

		if(!valid_term || arabic_current_value < arabic_previous_value ) {
			valid_term = false;
			break;
		}
		
		if(current_index == 0) {
			break;
		}
		
		arabic_previous_value = arabic_current_value;
	}

	return valid_term;
}

int validateInputParameters(char* first, char* operator, char* second, char* result) {

	if( first == NULL )
		return ROMAN_CALCULATOR_MISSING_FIRST_TERM;

	if( second == NULL )
		return ROMAN_CALCULATOR_MISSING_SECOND_TERM;

	if( operator == NULL )
		return ROMAN_CALCULATOR_MISSING_OPERATOR;

	if( result == NULL )
		return ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER;

	if( strcmp(operator, "+") && strcmp(operator, "-" ) ) 
		return ROMAN_CALCULATOR_INVALID_OPERATOR;

	if( !validateRomanNumeral(first) )
		return ROMAN_CALCULATOR_INVALID_FIRST_TERM;

	if( !validateRomanNumeral(second) )
		return ROMAN_CALCULATOR_INVALID_SECOND_TERM;

	return ROMAN_CALCULATOR_SUCCESS;	
}

int RomanCalculator(char *first, char* operator, char* second, char* result) {

	int returnCode;

	if( ( returnCode = validateInputParameters(first, operator, second, result) ) != 
        ROMAN_CALCULATOR_SUCCESS )
		return returnCode;

	int first_in_arabic;
	int second_in_arabic;

	first_in_arabic = convertRomanToArabic(first);

    if( first_in_arabic > MAX_ARABIC_VALUE ) {
        return ROMAN_CALCULATOR_FIRST_TERM_OVERFLOW;
    }

	second_in_arabic = convertRomanToArabic(second);

    if( second_in_arabic  > MAX_ARABIC_VALUE ) {
        return ROMAN_CALCULATOR_SECOND_TERM_OVERFLOW;
    }

    if( strcmp(operator, "+" ) == 0) {
        int sum = first_in_arabic + second_in_arabic;

        if( sum > MAX_ARABIC_VALUE ) {
            return ROMAN_CALCULATOR_RESULT_OVERFLOW;
        }

	    strcpy(result, convertArabicToRoman(sum));
    }
    else {
        int difference = first_in_arabic - second_in_arabic;

        if( difference < 1 )
            return ROMAN_CALCULATOR_RESULT_UNDERFLOW;

        strcpy(result, convertArabicToRoman(difference));
    }

	return ROMAN_CALCULATOR_SUCCESS;
}

