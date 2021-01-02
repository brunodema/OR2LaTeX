#pragma once
#include <cassert>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>

#define ASSERT_THROW(STATEMENT, EXCEPTION_TYPE) \
  try {                                         \
    STATEMENT;                                  \
    throw;                                      \
  } catch (const EXCEPTION_TYPE& e) {           \
  }
#define ASSERT_THROW_ALL(STATEMENT) \
  try {                             \
    STATEMENT;                      \
    throw;                          \
  } catch (...) {                   \
  }

namespace or2l::base_types {
class ModuleTester : std::vector<std::function<void()>> {
 public:
  static std::vector<std::function<void()>> tests_;

  static int Run() {
    std::cout << tests_.size() << " tests detected.\n";
    for (auto& test : tests_) {
      test();
      std::cout << "test executed.\n";
    }
    return 0;
  }
};
}  // namespace or2l::base_types
