#pragma once
#include <variant>
#include "VARIABLE.h"

namespace OR2L
{
    using VALID_COEFF = std::variant<double, VARIABLE>;

    class EXPRESSION
    {  
    public:
        EXPRESSION(const VALID_COEFF& var)
        {
            //coeffs.push_back(var);
        }

        EXPRESSION() {}
        
        EXPRESSION(const EXPRESSION&) = default;
        EXPRESSION(EXPRESSION&&) = default;
        virtual EXPRESSION& operator=(const EXPRESSION&) = default;
        virtual EXPRESSION& operator=(EXPRESSION&&) = default;
        virtual ~EXPRESSION() = default;

    private:
        std::unordered_map<VALID_COEFF, double> _weights = {};
    };
}