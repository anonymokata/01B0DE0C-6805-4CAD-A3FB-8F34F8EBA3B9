#ifndef ROMAN_CALC_H_DEFINED

#define ROMAN_CALC_H_DEFINED

#include "validate.h"
#include "convert.h"

enum CalculatorStatus RomanCalculator(char *first, char* operator, char* second, char* result);
#define BUFFER_SIZE 16
#endif
