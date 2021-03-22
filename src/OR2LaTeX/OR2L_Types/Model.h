#pragma once
#include "Constraint.h"
#include "Index.h"
#include "RegexString.h"
#include "SolverType.h"
#include "SymbolComponent.h"
#include "SymbolType.h"
#include "Variable.h"
#include "ortools/linear_solver/linear_solver.h"
#include "solver_objects/Solver.h"
#include <cassert>
#include <map>
#include <string>
#include <vector>

namespace or2l
{
class Model
{
  public:
    Model(const base_types::RegexString &name, std::initializer_list<Index> indexes,
          std::initializer_list<Variable> variables, std::initializer_list<Constraint> constraints);
    Model(const base_types::RegexString &name) : name_(name)
    {
    }
    virtual ~Model() = default;

    // symbol
    [[nodiscard]] SymbolComponent *Get(const base_types::RegexString &str) const;
    void RemoveSymbol(const base_types::RegexString &str);
    void AddVariable(const Variable &var);
    void RemoveVariable(const Variable &var);
    void ExtractIndexes(const Variable &var);
    void AddIndex(const Index &index);
    void RemoveIndex(const Index &index);
    void AddConstraint(const Constraint &constraint);
    void RemoveConstraint(const Constraint &constraint);

    // solver objects (variables, constraints)
    [[nodiscard]] double GetVariable(const Variable &var, const std::vector<std::size_t> &index_values) const
    {
        return solver->GetVariable(var, index_values);
    }

    // solver
    inline void DefineSolver(const SolverType type)
    {
        solver = std::make_unique<OrtoolsSolver>(type);
    }
#ifdef GUROBI
    inline void DefineSolver(const GRBEnv &env)
    {
        solver_ = std::make_unique<GurobiSolver>(env);
    }
#endif // GUROBI
    inline void ImplementModel()
    {
        if (solver == nullptr)
            throw or2l::Exception(ExceptionType::ERR_MODEL_NULLPTRSOLVER);

        for (const auto &[name, symbol] : symbol_map_)
        {
            switch (symbol->GetType())
            {
            case SymbolType::VARIABLE:
                solver->AddVariableSet(*static_cast<Variable *>(symbol.get()));
                break;
            }
        }
    }
    inline const ISolver *GetSolver()
    {
        return solver.get();
    };
    inline void FreeSolver()
    {
        solver.reset();
    };

  protected:
    base_types::RegexString name_ = "";
    std::unique_ptr<ISolver> solver;
    std::map<base_types::RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
}; // namespace or2l
} // namespace or2l