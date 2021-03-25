#pragma once
#include "Bounds.h"
#include "Variable.h"
#include "absl/hash/hash.h"

namespace or2l
{

using base_types::Bounds;

struct ExpressionCoefficient
{
  public:
    ExpressionCoefficient() = default;
    ExpressionCoefficient(const Variable &_var) : variable(_var), coefficient(1.00){};
    ExpressionCoefficient(const double _coefficient, const Variable &_var)
        : variable(_var), coefficient(_coefficient){};
    ExpressionCoefficient(const double &_value) : coefficient(_value){};

    bool operator==(const ExpressionCoefficient &_other) const
    {
        return this->variable == _other.variable && this->coefficient == _other.coefficient;
    }
    template <typename H> friend H AbslHashValue(H _h, const ExpressionCoefficient &_exprcoeff);

    Variable variable = {};
    double coefficient = 0.00;
};

template <typename H> H AbslHashValue(H _h, const or2l::ExpressionCoefficient &_exprcoeff)
{
    return H::combine(std::move(_h), _exprcoeff.variable, _exprcoeff.coefficient);
}

class InnerExpression
{
  public:
    InnerExpression() = default;
    InnerExpression(const ExpressionCoefficient &_exprcoeff)
    {
        coefficient_map[_exprcoeff.variable] = _exprcoeff.coefficient;
    }
    InnerExpression(const Variable &_var)
    {
        coefficient_map[_var] = 1.00;
    }
    InnerExpression(const double _value)
    {
        coefficient_map[{}] = _value;
    }

    template <typename H> friend H AbslHashValue(H _h, const InnerExpression &_inner_expr);
    bool operator==(const InnerExpression &_other) const
    {
        return this->GetCoefficients() == _other.GetCoefficients() && this->GetVariables() == _other.GetVariables();
    }

    friend InnerExpression operator+(const ExpressionCoefficient &_a, const ExpressionCoefficient &_b);
    inline InnerExpression operator+(const InnerExpression &_a) const
    {
        InnerExpression ret;
        for (const auto &pair : this->coefficient_map)
        {
            ret[pair.first] += pair.second;
        }
        for (const auto &pair : _a.coefficient_map)
        {
            ret[pair.first] += pair.second;
        }
        return ret;
    }

    double operator[](const Variable &_var) const
    {
        return this->coefficient_map.at(_var);
    }
    double &operator[](const Variable &_var)
    {
        return coefficient_map[_var];
    }

  private:
    std::vector<Variable> GetVariables() const
    {
        std::vector<Variable> ret(coefficient_map.size());
        for (const auto &pair : coefficient_map)
        {
            ret.push_back(pair.first);
        }
        return ret;
    }
    std::vector<double> GetCoefficients() const
    {
        std::vector<double> ret(coefficient_map.size());
        for (const auto &pair : coefficient_map)
        {
            ret.push_back(pair.second);
        }
        return ret;
    }
    std::unordered_map<Variable, double, absl::Hash<Variable>> coefficient_map = {};
};

template <typename H> H AbslHashValue(H _h, const or2l::InnerExpression &_inner_expr)
{
    return H::combine(std::move(_h), _inner_expr.GetVariables(), _inner_expr.GetCoefficients());
}

// template <typename H> H AbslHashValue(H _h, const or2l::InnerExpression &_inner_expr)
// {
//     return H::combine(std::move(_h), _inner_expr.GetVariables(), _inner_expr.GetCoefficients());
// }

inline InnerExpression operator+(const ExpressionCoefficient &_a, const ExpressionCoefficient &_b)
{
    InnerExpression ret;
    if (_a.variable == _b.variable)
    {
        ret.coefficient_map[_a.variable] = _a.coefficient + _b.coefficient;
        return ret;
    }
    ret.coefficient_map[_a.variable] = _a.coefficient;
    ret.coefficient_map[_b.variable] = _b.coefficient;
    return ret;
}

namespace operators // should include all other operators in the future
{
enum class ExpressionOperatorType
{
    SUMMATION
};
} // namespace operators

class IExpandedExpression
{
  public:
    IExpandedExpression() = default;
    IExpandedExpression(const operators::ExpressionOperatorType _type, const InnerExpression &_inner_expr,
                        const std::initializer_list<Index> _expr_indexes)
        : type(_type), inner_expression(std::move(_inner_expr)), expression_indexes(std::move(_expr_indexes)),
          coefficient(1.00)
    {
    }
    IExpandedExpression(const double _coefficient, const operators::ExpressionOperatorType _type,
                        const InnerExpression &_inner_expr, const std::initializer_list<Index> _expr_indexes)
        : type(_type), inner_expression(std::move(_inner_expr)), expression_indexes(std::move(_expr_indexes)),
          coefficient(_coefficient)
    {
    }
    virtual ~IExpandedExpression() = default;

