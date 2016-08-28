#include <stdio.h>
#include "romancalc.h"


int RomanCalculator(char *first, char* operator, char* second, char* result) {

	if( first == NULL )
		return ROMAN_CALCULATOR_MISSING_FIRST_TERM;

	if( second == NULL )
		return ROMAN_CALCULATOR_MISSING_SECOND_TERM;

	if( operator == NULL )
		return ROMAN_CALCULATOR_MISSING_OPERATOR;

	return ROMAN_CALCULATOR_SUCCESS;
}
