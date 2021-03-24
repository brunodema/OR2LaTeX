#pragma once
#include "auxiliary/Auxiliary.h"
#include "symbol/Variable.h"
#include <unordered_map>
#include <utility>

namespace or2l
{
class Expression
{
  public:
    Expression(const double _coeff = 0.00) : scalar_coefficient(_coeff)
    {
    }
    Expression(const Variable &_var) : variable_map({{_var, 1.00}})
    {
    }
    virtual ~Expression() = default;

    Expression &operator+=(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.variable_map)
        {
            this->variable_map.at(var_coeff.first) += var_coeff.second;
        }
        this->scalar_coefficient += _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator-=(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.variable_map)
        {
            if (this->variable_map.find(var_coeff.first) != this->variable_map.end())
                this->variable_map.at(var_coeff.first) -= var_coeff.second;
            else
                this->variable_map.emplace(var_coeff.first, var_coeff.second);

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
        if (this->variable_map.find(_var) != this->variable_map.end())
        {
            ++this->variable_map.at(_var);
        }
        else
        {
            this->variable_map.emplace(_var, 1.00);
        }
        return *this;
    }

    Expression &operator-=(const Variable &_var)
    {
        if (this->variable_map.find(_var) != this->variable_map.end())
        {
            --this->variable_map.at(_var);
            RemoveVariableIfZeroCoefficient(_var);
        }
        else
        {
            this->variable_map.emplace(_var, -1.00);
        }
        return *this;
    }

    Expression &operator*=(const double _coeff)
    {
        for (auto &var_coeff : variable_map)
        {
            var_coeff.second *= _coeff;
        }
        this->scalar_coefficient *= _coeff;
        return *this;
    }

    Expression &operator/=(const double _coeff)
    {
        for (auto &var_coeff : variable_map)
        {
            var_coeff.second /= _coeff;
        }
        this->scalar_coefficient /= _coeff;
        return *this;
    }

    Expression &operator+(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.variable_map)
        {
            this->variable_map.at(var_coeff.first) += var_coeff.second;
        }
        this->scalar_coefficient += _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator-(const Expression &_expr)
    {
        for (auto &&var_coeff : _expr.variable_map)
        {
            if (this->variable_map.find(var_coeff.first) != this->variable_map.end())
                this->variable_map.at(var_coeff.first) -= var_coeff.second;
            else
                this->variable_map.emplace(var_coeff.first, var_coeff.second);

            RemoveVariableIfZeroCoefficient(var_coeff.first);
        }
        this->scalar_coefficient -= _expr.scalar_coefficient;
        return *this;
    }

    Expression &operator+(const Variable &_var)
    {
        ++this->variable_map.at(_var);
        return *this;
    }

    Expression &operator-(const Variable &_var)
    {
        if (this->variable_map.find(_var) != this->variable_map.end())
            --this->variable_map.at(_var);
        else
            this->variable_map.emplace(_var, -1.00);

        RemoveVariableIfZeroCoefficient(_var);
        return *this;
    }

    friend Expression operator+(const Variable &_var1, const Variable &_var2);
    friend Expression operator+(const Variable &_var1, double _coeff);
    friend Expression operator+(double _coeff, const Variable &_var);
    friend Expression operator-(const Variable &_var1, const Variable &_var2);
    friend Expression operator-(const Variable &_var, double _coeff);
    friend Expression operator-(double _coeff, const Variable &_var);
    friend Expression operator*(double _coeff, const Variable &_var);
    friend Expression operator*(const Variable &_var, double _coeff);
    friend Expression operator/(const Variable &_var, double _coeff);
    friend Expression operator/(double _coeff, const Variable &_var);

    double GetConstant() const
    {
        return scalar_coefficient;
    }
    double GetCoefficient(const Variable &_var) const
    {
        return variable_map.at(_var);
    }
    void SetCoefficient(const Variable &_var, const double _coeff)
    {
        variable_map.at(_var) = _coeff;
    }
    bool ContainsVariable(const Variable &_var) const
    {
        return variable_map.find(_var) != this->variable_map.end();
    }

  private:
    std::unordered_map<Variable, double> variable_map = {};
    double scalar_coefficient = 0.00;

    void RemoveVariableIfZeroCoefficient(const Variable &_var)
    {
        if (IsNumericallyNull(this->GetCoefficient(_var)))
            this->variable_map.erase(_var);
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
    expr.variable_map.at(_var) *= _coeff;
    return expr;
}

inline Expression operator*(const Variable &_var, const double _coeff)
{
    Expression expr;
    expr += _var;
    expr.variable_map.at(_var) *= _coeff;
    return expr;
}

inline Expression operator/(const Variable &_var, const double _coeff)
{
    Expression expr;
    expr += _var;
    expr.variable_map.at(_var) /= _coeff;
    return expr;
}

inline Expression operator/(const double _coeff, const Variable &_var)
{
    Expression expr;
    expr += _var;
    expr.variable_map.at(_var) *= pow(_coeff, -1);
    return expr;
}
} // namespace or2l