#ifndef ROMAN_CALC_H_DEFINED

#define ROMAN_CALC_H_DEFINED

#define ROMAN_CALCULATOR_SUCCESS 			 0
#define ROMAN_CALCULATOR_MISSING_FIRST_TERM  1
#define ROMAN_CALCULATOR_MISSING_SECOND_TERM 2
#define ROMAN_CALCULATOR_MISSING_OPERATOR    3

int RomanCalculator(char *first, char* operator, char* second, char* result);

#endif
