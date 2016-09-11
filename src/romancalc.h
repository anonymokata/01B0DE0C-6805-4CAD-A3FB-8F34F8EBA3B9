#ifndef ROMAN_CALC_H_DEFINED

#define ROMAN_CALC_H_DEFINED

#define ROMAN_CALCULATOR_SUCCESS 			 	0
#define ROMAN_CALCULATOR_MISSING_FIRST_TERM  	1
#define ROMAN_CALCULATOR_MISSING_SECOND_TERM 	2
#define ROMAN_CALCULATOR_MISSING_OPERATOR       3
#define ROMAN_CALCULATOR_MISSING_OUTPUT_BUFFER 	4
#define ROMAN_CALCULATOR_INVALID_OPERATOR 		5
#define ROMAN_CALCULATOR_FAILURE 				255

int RomanCalculator(char *first, char* operator, char* second, char* result);

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
#endif
