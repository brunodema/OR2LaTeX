#pragma once
#include "NumericLimits.h"
#include "Variable.h"
#include <unordered_map>
#include <utility>

namespace or2l
{
class Expression
{
  public:
    Expression(const double coeff = 0.00) : scalar_coefficient(coeff)
    {
    }
    Expression(const Variable &var) : variable_map({{var, 1.00}})
    {
    }
    virtual ~Expression() = default;

    Expression &operator+=(const Expression &expr)
    {
        for (auto &&var_coeff : expr.variable_map)
        {
            this->variable_map.at(var_coeff.first) += var_coeff.second;
        }
        this->scalar_coefficient += expr.scalar_coefficient;
        return *this;
    }

    Expression &operator-=(const Expression &expr)
    {
        for (auto &&var_coeff : expr.variable_map)
        {
            if (this->variable_map.find(var_coeff.first) != this->variable_map.end())
                this->variable_map.at(var_coeff.first) -= var_coeff.second;
            else
                this->variable_map.emplace(var_coeff.first, var_coeff.second);

            RemoveVariableIfZeroCoefficient(var_coeff.first);
        }
        this->scalar_coefficient -= expr.scalar_coefficient;
        return *this;
    }

    Expression &operator+=(const double coeff)
    {
        this->scalar_coefficient += coeff;
        return *this;
    }

    Expression &operator-=(const double coeff)
    {
        this->scalar_coefficient -= coeff;
        return *this;
    }

    Expression &operator+=(const Variable &var)
    {
        if (this->variable_map.find(var) != this->variable_map.end())
        {
            ++this->variable_map.at(var);
        }
        else
        {
            this->variable_map.emplace(var, 1.00);
        }
        return *this;
    }

    Expression &operator-=(const Variable &var)
    {
        if (this->variable_map.find(var) != this->variable_map.end())
        {
            --this->variable_map.at(var);
            RemoveVariableIfZeroCoefficient(var);
        }
        else
        {
            this->variable_map.emplace(var, -1.00);
        }
        return *this;
    }

    Expression &operator*=(const double coeff)
    {
        for (auto &var_coeff : variable_map)
        {
            var_coeff.second *= coeff;
        }
        this->scalar_coefficient *= coeff;
        return *this;
    }

    Expression &operator/=(const double coeff)
    {
        for (auto &var_coeff : variable_map)
        {
            var_coeff.second /= coeff;
        }
        this->scalar_coefficient /= coeff;
        return *this;
    }

    Expression &operator+(const Expression &expr)
    {
        for (auto &&var_coeff : expr.variable_map)
        {
            this->variable_map.at(var_coeff.first) += var_coeff.second;
        }
        this->scalar_coefficient += expr.scalar_coefficient;
        return *this;
    }

    Expression &operator-(const Expression &expr)
    {
        for (auto &&var_coeff : expr.variable_map)
        {
            if (this->variable_map.find(var_coeff.first) != this->variable_map.end())
                this->variable_map.at(var_coeff.first) -= var_coeff.second;
            else
                this->variable_map.emplace(var_coeff.first, var_coeff.second);

            RemoveVariableIfZeroCoefficient(var_coeff.first);
        }
        this->scalar_coefficient -= expr.scalar_coefficient;
        return *this;
    }

    Expression &operator+(const Variable &var)
    {
        ++this->variable_map.at(var);
        return *this;
    }

    Expression &operator-(const Variable &var)
    {
        if (this->variable_map.find(var) != this->variable_map.end())
            --this->variable_map.at(var);
        else
            this->variable_map.emplace(var, -1.00);

        RemoveVariableIfZeroCoefficient(var);
        return *this;
    }

    friend Expression operator+(const Variable &var1, const Variable &var2);
    friend Expression operator+(const Variable &var1, double coeff);
    friend Expression operator+(double coeff, const Variable &var);
    friend Expression operator-(const Variable &var1, const Variable &var2);
    friend Expression operator-(const Variable &var, double coeff);
    friend Expression operator-(double coeff, const Variable &var);
    friend Expression operator*(double coeff, const Variable &var);
    friend Expression operator*(const Variable &var, double coeff);
    friend Expression operator/(const Variable &var, double coeff);
    friend Expression operator/(double coeff, const Variable &var);

    double GetConstant() const
    {
        return scalar_coefficient;
    }
    double GetCoefficient(const Variable &var) const
    {
        return variable_map.at(var);
    }
    void SetCoefficient(const Variable &var, const double coeff)
    {
        variable_map.at(var) = coeff;
    }
    bool ContainsVariable(const Variable &var) const
    {
        return variable_map.find(var) != this->variable_map.end();
    }

  private:
    std::unordered_map<Variable, double> variable_map = {};
    double scalar_coefficient = 0.00;

    void RemoveVariableIfZeroCoefficient(const Variable &var)
    {
        if (IsNumericallyNull(this->GetCoefficient(var)))
            this->variable_map.erase(var);
    }
};

inline Expression operator+(const Variable &var1, const Variable &var2)
{
    Expression expr;
    expr += var1;
    expr += var2;
    return expr;
}

inline Expression operator+(const Variable &var, const double coeff)
{
    Expression expr;
    expr += var;
    expr += coeff;
    return expr;
};

inline Expression operator+(const double coeff, const Variable &var)
{
    Expression expr;
    expr += coeff;
    expr += var;
    return expr;
};

inline Expression operator-(const Variable &var1, const Variable &var2)
{
    Expression expr;
    expr += var1;
    expr -= var2;
    return expr;
}

inline Expression operator-(const Variable &var, const double coeff)
{
    Expression expr;
    expr += var;
    expr -= coeff;
    return expr;
}
inline Expression operator-(const double coeff, const Variable &var)
{
    Expression expr;
    expr += coeff;
    expr -= var;
    return expr;
}

inline Expression operator*(const double coeff, const Variable &var)
{
    Expression expr;
    expr += var;
    expr.variable_map.at(var) *= coeff;
    return expr;
}

inline Expression operator*(const Variable &var, const double coeff)
{
    Expression expr;
    expr += var;
    expr.variable_map.at(var) *= coeff;
    return expr;
}

inline Expression operator/(const Variable &var, const double coeff)
{
    Expression expr;
    expr += var;
    expr.variable_map.at(var) /= coeff;
    return expr;
}

inline Expression operator/(const double coeff, const Variable &var)
{
    Expression expr;
    expr += var;
    expr.variable_map.at(var) *= pow(coeff, -1);
    return expr;
}
} // namespace or2l