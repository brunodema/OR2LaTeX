#pragma once
#include "CONSTRAINT.h"
#include "INDEX.h"
#include "REGEX_STRING.h"
#include "SYMBOL_COMPONENT.h"
#include "VARIABLE.h"
#include "VARIABLE_SET.h"
#include <map>
#include <string>

namespace or2l {
class MODEL {
 public:
  MODEL(const REGEX_STRING& name, const std::initializer_list<INDEX> indexes,
        const std::initializer_list<VARIABLE> variables,
        const std::initializer_list<CONSTRAINT> constraints)
      : name_(name) {
    for (auto&& index : indexes) {
      symbol_map_.insert_or_assign(index.GetName(),
                                   std::make_unique<INDEX>(index));
    }
    for (auto&& variable : variables) {
      symbol_map_.insert_or_assign(variable.GetName(),
                                   std::make_unique<VARIABLE>(variable));
    }
    for (auto&& constraint : constraints) {
      symbol_map_.insert_or_assign(constraint.GetName(),
                                   std::make_unique<CONSTRAINT>(constraint));
    }
  }

  explicit MODEL(const REGEX_STRING& name) : name_(name) {}
  virtual ~MODEL() = default;

  [[nodiscard]] SYMBOL_COMPONENT* Get(const REGEX_STRING& str) const {
    // SYMBOL_TYPE type = symbol_map_.at(str).get()->GetType();
    switch (const SYMBOL_TYPE type = symbol_map_.at(str).get()->GetType()) {
      case SYMBOL_TYPE::INDEX:
        return static_cast<INDEX*>(symbol_map_.at(str).get());
        break;

      case SYMBOL_TYPE::VARIABLE:
        return static_cast<VARIABLE*>(symbol_map_.at(str).get());
        break;

      case SYMBOL_TYPE::VARIABLE_SET:
        return static_cast<VARIABLE_SET*>(symbol_map_.at(str).get());
        break;

      case SYMBOL_TYPE::CONSTRAINT:
        return static_cast<CONSTRAINT*>(symbol_map_.at(str).get());
        break;

      default:
        throw OR2LEXCEPTION();
    }
  }

  void Remove(const REGEX_STRING& str) { symbol_map_.erase(str); }

  void AddVariable(const VARIABLE& var) {
    symbol_map_.insert_or_assign(var.GetName(),
                                 std::make_unique<VARIABLE>(var));
  }

  void RemoveVariable(const VARIABLE& var) { symbol_map_.erase(var.GetName()); }

  void ExtractIndexes(const VARIABLE& var) {
    for (auto&& index : var.GetIndexes()) {
      symbol_map_.insert_or_assign(index.GetName(),
                                   std::make_unique<INDEX>(index));
    }
  }

  void AddIndex(const INDEX& index) {
    symbol_map_.insert_or_assign(index.GetName(),
                                 std::make_unique<INDEX>(index));
  }

  void RemoveIndex(const INDEX& index) { symbol_map_.erase(index.GetName()); }

  void AddVariableSet(const VARIABLE_SET& var_set) {
    symbol_map_.insert_or_assign(var_set.GetName(),
                                 std::make_unique<VARIABLE_SET>(var_set));
  }

  void RemoveVariableSet(const VARIABLE_SET& var_set) {
    symbol_map_.erase(var_set.GetName());
  }

  void AddConstraint(const CONSTRAINT& constraint) {
    symbol_map_.insert_or_assign(constraint.GetName(),
                                 std::make_unique<CONSTRAINT>(constraint));
  }

  void RemoveConstraint(const CONSTRAINT& constraint) {
    symbol_map_.erase(constraint.GetName());
  }

 private:
  REGEX_STRING name_ = "";
  std::map<REGEX_STRING, std::unique_ptr<SYMBOL_COMPONENT>> symbol_map_ = {};
};
}  // namespace or2l