#pragma once
#include "NUMERIC_LIMITS.h"
#include "VARIABLE.h"
#include <unordered_map>
#include <utility>

namespace or2l {
class Expression {
 public:
  Expression(const double coeff = 0.00)
      : scalar_coefficient_(coeff), variable_map_() {}
  Expression(const VARIABLE& var) : variable_map_({{var, 1.00}}) {}
  virtual ~Expression() = default;

  Expression& operator+=(const Expression& expr) {
    for (auto&& var_coeff : expr.variable_map_) {
      this->variable_map_.at(var_coeff.first) += var_coeff.second;
    }
    this->scalar_coefficient_ += expr.scalar_coefficient_;
    return *this;
  }

  Expression& operator-=(const Expression& expr) {
    for (auto&& var_coeff : expr.variable_map_) {
      if (this->variable_map_.contains(var_coeff.first))
        this->variable_map_.at(var_coeff.first) -= var_coeff.second;
      else
        this->variable_map_.emplace(var_coeff.first, var_coeff.second);

      RemoveVariableIfZeroCoefficient(var_coeff.first);
    }
    this->scalar_coefficient_ -= expr.scalar_coefficient_;
    return *this;
  }

  Expression& operator+=(const double coeff) {
    this->scalar_coefficient_ += coeff;
    return *this;
  }

  Expression& operator-=(const double coeff) {
    this->scalar_coefficient_ -= coeff;
    return *this;
  }

  Expression& operator+=(const VARIABLE& var) {
    if (this->variable_map_.contains(var)) {
      ++this->variable_map_.at(var);
    } else {
      this->variable_map_.emplace(var, 1.00);
    }
    return *this;
  }

  Expression& operator-=(const VARIABLE& var) {
    if (this->variable_map_.contains(var)) {
      --this->variable_map_.at(var);
      RemoveVariableIfZeroCoefficient(var);
    } else {
      this->variable_map_.emplace(var, -1.00);
    }
    return *this;
  }

  Expression& operator*=(const double coeff) {
    for (auto& var_coeff : variable_map_) {
      var_coeff.second *= coeff;
    }
    this->scalar_coefficient_ *= coeff;
    return *this;
  }

  Expression& operator/=(const double coeff) {
    for (auto& var_coeff : variable_map_) {
      var_coeff.second /= coeff;
    }
    this->scalar_coefficient_ /= coeff;
    return *this;
  }

  Expression& operator+(const Expression& expr) {
    for (auto&& var_coeff : expr.variable_map_) {
      this->variable_map_.at(var_coeff.first) += var_coeff.second;
    }
    this->scalar_coefficient_ += expr.scalar_coefficient_;
    return *this;
  }

  Expression& operator-(const Expression& expr) {
    for (auto&& var_coeff : expr.variable_map_) {
      if (this->variable_map_.contains(var_coeff.first))
        this->variable_map_.at(var_coeff.first) -= var_coeff.second;
      else
        this->variable_map_.emplace(var_coeff.first, var_coeff.second);

      RemoveVariableIfZeroCoefficient(var_coeff.first);
    }
    this->scalar_coefficient_ -= expr.scalar_coefficient_;
    return *this;
  }

  Expression& operator+(const VARIABLE& var) {
    ++this->variable_map_.at(var);
    return *this;
  }

  Expression& operator-(const VARIABLE& var) {
    if (this->variable_map_.contains(var))
      --this->variable_map_.at(var);
    else
      this->variable_map_.emplace(var, -1.00);

    RemoveVariableIfZeroCoefficient(var);
    return *this;
  }

  friend Expression operator+(const VARIABLE& var1, const VARIABLE& var2);
  friend Expression operator-(const VARIABLE& var1, const VARIABLE& var2);
  friend Expression operator*(double coeff, const VARIABLE& var);
  friend Expression operator*(const VARIABLE& var, double coeff);
  friend Expression operator/(const VARIABLE& var, double coeff);
  friend Expression operator/(double coeff, const VARIABLE& var);

  double GetConstant() const { return scalar_coefficient_; }
  double GetCoefficient(const VARIABLE& var) const {
    return variable_map_.at(var);
  }
  void SetCoefficient(const VARIABLE& var, const double coeff) {
    variable_map_.at(var) = coeff;
  }
  bool ContainsVariable(const VARIABLE& var) const {
    return variable_map_.contains(var);
  }

 private:
  std::unordered_map<VARIABLE, double> variable_map_ = {};
  double scalar_coefficient_ = 0.00;

  void RemoveVariableIfZeroCoefficient(const VARIABLE& var) {
    if (IsNumericallyNull(this->GetCoefficient(var)))
      this->variable_map_.erase(var);
  }
};

Expression operator+(const VARIABLE& var1, const VARIABLE& var2) {
  Expression expr;
  expr += var1;
  expr += var2;
  return expr;
}

Expression operator-(const VARIABLE& var1, const VARIABLE& var2) {
  Expression expr;
  expr += var1;
  expr -= var2;
  return expr;
}

Expression operator*(const double coeff, const VARIABLE& var) {
  Expression expr;
  expr += var;
  expr.variable_map_.at(var) *= coeff;
  return expr;
}

Expression operator*(const VARIABLE& var, const double coeff) {
  Expression expr;
  expr += var;
  expr.variable_map_.at(var) *= coeff;
  return expr;
}

Expression operator/(const VARIABLE& var, const double coeff) {
  Expression expr;
  expr += var;
  expr.variable_map_.at(var) /= coeff;
  return expr;
}

Expression operator/(const double coeff, const VARIABLE& var) {
  Expression expr;
  expr += var;
  expr.variable_map_.at(var) *= pow(coeff, -1);
  return expr;
}
}  // namespace or2l