#include "ModuleTester.h"
#include <string_view>

namespace or2l::base_types {
int ModuleTester::Run() {
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
}  // namespace or2l::base_types
