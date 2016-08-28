#include <stdio.h>
#include "romancalc.h"


int RomanCalculator(char *first, char* operator, char* second, char* result) {

	if( first == NULL )
		return ROMAN_CALCULATOR_INVALID_FIRST_TERM;

	if( second == NULL )
		return ROMAN_CALCULATOR_INVALID_SECOND_TERM;

	return ROMAN_CALCULATOR_SUCCESS;
}
