#ifndef VALIDATE_H_DEFINED
#define VALIDATE_H_DEFINED

#include "convert.h"

char* uppercase(char* parm);
_Bool validateRomanNumeral(char *romanNumeral);
int validateInputParametersPresent(char* first, char* operator, char* second, char* result);
int validateInputParametersValid(char* first, char* operator, char* second);
int validateInputTermsProperSize(char* first, char* second);

#define BUFFER_SIZE 16

enum CalculatorStatus {
    Success,
    FirstTermMissing,
    FirstTermInvalid,
    FirstTermOverflow,
    SecondTermMissing,
    SecondTermInvalid,
    SecondTermOverflow,
    OperatorMissing,
    OperatorInvalid,
    OutputBufferMissing,
    ResultUnderflow,
    ResultOverflow
};

#endif