#pragma once
#include <unordered_map>
#include <utility>
#include "VARIABLE.h"
#include "NUMERIC_LIMITS.h"

namespace OR2L
{
    class EXPRESSION
    {
    public:
        EXPRESSION(const double coeff = 0.00) : scalar_coefficient_(coeff), variable_map_() {}
        EXPRESSION(const VARIABLE var) : scalar_coefficient_(), variable_map_({ {var, 1.00} }) {}

        EXPRESSION(const EXPRESSION&) = default;
        EXPRESSION(EXPRESSION&&) = default;
        virtual EXPRESSION& operator=(const EXPRESSION&) = default;
        virtual EXPRESSION& operator=(EXPRESSION&&) = default;
        virtual ~EXPRESSION() = default;

        EXPRESSION& operator+=(const EXPRESSION& expr)
        {
            for (auto&& var_coeff : expr.variable_map_)
            {
                this->variable_map_.at(var_coeff.first) += var_coeff.second;
            }
            this->scalar_coefficient_ += expr.scalar_coefficient_;
            return *this;
        }

        EXPRESSION& operator-=(const EXPRESSION& expr)
        {
            for (auto&& var_coeff : expr.variable_map_)
            {
                if (this->variable_map_.contains(var_coeff.first))
                    this->variable_map_.at(var_coeff.first) -= var_coeff.second;
                else
                    this->variable_map_.emplace(var_coeff.first, var_coeff.second);

                RemoveVariableIfZeroCoefficient(var_coeff.first);
            }
            this->scalar_coefficient_ -= expr.scalar_coefficient_;
            return *this;
        }

        EXPRESSION& operator+=(const double coeff)
        {
            this->scalar_coefficient_ += coeff;
            return *this;
        }

        EXPRESSION& operator-=(const double coeff)
        {
            this->scalar_coefficient_ -= coeff;
            return *this;
        }

        EXPRESSION& operator+=(const VARIABLE& var)
        {
            if (this->variable_map_.contains(var))
            {
                ++this->variable_map_.at(var);
            }
            else
            {
                this->variable_map_.emplace(var, 1.00);
            }
            return *this;
        }

        EXPRESSION& operator-=(const VARIABLE& var)
        {
            if (this->variable_map_.contains(var))
            {
                --this->variable_map_.at(var);
                RemoveVariableIfZeroCoefficient(var);
            }
            else
            {
                this->variable_map_.emplace(var, -1.00);
            }
            return *this;
        }

        EXPRESSION& operator*=(const double coeff)
        {
            for (auto& var_coeff : variable_map_)
            {
                var_coeff.second *= coeff;
            }
            this->scalar_coefficient_ *= coeff;
            return *this;
        }

        EXPRESSION& operator/=(const double coeff)
        {
            for (auto& var_coeff : variable_map_)
            {
                var_coeff.second /= coeff;
            }
            this->scalar_coefficient_ /= coeff;
            return *this;
        }

        EXPRESSION& operator+(const EXPRESSION& expr)
        {
            for (auto&& var_coeff : expr.variable_map_)
            {
                this->variable_map_.at(var_coeff.first) += var_coeff.second;
            }
            this->scalar_coefficient_ += expr.scalar_coefficient_;
            return *this;
        }

        EXPRESSION& operator-(const EXPRESSION& expr)
        {
            for (auto&& var_coeff : expr.variable_map_)
            {
                if (this->variable_map_.contains(var_coeff.first))
                    this->variable_map_.at(var_coeff.first) -= var_coeff.second;
                else
                    this->variable_map_.emplace(var_coeff.first, var_coeff.second);

                RemoveVariableIfZeroCoefficient(var_coeff.first);
            }
            this->scalar_coefficient_ -= expr.scalar_coefficient_;
            return *this;
        }

        EXPRESSION& operator+(const VARIABLE& var)
        {
            ++this->variable_map_.at(var);
            return *this;
        }

        EXPRESSION& operator-(const VARIABLE& var)
        {
            if (this->variable_map_.contains(var))
                --this->variable_map_.at(var);
            else
                this->variable_map_.emplace(var, -1.00);

            RemoveVariableIfZeroCoefficient(var);
            return *this;
        }

        friend EXPRESSION operator+(const VARIABLE& var1, const VARIABLE& var2);
        friend EXPRESSION operator-(const VARIABLE& var1, const VARIABLE& var2);
        friend EXPRESSION operator*(const double coeff, const VARIABLE& var);
        friend EXPRESSION operator*(const VARIABLE& var, const double coeff);
        friend EXPRESSION operator/(const VARIABLE& var, const double coeff);
        //friend EXPRESSION operator/(const double coeff, const VARIABLE& var);

        double GetConstant() const { return scalar_coefficient_; }
        double GetCoefficient(const VARIABLE& var) const { return variable_map_.at(var); }
        void SetCoefficient(const VARIABLE& var, const double coeff) { variable_map_.at(var) = coeff; }
        bool ContainsVariable(const VARIABLE& var) const { return variable_map_.contains(var); }

    private:
        std::unordered_map<VARIABLE, double> variable_map_ = {};
        double scalar_coefficient_ = 0.00;

        void RemoveVariableIfZeroCoefficient(const VARIABLE& var)
        {
            if (IsNumericallyNull(this->GetCoefficient(var)))
                this->variable_map_.erase(var);
        }
    };

    EXPRESSION operator+(const VARIABLE& var1, const VARIABLE& var2)
    {
        EXPRESSION expr;
        expr += var1;
        expr += var2;
        return expr;
    }

    EXPRESSION operator-(const VARIABLE& var1, const VARIABLE& var2)
    {
        EXPRESSION expr;
        expr += var1;
        expr -= var2;
        return expr;
    }

    EXPRESSION operator*(const double coeff, const VARIABLE& var)
    {
        EXPRESSION expr;
        expr += var;
        expr.variable_map_.at(var) *= coeff;
        return expr;
    }

    EXPRESSION operator*(const VARIABLE& var, const double coeff)
    {
        EXPRESSION expr;
        expr += var;
        expr.variable_map_.at(var) *= coeff;
        return expr;
    }

    EXPRESSION operator/(const VARIABLE& var, const double coeff)
    {
        EXPRESSION expr;
        expr += var;
        expr.variable_map_.at(var) /= coeff;
        return expr;
    }

    // EXPRESSION operator/(const double coeff, const VARIABLE& var)
    // {
    //     EXPRESSION expr;
    //     expr += var;
    //     expr.variable_map_.at(var) /= coeff;
    //     return expr;
    // }
} // namespace OR2L