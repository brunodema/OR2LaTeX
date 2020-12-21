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

        EXPRESSION() {}

        EXPRESSION(const EXPRESSION &) = default;
        EXPRESSION(EXPRESSION &&) = default;
        virtual EXPRESSION &operator=(const EXPRESSION &) = default;
        virtual EXPRESSION &operator=(EXPRESSION &&) = default;
        virtual ~EXPRESSION() = default;

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

    EXPRESSION operator+(const COEFFICIENT &A, const COEFFICIENT &B)
    {
        return EXPRESSION(A);
    }
} // namespace OR2L