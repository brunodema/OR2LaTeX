#pragma once
#include "EXPRESSION.h"

namespace OR2L
{
    class MATH_EXPRESSION
    {
    public:
        MATH_EXPRESSION() {}

        MATH_EXPRESSION(const MATH_EXPRESSION&) = default;
        MATH_EXPRESSION(MATH_EXPRESSION&&) = default;
        virtual MATH_EXPRESSION& operator=(const MATH_EXPRESSION&) = default;
        virtual MATH_EXPRESSION& operator=(MATH_EXPRESSION&&) = default;
        virtual ~MATH_EXPRESSION() = default;

    private:

    }

} // namespace OR2