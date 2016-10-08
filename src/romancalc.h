#ifndef ROMAN_CALC_H_DEFINED

#define ROMAN_CALC_H_DEFINED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "validate.h"

typedef struct arabicRomanPair {
	int 	arabic;
	char* 	roman;
	int 	romanLength;
} arabicRomanPair; 

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

enum CalculatorStatus RomanCalculator(char *first, char* operator, char* second, char* result);
char *convertArabicToRoman(int value);

#define ROMAN_I 	"I" 	/* 		1 */
#define ROMAN_II 	"II" 	/* 		2 */
#define ROMAN_III 	"III" 	/* 		3 */
#define ROMAN_IV 	"IV" 	/* 		4 */
#define ROMAN_V 	"V" 	/* 		5 */
#define ROMAN_IX 	"IX" 	/* 		9 */
#define ROMAN_X 	"X" 	/* 	   10 */
#define ROMAN_XL 	"XL" 	/* 	   40 */
#define ROMAN_L 	"L" 	/* 	   50 */
#define ROMAN_XC 	"XC" 	/* 	   90 */
#define ROMAN_C 	"C" 	/* 	  100 */
#define ROMAN_CD 	"CD" 	/* 	  400 */
#define ROMAN_D 	"D" 	/* 	  500 */
#define ROMAN_CM 	"CM" 	/* 	  900 */
#define ROMAN_M 	"M" 	/* 	 1000 */

#define MAX_ARABIC_VALUE    3999
#endif
