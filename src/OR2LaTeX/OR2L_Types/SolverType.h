#pragma once
#include <map>
#include <string>

namespace or2l {
enum class ORTSolverType { CBC, SCIP };

class SolverType {
 private:
  static std::map<ORTSolverType, std::string> types_;

 public:
  [[nodiscard]] inline static std::string GetType(
      const ORTSolverType ort_solver_type) {
    return types_.at(ort_solver_type);
  }
};
}  // namespace or2l