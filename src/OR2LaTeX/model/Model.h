#pragma once
#include "RegexString.h"
#include "ortools/linear_solver/linear_solver.h"
#include "solver/Solver.h"
#include "solver/SolverType.h"
#include "symbol/Constraint.h"
#include "symbol/Index.h"
#include "symbol/SymbolComponent.h"
#include "symbol/Variable.h"
#include <cassert>
#include <map>
#include <string>
#include <vector>

namespace or2l
{
class Model
{
  public:
    Model(const base_types::RegexString &_name, std::initializer_list<Index> _indexes,
          std::initializer_list<Variable> _variables, std::initializer_list<Constraint> _constraints);
    Model(const base_types::RegexString &_name) : name_(_name)
    {
    }
    virtual ~Model() = default;

    // symbol
    [[nodiscard]] SymbolComponent *Get(const base_types::RegexString &_str) const;
    void RemoveSymbol(const base_types::RegexString &_str);
    void AddVariable(const Variable &_var);
    void RemoveVariable(const Variable &_var);
    void MapIndexesFromVariable(const Variable &_var);
    void AddIndex(const Index &_index);
    void RemoveIndex(const Index &_index);
    void AddConstraint(const Constraint &_constraint);
    void RemoveConstraint(const Constraint &_constraint);

    // solver objects (variables, constraints)
    [[nodiscard]] double GetVariable(const Variable &_var, const std::vector<std::size_t> &_index_values) const
    {
        return solver->GetVariable(_var, _index_values);
    }

    // solver
    inline void DefineSolver(const SolverType _type)
    {
        solver = std::make_unique<OrtoolsSolver>(_type);
    }
#ifdef GUROBI
    inline void DefineSolver(const GRBEnv &env)
    {
        solver = std::make_unique<GurobiSolver>(env);
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