    virtual operators::ExpressionOperatorType GetType() const
    {
        return type;
    }
    virtual InnerExpression GetInnerExpression() const
    {
        return inner_expression;
    }
    virtual std::vector<Index> GetExpressionIndexes() const
    {
        return expression_indexes;
    }
    virtual double GetCoefficient() const
    {
        return coefficient;
    }

  protected:
    operators::ExpressionOperatorType type = {};
    InnerExpression inner_expression = {};
    std::vector<Index> expression_indexes = {};
    double coefficient = 0.00;
};

class ExpandedExpression : public IExpandedExpression
{
  public:
    ExpandedExpression() = default;
    ExpandedExpression(operators::ExpressionOperatorType _type, const InnerExpression &_inner_expr,
                       std::initializer_list<Index> _expr_indexes)
        : IExpandedExpression(1.00, _type, std::move(_inner_expr), _expr_indexes){};
    ExpandedExpression(const double _coefficient, operators::ExpressionOperatorType _type,
                       const InnerExpression &_inner_expr, std::initializer_list<Index> _expr_indexes)
        : IExpandedExpression(_coefficient, _type, std::move(_inner_expr), _expr_indexes){};

    bool operator==(const ExpandedExpression &_other) const
    {
        return this->type == _other.type && this->inner_expression == _other.inner_expression &&
               this->expression_indexes == _other.expression_indexes;
    }
    template <typename H> friend H AbslHashValue(H _h, const ExpandedExpression &_expr_operator);
};

template <typename H> H AbslHashValue(H _h, const or2l::ExpandedExpression &_expr_operator)
{
    return H::combine(std::move(_h), _expr_operator.type, _expr_operator.inner_expression,
                      _expr_operator.expression_indexes);
}

class NewExpression
{
  public:
    NewExpression() = default;
    NewExpression(const InnerExpression &_inner_expr) : inner_expression(std::move(_inner_expr))
    {
    }
    NewExpression(const ExpandedExpression &_expanded_expr) : inner_expression(_expanded_expr.GetInnerExpression())
    {
        expandable_expression[_expanded_expr] = 1.00;
    }

    friend NewExpression operator+(const ExpandedExpression &_a, const ExpandedExpression &_b);

  private:
    InnerExpression inner_expression = {};
    std::unordered_map<ExpandedExpression, double, absl::Hash<ExpandedExpression>> expandable_expression = {};
};

inline NewExpression operator+(const ExpandedExpression &_a, const ExpandedExpression &_b)
{
    // attention: the assumptions here are that (1) the type of the operation match, after all it does not make sense to
    // add a 'Summation' to a 'Product Notation'; (2) the indexes of the operator are EXACTLY the same. These
    // assumptions might need to be reviewed in the future.
    NewExpression ret;
    if (_a.GetType() == _b.GetType() && _a.GetExpressionIndexes() == _b.GetExpressionIndexes())
    {
        auto expression_indexes = _a.GetExpressionIndexes(); // only way to make it work
        ret.expandable_expression[_a] = _a.GetCoefficient() + _b.GetCoefficient();
        return ret;
    }
    ret.expandable_expression[_a] = _a.GetCoefficient();
    ret.expandable_expression[_b] = _b.GetCoefficient();
    return ret;
}

} // namespace or2l