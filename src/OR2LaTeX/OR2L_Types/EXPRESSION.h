#pragma once
#include <set>
#include "VARIABLE.h"

namespace OR2L
{
    class EXPRESSION
    {
    public:
        EXPRESSION(COEFFICIENT &coeff)
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

        EXPRESSION() {}

        EXPRESSION(const EXPRESSION &) = default;
        EXPRESSION(EXPRESSION &&) = default;
        virtual EXPRESSION &operator=(const EXPRESSION &) = default;
        virtual EXPRESSION &operator=(EXPRESSION &&) = default;
        virtual ~EXPRESSION() = default;

    private:
        std::unordered_map<VARIABLE, double> _coeffs = {};
    };

    EXPRESSION operator+(const VARIABLE &A, const VARIABLE &B)
    {
    }
} // namespace OR2L