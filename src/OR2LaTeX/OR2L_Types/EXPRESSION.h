#pragma once
#include <unordered_map>
#include "VARIABLE.h"
#include "COEFFICIENT.h"
#include <varargs.h>
#include <cstdarg>

namespace OR2L
{
    class EXPRESSION
    {
    public:
        EXPRESSION(const COEFFICIENT &coeff)
        {
            InsertOrUpdate(coeff);
        }

        EXPRESSION(const std::initializer_list<COEFFICIENT> coeffs)
        {
            for (auto &&coeff : coeffs)
            {
                InsertOrUpdate(coeff);
            }
        }

        EXPRESSION() {}

        EXPRESSION(const EXPRESSION &) = default;
        EXPRESSION(EXPRESSION &&) = default;
        virtual EXPRESSION &operator=(const EXPRESSION &) = default;
        virtual EXPRESSION &operator=(EXPRESSION &&) = default;
        virtual ~EXPRESSION() = default;

        EXPRESSION &operator+=(const EXPRESSION &B)
        {
            for (auto &&coeff : B._coeffs)
            {
                this->InsertOrUpdate({coeff.first, coeff.second});
            }
            return *this;
        }

        EXPRESSION &operator+=(const COEFFICIENT &coeff)
        {
            this->InsertOrUpdate(coeff);
            return *this;
        }

        EXPRESSION &operator+(COEFFICIENT &coeff)
        {
            this->InsertOrUpdate(coeff);
            return *this;
        }

        COEFFICIENT GetCoefficient(const VARIABLE &var) const
        {
            try
            {
                return {var, this->_coeffs.at(var)};
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

    private:
        void InsertOrUpdate(const COEFFICIENT &coeff)
        {
            if (_coeffs.contains(coeff.Variable()))
            {
                _coeffs.at(coeff.Variable()) += coeff.Multiplier();
            }
            else
            {
                _coeffs.try_emplace(coeff.Variable(), coeff.Multiplier());
            }
        }

        std::unordered_map<VARIABLE, double, HASH_VARIABLE> _coeffs;
    };

    EXPRESSION operator+(const COEFFICIENT &coeffA, const COEFFICIENT &coeffB)
    {
        return EXPRESSION({coeffA, coeffB});
    }
} // namespace OR2L