#ifndef VALIDATE_H_DEFINED
#define VALIDATE_H_DEFINED

#include "romancalc.h"

char* uppercase(char* parm);
_Bool validateRomanNumeral(char *romanNumeral);
int validateInputParameters(char* first, char* operator, char* second, char* result);

extern char first_parm[16];
extern char second_parm[16];

#endif