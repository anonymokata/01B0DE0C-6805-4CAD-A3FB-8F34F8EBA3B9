#include "validate.h"

char* uppercase(char* parm){
    int parm_length = strlen(parm);
   
    for(int i = 0 ; i < parm_length ; i++) {
        parm[i] = toupper((int) parm[i]);    
    }

    return parm;
}

#define isNotValidOperator()  strcmp(operator, "+") && strcmp(operator, "-" )

int validateInputParametersValid(char* first, char* operator, char* second) {

	if(isNotValidOperator()) {
		return OperatorInvalid;
    }

	if( !validateRomanNumeral(first) ) {
		return FirstTermInvalid;
    }

	if( !validateRomanNumeral(second) ) {
		return SecondTermInvalid;
    }

    return Success;
}

int validateInputTermsProperSize(char* first, char* second) {
    if(strlen(first) > BUFFER_SIZE)
        return FirstTermInvalid;

    if( strlen(second) > BUFFER_SIZE )
        return SecondTermInvalid;

    return Success;
}

int validateInputParametersPresent(char* first, char* operator, char* second, char* result) {

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
	_Bool romanNumeralIsValid = false;

    if(current_index > BUFFER_SIZE)
        return romanNumeralIsValid;

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