#pragma once
#include "EXPRESSION.h"
#include "EXPRESSION_OPERATORS_TYPE.h"

namespace OR2L
{
    class MATH_EXPRESSION
    {
    public:
        MATH_EXPRESSION(EXPRESSION& lhs, EXPRESSION_OPERATORS_TYPE eq_type, EXPRESSION& rhs) :
            lhs_(lhs),
            eq_type_(eq_type),
            rhs_(rhs) {}

        MATH_EXPRESSION(const MATH_EXPRESSION&) = default;
        MATH_EXPRESSION(MATH_EXPRESSION&&) = default;
        virtual MATH_EXPRESSION& operator=(const MATH_EXPRESSION&) = default;
        virtual MATH_EXPRESSION& operator=(MATH_EXPRESSION&&) = default;
        virtual ~MATH_EXPRESSION() = default;

    private:
        EXPRESSION lhs_ = 1.00;
        EXPRESSION rhs_ = 1.00;
        EXPRESSION_OPERATORS_TYPE eq_type_ = EXPRESSION_OPERATORS_TYPE::EQUAL;
    };

} // namespace OR2