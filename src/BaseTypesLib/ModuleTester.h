#pragma once
#include <cassert>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>

#define ASSERT_THROW(STATEMENT, ExceptionType) \
  try {                                        \
    STATEMENT;                                 \
    throw;                                     \
  } catch (const ExceptionType& e) {           \
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
    auto tests_executed = 0;
    try {
      for (auto& test : tests_) {
        test();
        std::cout << "test executed.\n";
        ++tests_executed;
      }
    } catch (const std::exception& e) {
      const std::string_view what(e.what());
      std::cout << "test failed. (" << what << ")\n";
    }
    std::cout << "total of successful tests: " << tests_executed << "/"
              << tests_.size() << ".\n";
    return 0;
  }
};
}  // namespace or2l::base_types
