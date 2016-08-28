#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "romancalctest.h"

int main() {
	int failed_test_count = 0;

	Suite* calculator_suite = CalculatorSuite();
	SRunner* runner = srunner_create(calculator_suite);

	srunner_run_all(runner, CK_VERBOSE);
	failed_test_count = srunner_ntests_failed(runner);
	srunner_free(runner);
	return failed_test_count;
}
