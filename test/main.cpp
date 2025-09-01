#include "strutiltests.h"
#include "iotests.h"

#include <test/cbtest.h>

int main() {
	strutiltests::addTestCases();
	iotests::addTestCases();

	RUN_TEST_CASES_MENU();
}
