/*
This module tests whether your device is compatable with the program.
*/

#include "test.h"

namespace procserver_test {

TEST(procinfo, test_1plus1) {
  // Google Test will also provide macros for assertions.
  ASSERT_EQ(1+1, 2);
}

TEST(procinfo, test_1plus0) {
  // Google Test will also provide macros for assertions.
  ASSERT_EQ(1+0, 1);
}

}  // namespace procserver_test
