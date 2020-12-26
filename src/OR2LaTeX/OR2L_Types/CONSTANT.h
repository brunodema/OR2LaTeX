#pragma once
#include "VARIABLE.h"

namespace OR2L
{
    class CONSTANT : public VARIABLE
    {
    public:
        CONSTANT(double val = 0.00) {}

        CONSTANT(const CONSTANT &) = default;
        CONSTANT(CONSTANT &&) = default;
        virtual CONSTANT &operator=(const CONSTANT &) = default;
        virtual CONSTANT &operator=(CONSTANT &&) = default;
        virtual ~CONSTANT() = default;



        double multiplier = 0.00;
    };
} // namespace OR2L