#pragma once
#include "VARIABLE.h"

namespace OR2L
{
    class COEFFICIENT
    {
    public:
        COEFFICIENT(const VARIABLE &var = VARIABLE({}, ""), const double multiplier = 1.00) : _variable(var),
                                                                                              _multiplier(multiplier) {}

        COEFFICIENT(const double &constant) : _multiplier(constant) {}

        COEFFICIENT(const COEFFICIENT &) = default;
        COEFFICIENT(COEFFICIENT &&) = default;
        virtual COEFFICIENT &operator=(const COEFFICIENT &) = default;
        virtual COEFFICIENT &operator=(COEFFICIENT &&) = default;
        virtual ~COEFFICIENT() = default;

        inline VARIABLE GetVariable() const { return _variable; }
        inline void SetVariable(const VARIABLE& var) { _variable = var; }
        inline double GetMultiplier() const { return _multiplier; }
        inline void SetMultiplier(const double val) { _multiplier = val; }

    private:
        VARIABLE _variable = VARIABLE({}, "");
        double _multiplier = 1.00;
    };
} // namespace OR2L
