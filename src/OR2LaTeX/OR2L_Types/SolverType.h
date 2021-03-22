#pragma once
#include <map>
#include <string>

namespace or2l
{
enum class SolverType
{
    ORTOOLS_CBC,
    ORTOOLS_SCIP,
    OR2L_GUROBI
};

static const int SOLVERTYPE_ORTOOLS_MAX = static_cast<int>(SolverType::ORTOOLS_SCIP);

class SolverTypeDictionary
{
  private:
    static std::map<SolverType, std::string> types;

  public:
    [[nodiscard]] inline static std::string GetType(const SolverType ort_solver_type)
    {
        return types.at(ort_solver_type);
    }
};
} // namespace or2l