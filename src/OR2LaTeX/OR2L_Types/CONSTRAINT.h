#pragma once
#include "MATH_EXPRESSION.h"

namespace OR2L
{
    class CONSTRAINT : public SYMBOL_COMPONENT
    {
    public:
        CONSTRAINT(const REGEX_STRING name, const MATH_EXPRESSION& math_expression) :
            SYMBOL_COMPONENT(name, SYMBOL_TYPE::CONSTRAINT),
            math_expression_(math_expression) {}

        virtual ~CONSTRAINT() {}

    private:
        MATH_EXPRESSION math_expression_;
    };
} // namespace OR2L
