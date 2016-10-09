#include "romancalc.h"

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

typedef struct {
    char first_term[BUFFER_SIZE];
    char second_term[BUFFER_SIZE];
} uppercaseTerms;

#define additionOperation()  strcmp(operator, "+" ) == 0

enum CalculatorStatus RomanCalculator(char *first, char* operator, char* second, char* result) {

	int returnCode;
	uppercaseTerms terms;

	if( ( returnCode = validateInputParametersPresent(first, operator, second, result) ) != Success ) {
		return returnCode;
    }

	if( ( returnCode = validateInputTermsProperSize(first, second) ) != Success ) {
		return returnCode;
	}

    memset(terms.first_term, 0x00, sizeof(terms.first_term));
    strcat(terms.first_term, first);
    uppercase(terms.first_term);

    memset(terms.second_term, 0x00, sizeof(terms.second_term));
    strcat(terms.second_term, second);
    uppercase(terms.second_term);

	if( ( returnCode = validateInputParametersValid(terms.first_term, operator, terms.second_term) ) != Success ) {
		return returnCode;
    }

	int first_in_arabic;
	int second_in_arabic;

	first_in_arabic = convertRomanToArabic(terms.first_term);

    if( first_in_arabic > MAX_ARABIC_VALUE ) {
        return FirstTermOverflow;
    }

	second_in_arabic = convertRomanToArabic(terms.second_term);

    if( second_in_arabic  > MAX_ARABIC_VALUE ) {
        return SecondTermOverflow;
    }

	char romanNumeral[BUFFER_SIZE];
	memset(romanNumeral, 0x00, sizeof(romanNumeral));

    if(additionOperation()) {
        int sum = first_in_arabic + second_in_arabic;

        if( sum > MAX_ARABIC_VALUE ) {
            return ResultOverflow;
        }

	    strcpy(result, convertArabicToRoman(sum, romanNumeral));
    }
    else {
        int difference = first_in_arabic - second_in_arabic;

        if( difference < 1 ) {
            return ResultUnderflow;
        }

        strcpy(result, convertArabicToRoman(difference, romanNumeral));
    }

	return Success;
}