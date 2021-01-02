#pragma once
#include "EXPRESSION.h"
#include "EXPRESSION_OPERATORS_TYPE.h"

namespace OR2L
{
    class MATH_EXPRESSION
    {
    public:
        MATH_EXPRESSION(const EXPRESSION& lhs, const EXPRESSION_OPERATORS_TYPE eq_type, const EXPRESSION& rhs) :
            lhs_(lhs),
            eq_type_(eq_type),
            rhs_(rhs) {}
        virtual ~MATH_EXPRESSION() {}

    private:
        EXPRESSION lhs_ = 1.00;
        EXPRESSION rhs_ = 1.00;
        EXPRESSION_OPERATORS_TYPE eq_type_ = EXPRESSION_OPERATORS_TYPE::EQUAL;
    };

} // namespace OR2