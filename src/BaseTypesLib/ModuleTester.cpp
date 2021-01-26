#include "ModuleTester.h"
#include <string_view>

namespace or2l::base_types {
int ModuleTester::Run() {
  std::cout << tests_.size() << " tests detected.\n";
  auto tests_passed = 0;
  auto tests_failed = 0;

  for (auto& test : tests_) {
    try {
      test();
      std::cout << "test executed.\n";
      ++tests_passed;
    } catch (const std::exception& e) {
      const std::string_view what(e.what());
      std::cout << "test failed. (" << what << ")\n";
      ++tests_failed;
    }
  }

  std::cout << "total of successful tests: " << tests_passed << "/"
            << tests_.size() << ".\n";

  if (tests_failed) {
    return 1;
  }
  return 0;
}
}  // namespace or2l::base_types
