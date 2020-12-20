#pragma once
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
} // namespace OR2L
