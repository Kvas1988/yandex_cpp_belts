#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

void TestLoop() {
    ostringstream output;
    for (size_t i = 0; i < 5; i++)
        PRINT_VALUES(output, 4, "CppRef");

    ASSERT_EQUAL(output.str(), "4\nCppRef\n4\nCppRef\n4\nCppRef\n4\nCppRef\n4\nCppRef\n");
}

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");

  RUN_TEST(tr, TestLoop);
}
