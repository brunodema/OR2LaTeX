#pragma once
#include <unordered_map>
#include <utility>
#include "VARIABLE.h"

using namespace OR2L;

namespace OR2L
{
    class EXPRESSION
    {
    public:
        EXPRESSION(const double coeff = 0.00) : _scalar_coefficient(coeff) {}

        EXPRESSION(const EXPRESSION &) = default;
        EXPRESSION(EXPRESSION &&) = default;
        virtual EXPRESSION &operator=(const EXPRESSION &) = default;
        virtual EXPRESSION &operator=(EXPRESSION &&) = default;
        virtual ~EXPRESSION() = default;

        EXPRESSION &operator+=(const double coeff)
        {
            this->_scalar_coefficient += coeff;
            return *this;
        }

        EXPRESSION &operator-=(const double coeff)
        {
            this->_scalar_coefficient -= coeff;
            return *this;
        }

        EXPRESSION &operator+=(const VARIABLE &var)
        {
            if (this->_variable_map.contains(var))
            {
                ++this->_variable_map.at(var);
            }
            else
            {
                this->_variable_map.emplace(var, 1.00);
            }
            return *this;
        }

        EXPRESSION &operator-=(const VARIABLE &var)
        {
            if (this->_variable_map.contains(var))
            {
                --this->_variable_map.at(var);
            }
            else
            {
                this->_variable_map.emplace(var, -1.00);
            }
            return *this;
        }

        EXPRESSION &operator*=(const double coeff)
        {
            this->_scalar_coefficient *= coeff;
            return *this;
        }

        EXPRESSION &operator/=(const double coeff)
        {
            this->_scalar_coefficient /= coeff;
            return *this;
        }

        EXPRESSION &operator+(const EXPRESSION &expr)
        {
            for (auto &&var_coeff : expr._variable_map)
            {
                this->_variable_map.at(var_coeff.first) += var_coeff.second;
            }
            this->_scalar_coefficient += expr._scalar_coefficient;
            return *this;
        }

        EXPRESSION &operator-(const EXPRESSION &expr)
        {
            for (auto &&var_coeff : expr._variable_map)
            {
                this->_variable_map.at(var_coeff.first) -= var_coeff.second;
            }
            this->_scalar_coefficient -= expr._scalar_coefficient;
            return *this;
        }

        EXPRESSION &operator+(const VARIABLE &var)
        {
            ++this->_variable_map.at(var);
            return *this;
        }

        EXPRESSION &operator-(const VARIABLE &var)
        {
            --this->_variable_map.at(var);
            return *this;
        }

        friend EXPRESSION operator+(const VARIABLE &var1, const VARIABLE &var2);
        friend EXPRESSION operator-(const VARIABLE &var1, const VARIABLE &var2);
        friend EXPRESSION operator*(const VARIABLE &var, const double coeff);

    private:
        std::unordered_map<VARIABLE, double> _variable_map = {};
        double _scalar_coefficient = 0.00;
    };

    EXPRESSION operator+(const VARIABLE &var1, const VARIABLE &var2)
    {
        EXPRESSION expr;
        expr += var1;
        expr += var2;
        return expr;
    }

    EXPRESSION operator-(const VARIABLE &var1, const VARIABLE &var2)
    {
        EXPRESSION expr;
        expr += var1;
        expr -= var2;
        return expr;
    }

    EXPRESSION operator*(const VARIABLE &var, const double coeff)
    {
        EXPRESSION expr;
        expr += var;
        expr._variable_map.at(var) *= coeff;
        return expr;
    }

    // create overloads for operator*(var, double)
} // namespace OR2L