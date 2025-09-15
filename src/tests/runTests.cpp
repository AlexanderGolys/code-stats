#include "filesystemTests.hpp"
#include "isbell.hpp"

int main()
  {
	logging::Logger::init();
	UnitTestResult test_result, total_result;

	test_result = filesystemTests__all();
	total_result += test_result;
	printTestResult("Filesystem Tests", test_result);

	LOG("--------------------------------");
	printTestResult("All Tests", total_result);
  }
