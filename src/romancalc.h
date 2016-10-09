#ifndef ROMAN_CALC_H_DEFINED

#define ROMAN_CALC_H_DEFINED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "validate.h"
#include "convert.h"

extern arabicRomanPair roman_arabic_lookup[];
extern arabicRomanPair arabic_roman_lookup[];
extern arabicRomanPair* lastRomanArabicLookupEntry;
extern arabicRomanPair* lastArabicRomanLookupEntry;

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

typedef struct {
    char first_term[16];
    char second_term[16];
} uppercaseTerms;

enum CalculatorStatus RomanCalculator(char *first, char* operator, char* second, char* result);
char *convertArabicToRoman(int value);

#endif
