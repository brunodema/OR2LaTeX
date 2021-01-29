#pragma once
#include "Constraint.h"
#include "Index.h"
#include "RegexString.h"
#include "SolverType.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include "VariableSet.h"
#include "ortools/linear_solver/linear_solver.h"
#include <map>
#include <string>

using operations_research::MPSolver;

namespace or2l {

template <class T = MPSolver>
class Model {
 public:
  Model(const RegexString& name, std::initializer_list<Index> indexes,
        std::initializer_list<Variable> variables,
        std::initializer_list<Constraint> constraints);
  Model(const RegexString& name) : name_(name) {}
  virtual ~Model() = default;

  [[nodiscard]] SymbolComponent* Get(const RegexString& str) const;

  void RemoveSymbol(const RegexString& str);
  void AddVariable(const Variable& var);
  void RemoveVariable(const Variable& var);
  void ExtractIndexes(const Variable& var);
  void AddIndex(const Index& index);
  void RemoveIndex(const Index& index);
  void AddVariableSet(const VariableSet& var_set);
  void RemoveVariableSet(const VariableSet& var_set);
  void AddConstraint(const Constraint& constraint);
  void RemoveConstraint(const Constraint& constraint);

  inline void CreateModel() { CreateModelImpl(); };
  virtual void CreateModelImpl() = 0;
  // virtual void DestroyModel() = 0;
  // virtual const T* GetModel() = 0;

 private:
  RegexString name_ = "";
  std::map<RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
};


class ModelORTOOLS : public Model<MPSolver> {
 public:
  ModelORTOOLS(const RegexString& name, ORTSolverType type);

  void CreateModelImpl() override { return; }

 private:
  ORTSolverType type_ = ORTSolverType::CBC;
};

void lol() { std::unique_ptr<Model<MPSolver>> lol = std::make_unique<ModelORTOOLS>("LOL", ORTSolverType::CBC); }

}  // namespace or2l
