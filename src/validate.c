#include "validate.h"

char* uppercase(char* parm){
    int parm_length = strlen(parm);
   
    for(int i = 0 ; i < parm_length ; i++) {
        parm[i] = toupper((int) parm[i]);    
    }

    return parm;
}

char first_parm[16];
char second_parm[16];

#define isNotValidOperator()  strcmp(operator, "+") && strcmp(operator, "-" )

int validateInputParameters(char* first, char* operator, char* second, char* result) {

	if( first == NULL ) {
		return FirstTermMissing;
    }

	if( second == NULL ) {
		return SecondTermMissing;
    }

	if( operator == NULL ) {
		return OperatorMissing;
    }

	if( result == NULL ) {
		return OutputBufferMissing;
    }

    memset(first_parm, 0x00, sizeof(first_parm));
    strcat(first_parm, first);
    uppercase(first_parm);

    memset(second_parm, 0x00, sizeof(second_parm));
    strcat(second_parm, second);
    uppercase(second_parm);

	if(isNotValidOperator()) {
		return OperatorInvalid;
    }

	if( !validateRomanNumeral(first_parm) ) {
		return FirstTermInvalid;
    }

	if( !validateRomanNumeral(second_parm) ) {
		return SecondTermInvalid;
    }

	return Success;	
}

#define notFinishedParsingRomanNumeral()  current_index > 0 
#define endOfRomanNumeralString() strlen(romanNumeral)
#define romanSubstringMatchesCurrentTableEntry() memcmp(&romanNumeral[current_index - pair->romanLength], pair->roman, pair->romanLength) == 0
#define valueNotFoundOrIsLessThanPrevious() !romanNumeralIsValid || current_value < previous_value
#define entireRomanNumeralProcessed() current_index == 0

_Bool validateRomanNumeral(char *romanNumeral) {

	int current_value = 0;
	int previous_value = 0;
	int current_index = endOfRomanNumeralString();
	_Bool romanNumeralIsValid;

	while(notFinishedParsingRomanNumeral()) {
		romanNumeralIsValid = false;

		for( arabicRomanPair* pair = roman_arabic_lookup ; pair <= lastRomanArabicLookupEntry ; pair++ ) {
			if(romanSubstringMatchesCurrentTableEntry()) {
				current_index -= pair->romanLength;
				current_value = pair->arabic;
				romanNumeralIsValid = true;
				break;
			}
		}

		if(valueNotFoundOrIsLessThanPrevious() ) {
			romanNumeralIsValid = false;
			break;
		}
		
		if(entireRomanNumeralProcessed()) {
			break;
		}
		
		previous_value = current_value;
	}

	return romanNumeralIsValid;
}