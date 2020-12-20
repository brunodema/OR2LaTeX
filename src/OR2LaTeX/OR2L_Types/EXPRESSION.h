#pragma once
#include <set>
#include "VARIABLE.h"

namespace OR2L
{
    class COEFFICIENT
    {
    public:
        COEFFICIENT(const VARIABLE &var = VARIABLE({}, ""), const double multiplier = 1.00) : _variable(var),
                                                                                              _multiplier(multiplier) {}

        COEFFICIENT(const COEFFICIENT &) = default;
        COEFFICIENT(COEFFICIENT &&) = default;
        virtual COEFFICIENT &operator=(const COEFFICIENT &) = default;
        virtual COEFFICIENT &operator=(COEFFICIENT &&) = default;
        virtual ~COEFFICIENT() = default;

        inline VARIABLE Variable() const { return _variable; }
        inline double Multiplier() const { return _multiplier; }

    private:
        VARIABLE _variable = VARIABLE({}, "");
        double _multiplier = 1.00;
    };

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