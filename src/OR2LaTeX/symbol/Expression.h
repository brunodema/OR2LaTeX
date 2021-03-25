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
using base_types::Bounds;

struct ExpressionCoefficient
{
  public:
    ExpressionCoefficient() = default;
    ExpressionCoefficient(const Variable &_var) : variable(_var), coefficient(1.00){};
    ExpressionCoefficient(const double _coefficient, const Variable &_var)
        : variable(_var), coefficient(_coefficient){};
    ExpressionCoefficient(const double &_value) : coefficient(_value){};

    bool operator==(const ExpressionCoefficient &_other) const
    {
        return this->variable == _other.variable && this->coefficient == _other.coefficient;
    }
    template <typename H> friend H AbslHashValue(H _h, const ExpressionCoefficient &_exprcoeff);

    Variable variable = {};
    double coefficient = 0.00;
};

template <typename H> H AbslHashValue(H _h, const or2l::ExpressionCoefficient &_exprcoeff)
{
    return H::combine(std::move(_h), _exprcoeff.variable, _exprcoeff.coefficient);
}

class InnerExpression
{
  public:
    InnerExpression() = default;
    InnerExpression(const ExpressionCoefficient &_exprcoeff)
    {
        coefficient_map.at(_exprcoeff.variable) = _exprcoeff.coefficient;
    }

    friend InnerExpression operator+(const ExpressionCoefficient &_a, const ExpressionCoefficient &_b);

    double operator[](const Variable &_var) const
    {
        return coefficient_map.at(_var);
    }

  private:
    std::unordered_map<Variable, double, absl::Hash<Variable>> coefficient_map = {};
};

inline InnerExpression operator+(const ExpressionCoefficient &_a, const ExpressionCoefficient &_b)
{
    InnerExpression ret;
    if (_a.variable == _b.variable)
    {
        ret.coefficient_map[_a.variable] = _a.coefficient + _b.coefficient;
        return ret;
    }
    ret.coefficient_map[_a.variable] = _a.coefficient;
    ret.coefficient_map[_b.variable] = _b.coefficient;
    return ret;
}

// namespace operators // should include all other operators in the future
// {
// enum class ExpressionOperatorType
// {
//     SCALAR,
//     SUMMATION
// };
// class ExpressionOperator
// {
//   public:
//     // implement custom rules for bounds in the future
//     ExpressionOperator() = default;
//     ExpressionOperator(const ExpressionOperatorType _type, InnerExpression _expr,
//                        const std::initializer_list<Index> _indexes)
//         : type(_type), inner_expression(std::move(_expr)), indexes(_indexes){};

//     bool IsValid() const
//     {
//     }

//     operators::ExpressionOperatorType GetType() const
//     {
//         return type;
//     }
//     InnerExpression GetExpression() const
//     {
//         return inner_expression;
//     }
//     std::vector<Index> GetIndexes() const
//     {
//         return indexes;
//     }

//   private:
//     operators::ExpressionOperatorType type = operators::ExpressionOperatorType::SCALAR;
//     InnerExpression inner_expression = {};
//     std::vector<Index> indexes = {};
// };
//} // namespace or2l

// -----------------------------------------------------------------

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