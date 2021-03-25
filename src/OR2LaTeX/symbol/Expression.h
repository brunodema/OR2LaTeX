#pragma once
#include "Bounds.h"
#include "auxiliary/Auxiliary.h"
#include "auxiliary/Exception.h"
#include "symbol/Variable.h"
#include <absl/hash/hash.h>
#include <initializer_list>
#include <unordered_map>
#include <utility>
#include <vector>

namespace or2l
{
class Expression
{
  public:
    Expression(const double _coeff = 0.00) : scalar_coefficient(_coeff)
    {
    }
    Expression(const Variable &_var) : coefficient_map({{_var, 1.00}})
    {
    }
    virtual ~Expression() = default;

    Expression &operator+=(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.coefficient_map)
        {
            this->coefficient_map.at(var_coeff.first) += var_coeff.second;
        }
        this->scalar_coefficient += _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator-=(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.coefficient_map)
        {
            if (this->coefficient_map.find(var_coeff.first) != this->coefficient_map.end())
                this->coefficient_map.at(var_coeff.first) -= var_coeff.second;
            else
                this->coefficient_map.emplace(var_coeff.first, var_coeff.second);

            RemoveVariableIfZeroCoefficient(var_coeff.first);
        }
        this->scalar_coefficient -= _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator+=(const double _coeff)
    {
        this->scalar_coefficient += _coeff;
        return *this;
    }

    Expression &operator-=(const double _coeff)
    {
        this->scalar_coefficient -= _coeff;
        return *this;
    }

    Expression &operator+=(const Variable &_var)
    {
        if (this->coefficient_map.find(_var) != this->coefficient_map.end())
        {
            ++this->coefficient_map.at(_var);
        }
        else
        {
            this->coefficient_map.emplace(_var, 1.00);
        }
        return *this;
    }

    Expression &operator-=(const Variable &_var)
    {
        if (this->coefficient_map.find(_var) != this->coefficient_map.end())
        {
            --this->coefficient_map.at(_var);
            RemoveVariableIfZeroCoefficient(_var);
        }
        else
        {
            this->coefficient_map.emplace(_var, -1.00);
        }
        return *this;
    }

    Expression &operator*=(const double _coeff)
    {
        for (auto &var_coeff : coefficient_map)
        {
            var_coeff.second *= _coeff;
        }
        this->scalar_coefficient *= _coeff;
        return *this;
    }

    Expression &operator/=(const double _coeff)
    {
        for (auto &var_coeff : coefficient_map)
        {
            var_coeff.second /= _coeff;
        }
        this->scalar_coefficient /= _coeff;
        return *this;
    }

    Expression &operator+(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.coefficient_map)
        {
            this->coefficient_map.at(var_coeff.first) += var_coeff.second;
        }
        this->scalar_coefficient += _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator-(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.coefficient_map)
        {
            if (this->coefficient_map.find(var_coeff.first) != this->coefficient_map.end())
                this->coefficient_map.at(var_coeff.first) -= var_coeff.second;
            else
                this->coefficient_map.emplace(var_coeff.first, var_coeff.second);

            RemoveVariableIfZeroCoefficient(var_coeff.first);
        }
        this->scalar_coefficient -= _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator+(const Variable &_var)
    {
        ++this->coefficient_map.at(_var);
        return *this;
    }

    Expression &operator-(const Variable &_var)
    {
        if (this->coefficient_map.find(_var) != this->coefficient_map.end())
            --this->coefficient_map.at(_var);
        else
            this->coefficient_map.emplace(_var, -1.00);

        RemoveVariableIfZeroCoefficient(_var);
        return *this;
    }

    // cross-variable sum/subtraction
    friend Expression operator+(const Variable &_var1, const Variable &_var2);
    friend Expression operator-(const Variable &_var1, const Variable &_var2);
    // variable-coefficient sum/subtraction
    friend Expression operator+(const Variable &_var, double _coeff);
    friend Expression operator-(const Variable &_var, double _coeff);
    friend Expression operator+(double _coeff, const Variable &_var);
    friend Expression operator-(double _coeff, const Variable &_var);
    // variable-coefficient multiplication
    friend Expression operator*(double _coeff, const Variable &_var);
    friend Expression operator*(const Variable &_var, double _coeff);
    // variable-coefficient division
    friend Expression operator/(const Variable &_var, double _coeff);
    friend Expression operator/(double _coeff, const Variable &_var);

    double GetConstant() const
    {
        return scalar_coefficient;
    }
    double GetCoefficient(const Variable &_var) const
    {
        return coefficient_map.at(_var);
    }
    void SetCoefficient(const Variable &_var, const double _coeff)
    {
        coefficient_map.at(_var) = _coeff;
    }
    bool ContainsVariable(const Variable &_var) const
    {
        return coefficient_map.find(_var) != this->coefficient_map.end();
    }

  private:
    std::unordered_map<Variable, double, absl::Hash<Variable>> coefficient_map = {};
    double scalar_coefficient = 0.00;

    void RemoveVariableIfZeroCoefficient(const Variable &_var)
    {
        if (IsNumericallyNull(this->GetCoefficient(_var)))
            this->coefficient_map.erase(_var);
    }
};

inline Expression operator+(const Variable &_var1, const Variable &_var2)
{
    Expression expr;
    expr += _var1;
    expr += _var2;
    return expr;
}

inline Expression operator+(const Variable &_var, const double _coeff)
{
    Expression expr;
    expr += _var;
    expr += _coeff;
    return expr;
};

inline Expression operator+(const double _coeff, const Variable &_var)
{
    Expression expr;
    expr += _coeff;
    expr += _var;
    return expr;
};

inline Expression operator-(const Variable &_var1, const Variable &_var2)
{
    Expression expr;
    expr += _var1;
    expr -= _var2;
    return expr;
}

inline Expression operator-(const Variable &_var, const double _coeff)
{
    Expression expr;
    expr += _var;
    expr -= _coeff;
    return expr;
}
inline Expression operator-(const double _coeff, const Variable &_var)
{
    Expression expr;
    expr += _coeff;
    expr -= _var;
    return expr;
}

inline Expression operator*(const double _coeff, const Variable &_var)
{
    Expression expr;
    expr += _var;
    expr.coefficient_map.at(_var) *= _coeff;
    return expr;
}

inline Expression operator*(const Variable &_var, const double _coeff)
{
    Expression expr;
    expr += _var;
    expr.coefficient_map.at(_var) *= _coeff;
    return expr;
}

inline Expression operator/(const Variable &_var, const double _coeff)
{
    Expression expr;
    expr += _var;
    expr.coefficient_map.at(_var) /= _coeff;
    return expr;
}

inline Expression operator/(const double _coeff, const Variable &_var)
{
    Expression expr;
    expr += _var;
    expr.coefficient_map.at(_var) *= pow(_coeff, -1);
    return expr;
}
} // namespace or2l