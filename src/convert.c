#include "convert.h"

arabicRomanPair roman_arabic_lookup[] = 	{
												{   3, 	ROMAN_III, sizeof(ROMAN_III) - 1},
												{   2, 	ROMAN_II , sizeof(ROMAN_II) - 1 },
												{   4, 	ROMAN_IV , sizeof(ROMAN_IV) - 1 },
												{   9, 	ROMAN_IX , sizeof(ROMAN_IX) - 1 },
												{  40, 	ROMAN_XL , sizeof(ROMAN_XL) - 1 },
												{  90, 	ROMAN_XC , sizeof(ROMAN_XC) - 1 },
												{ 400, 	ROMAN_CD , sizeof(ROMAN_CD) - 1 },
												{ 900, 	ROMAN_CM , sizeof(ROMAN_CM) - 1 },
												{   1, 	ROMAN_I  , sizeof(ROMAN_I) - 1  },
												{   5, 	ROMAN_V  , sizeof(ROMAN_V) - 1  },
												{  10, 	ROMAN_X  , sizeof(ROMAN_X) - 1  },
												{  50, 	ROMAN_L  , sizeof(ROMAN_L) - 1  },
												{ 100, 	ROMAN_C  , sizeof(ROMAN_C) - 1  },
												{ 500, 	ROMAN_D  , sizeof(ROMAN_D) - 1  },
												{1000, 	ROMAN_M  , sizeof(ROMAN_M) - 1  }
											};

arabicRomanPair* lastRomanArabicLookupEntry = &roman_arabic_lookup[sizeof(roman_arabic_lookup) / 
                                                sizeof(arabicRomanPair) - 1];

arabicRomanPair arabic_roman_lookup[] = 	{
												{   1, 	ROMAN_I  , sizeof(ROMAN_I) - 1  },
												{   2, 	ROMAN_II , sizeof(ROMAN_II) - 1 },
												{   3, 	ROMAN_III, sizeof(ROMAN_III) - 1},
												{   4, 	ROMAN_IV , sizeof(ROMAN_IV) - 1 },
												{   5, 	ROMAN_V  , sizeof(ROMAN_V) - 1  },
												{   9, 	ROMAN_IX , sizeof(ROMAN_IX) - 1 },
												{  10, 	ROMAN_X  , sizeof(ROMAN_X) - 1  },
												{  40, 	ROMAN_XL , sizeof(ROMAN_XL) - 1 },
												{  50, 	ROMAN_L  , sizeof(ROMAN_L) - 1  },
												{  90, 	ROMAN_XC , sizeof(ROMAN_XC) - 1 },
												{ 100, 	ROMAN_C  , sizeof(ROMAN_C) - 1  },
												{ 400, 	ROMAN_CD , sizeof(ROMAN_CD) - 1 },
												{ 500, 	ROMAN_D  , sizeof(ROMAN_D) - 1  },
												{ 900, 	ROMAN_CM , sizeof(ROMAN_CM) - 1 },
												{1000, 	ROMAN_M  , sizeof(ROMAN_M) - 1  }	
											};

arabicRomanPair* lastArabicRomanLookupEntry = &arabic_roman_lookup[sizeof(roman_arabic_lookup) / 
                                                sizeof(arabicRomanPair) - 1];

#define romanNumeralComponentIsFound() strncmp(position_in_roman_numeral, pair->roman, pair->romanLength) == 0

int convertRomanToArabic(char* romanNumeral) {
	char* position_in_roman_numeral = romanNumeral;
	int accumulator = 0;

	while( strlen(position_in_roman_numeral) != 0 ) {
		arabicRomanPair* pair = roman_arabic_lookup;

		while( pair <= lastRomanArabicLookupEntry ) {
			if(romanNumeralComponentIsFound()) {
				accumulator += pair->arabic;
				break;
			}

			pair++;
		}
		
		position_in_roman_numeral += pair->romanLength;
	}

	return accumulator;
}

#define arabicValueNotDepleted() arabic_value > 0
#define exactMatchToArabicValue() pair->arabic == arabic_value
#define tableEntryExceedsArabicValue() pair->arabic > arabic_value
#define lastTableEntryIsLessOrEqualToArabicValue()  pair == lastArabicRomanLookupEntry && pair->arabic <= arabic_value
#define arabicValueAndTableEntriesRemain() pair <= lastArabicRomanLookupEntry && arabic_value > 0

char* convertArabicToRoman(int arabic_number, char *romanNumeral){
	int arabic_value = arabic_number;

	while(arabicValueNotDepleted()) {
		arabicRomanPair* pair = arabic_roman_lookup;

		do {
            if(lastTableEntryIsLessOrEqualToArabicValue()) {
				strcat(romanNumeral, pair->roman);
				arabic_value -= pair->arabic;
				break;
			}
	
			if(tableEntryExceedsArabicValue()) {
				strcat(romanNumeral, (pair - 1)->roman);
				arabic_value -= (pair - 1)->arabic;
				break;
			} 
            else if (exactMatchToArabicValue()) {
                strcat(romanNumeral, pair->roman);
                arabic_value -= pair->arabic;
                break;
            }

			pair++;
		} while(arabicValueAndTableEntriesRemain());
	}

	return romanNumeral; 
}