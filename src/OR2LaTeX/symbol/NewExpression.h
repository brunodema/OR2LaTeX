#pragma once
#include "Bounds.h"
#include "Variable.h"
#include "absl/hash/hash.h"
#include "symbol/Index.h"
#include <cstddef>
#include <iterator>
#include <vector>

namespace or2l
{

using base_types::Bounds;

struct IndexedCoefficient
{
  public:
    IndexedCoefficient() = default;
    IndexedCoefficient(const IndexedObject &_obj) : object(_obj), coefficient(1.00){};
    IndexedCoefficient(const double _coefficient, const IndexedObject &_obj)
        : object(_obj), coefficient(_coefficient){};
    IndexedCoefficient(const double &_value) : coefficient(_value){};

    bool operator==(const IndexedCoefficient &_other) const
    {
        return this->object == _other.object && this->coefficient == _other.coefficient;
    }
    template <typename H> friend H AbslHashValue(H _h, const IndexedCoefficient &_exprcoeff);

    IndexedObject object = {};
    double coefficient = 0.00;
};

template <typename H> H AbslHashValue(H _h, const or2l::IndexedCoefficient &_exprcoeff)
{
    return H::combine(std::move(_h), _exprcoeff.object, _exprcoeff.coefficient);
}

template<class T>
class InnerExpression
{
  public:
    InnerExpression<T>() = default;
    InnerExpression<T>(const T& _obj)
    {
        coefficient_map[_obj] = 1.00;
    }
    InnerExpression<T>(const double _value)
    {
        coefficient_map[{}] = _value;
    }

    template <typename H> friend H AbslHashValue(H _h, const InnerExpression<T> &_inner_expr);
    bool operator==(const InnerExpression<T> &_other) const
    {
        return this->GetCoefficients() == _other.GetCoefficients() && this->GetVariables() == _other.GetVariables();
    }

    friend InnerExpression<T> operator+(const IndexedCoefficient &_a, const IndexedCoefficient &_b);
    inline InnerExpression<T> operator+(const InnerExpression<T> &_a) const
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


    double &operator[](const T &_obj)
    {
        return coefficient_map[_obj];
    }

    std::size_t Size() const
    {
        return this->coefficient_map.size();
    }

    using Iterator = typename std::unordered_map<T, double, absl::Hash<T>>::const_iterator;
    Iterator begin() const
    {
        return this->coefficient_map.begin();
    }
    Iterator end() const
    {
        return this->coefficient_map.end();
    }

  private:
    std::vector<T> GetObjects() const
    {
        std::vector<T> ret(coefficient_map.size());
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
    std::unordered_map<T, double, absl::Hash<T>> coefficient_map = {};
};

template <class T, typename H> H AbslHashValue(H _h, const or2l::InnerExpression<T> &_inner_expr)
{
    return H::combine(std::move(_h), _inner_expr.GetObjects(), _inner_expr.GetCoefficients());
}

template<class T>
inline InnerExpression<T> operator+(const IndexedCoefficient &_a, const IndexedCoefficient &_b)
{
    InnerExpression<T> ret;
    if (_a.object == _b.object)
    {
        ret.coefficient_map[_a.object] = _a.coefficient + _b.coefficient;
        return ret;
    }
    ret.coefficient_map[_a.object] = _a.coefficient;
    ret.coefficient_map[_b.object] = _b.coefficient;
    return ret;
}

namespace operators // should include all other operators in the future
{
enum class ExpressionOperatorType
{
    SUMMATION
};
} // namespace operators

template<class T>
class IExpandedExpression
{
  public:
    IExpandedExpression() = default;
    IExpandedExpression(const operators::ExpressionOperatorType _type, const InnerExpression<T> &_inner_expr,
                        const std::initializer_list<Index> _expr_indexes)
        : type(_type), inner_expression(std::move(_inner_expr)), expression_indexes(std::move(_expr_indexes)),
          coefficient(1.00)
    {
    }
    IExpandedExpression(const double _coefficient, const operators::ExpressionOperatorType _type,
                        const InnerExpression<T> &_inner_expr, const std::initializer_list<Index> _expr_indexes)
        : type(_type), inner_expression(std::move(_inner_expr)), expression_indexes(std::move(_expr_indexes)),
          coefficient(_coefficient)
    {
    }
    virtual ~IExpandedExpression() = default;

    virtual operators::ExpressionOperatorType GetType() const
    {
        return type;
    }
    virtual InnerExpression<T> GetInnerExpression() const
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
    InnerExpression<T> inner_expression = {};
    std::vector<Index> expression_indexes = {};
    double coefficient = 0.00;
};

template<class T>
class ExpandedExpression : public IExpandedExpression<T>
{
  public:
    ExpandedExpression() = default;
    ExpandedExpression(operators::ExpressionOperatorType _type, const InnerExpression<T> &_inner_expr,
                       std::initializer_list<Index> _expr_indexes)
        : IExpandedExpression(1.00, _type, std::move(_inner_expr), _expr_indexes){};
    ExpandedExpression(const double _coefficient, operators::ExpressionOperatorType _type,
                       const InnerExpression<T> &_inner_expr, std::initializer_list<Index> _expr_indexes)
        : IExpandedExpression(_coefficient, _type, std::move(_inner_expr), _expr_indexes){};

    bool operator==(const ExpandedExpression<T> &_other) const
    {
        return this->type == _other.type && this->inner_expression == _other.inner_expression &&
               this->expression_indexes == _other.expression_indexes;
    }
    template <typename H> friend H AbslHashValue(H _h, const ExpandedExpression<T> &_expr_operator);
};

template <class T, typename H> H AbslHashValue(H _h, const or2l::ExpandedExpression<T> &_expr_operator)
{
    return H::combine(std::move(_h), _expr_operator.type, _expr_operator.inner_expression,
                      _expr_operator.expression_indexes);
}

template<class T>
class NewExpression
{
  public:
    NewExpression() = default;
    NewExpression(const InnerExpression<T> &_inner_expr) : inner_expression(std::move(_inner_expr))
    {
    }
    NewExpression(const ExpandedExpression<T> &_expanded_expr)
    {
        expandable_expression[_expanded_expr] = 1.00;
    }

    friend NewExpression<T> operator+(const ExpandedExpression<T> &_a, const ExpandedExpression<T> &_b);
    NewExpression<T> operator+(const NewExpression<T> &_a) const
    {
        NewExpression<T> ret;
        for (const auto &pair : this->inner_expression)
        {
            ret[pair.first] += pair.second;
        }
        for (const auto &pair : _a.inner_expression)
        {
            ret[pair.first] += pair.second;
        }
        for (const auto &pair : this->expandable_expression)
        {
            ret.expandable_expression[pair.first] += pair.second;
        }
        for (const auto &pair : _a.expandable_expression)
        {
            ret.expandable_expression[pair.first] += pair.second;
        }
        return ret;
    }

    double &operator[](const IndexedCoefficient &_obj)
    {
        return inner_expression[_obj];
    }
    double GetExpandableExpressionCoeff(const ExpandedExpression<T> &_exp_expr)
    {
        return this->expandable_expression[_exp_expr];
    }

  private:
    InnerExpression<T> inner_expression = {};
    using ExpExprMap = std::unordered_map<ExpandedExpression<T>, double, absl::Hash<ExpandedExpression<T>>>;
    ExpExprMap expandable_expression = {};
};

template<class T>
inline NewExpression<T> operator+(const ExpandedExpression<T> &_a, const ExpandedExpression<T> &_b)
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
