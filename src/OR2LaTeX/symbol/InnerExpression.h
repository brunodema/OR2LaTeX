#pragma once
#include "Variable.h"
#include "absl/hash/hash.h"

template <class T> struct type_traits
{
    using parent = void;
};
template <> struct type_traits<or2l::Variable>
{
    using parent = or2l::IndexedSymbol;
};
template <> struct type_traits<or2l::Constant>
{
    using parent = or2l::IndexedSymbol;
};

template <class T, class U = T> struct inheritance_traits
{
    constexpr static bool has_same_parent();
    constexpr static bool inherits_from();
};
template <class T, class U> constexpr bool inheritance_traits<T, U>::has_same_parent()
{
    using parent_type = typename type_traits<T>::parent;
    return std::is_base_of<parent_type, T>::value && std::is_base_of<parent_type, U>::value &&
           !std::is_same<parent_type, T>::value && !std::is_same<parent_type, U>::value;
}

template <class T, class U> constexpr bool inheritance_traits<T, U>::inherits_from()
{
    return std::is_base_of<T, U>::value && !std::is_same<T, U>::value;
}

template <class T> class InnerExpression
{

  public:
    InnerExpression() = default;
    InnerExpression(const T &_obj)
    {
        this->coefficient_map[_obj] += 1.00;
    }

    template <class numeric_type, typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
    InnerExpression<T> &operator+=(const numeric_type &_val)
    {
        this->operator[]({}) += _val;
        return *this;
    }

    InnerExpression<T> &operator+=(const T &_obj)
    {
        this->operator[](static_cast<T>(_obj)) += 1.00;
        return *this;
    }

    template <class Child, typename = typename std::enable_if<inheritance_traits<T, Child>::inherits_from()>::type>
    InnerExpression<T> &operator+=(const InnerExpression<Child> &_expr)
    {
        for (const auto &pair : _expr)
        {
            this->operator[](static_cast<T>(pair.first)) += pair.second;
        }
        return *this;
    }

    InnerExpression<T> &operator+=(const InnerExpression<T> &_expr)
    {
        for (const auto &pair : _expr)
        {
            this->operator[](pair.first) += pair.second;
        }
        return *this;
    }

    template <class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<inheritance_traits<parent_type, T>::inherits_from()>::type>
    InnerExpression<parent_type> operator+=(const parent_type &_obj)
    {
        InnerExpression<parent_type> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(pair.first)] += pair.second;
        }
        ret[_obj] += 1.00;
        return ret;
    }

    template <class parent_type = typename type_traits<T>::parent, class Child,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    InnerExpression<parent_type> operator+=(const Child &_obj)
    {
        InnerExpression<parent_type> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(_obj)] += pair.second;
        }
        ret[static_cast<parent_type>(_obj)] += 1.00;
        return ret;
    }

    template <class parent_type,
              typename = typename std::enable_if<inheritance_traits<parent_type, T>::inherits_from()>::type>
    InnerExpression<parent_type> operator+=(const InnerExpression<parent_type> &_expr)
    {
        InnerExpression<parent_type> ret(_expr);
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(pair.first)] += pair.second;
        }
        return ret;
    }

    template <class Child, class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    InnerExpression<parent_type> operator+=(const InnerExpression<Child> &_expr)
    {
        InnerExpression<parent_type> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(pair.first)] += pair.second;
        }
        for (const auto &pair : _expr)
        {
            ret[static_cast<parent_type>(pair.first)] += pair.second;
        }
        return ret;
    }

    auto begin() const
    {
        return this->coefficient_map.begin();
    }
    auto end() const
    {
        return this->coefficient_map.end();
    }
    double &operator[](const T &_obj)
    {
        return this->coefficient_map[_obj];
    }
    double operator[](const T &_obj) const
    {
        return this->coefficient_map.at(obj);
    }
    std::size_t GetSize() const
    {
        return this->coefficient_map.size();
    }

  private:
    using map_type = std::unordered_map<T, double, absl::Hash<T>>;
    map_type coefficient_map = {{{}, 0.00}};
};

template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const T &_obj, const numeric_type &_val)
{
    InnerExpression<T> ret(_obj);
    return ret += _val;
}
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const numeric_type &_val, const T &_obj)
{
    return _obj + _val; // commutative
}

template <class T> InnerExpression<T> operator+(const T &_lhs, const T &_rhs)
{
    InnerExpression<T> ret(_lhs);
    return ret += _rhs;
}

template <class T> InnerExpression<T> operator+(InnerExpression<T> _expr1, const InnerExpression<T> &_expr2)
{
    return _expr1 += _expr2; // uses copy of _expr to speed things up
}

template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(const Child1 &_child1, const Child2 &_child2)
{
    InnerExpression<parent_type> ret(static_cast<parent_type>(_child1));
    return ret += _child2;
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(const parent_type &_parent, const Child &_child)
{
    InnerExpression<parent_type> ret(_parent);
    return ret += _child;
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(const Child &_child, const parent_type &_parent)
{
    return _parent + _child; // commutative
}

template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(InnerExpression<T> _expr, const numeric_type &_val)
{
    return _expr += _val; // uses copy of _expr to speed things up
}

template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const numeric_type &_val, const InnerExpression<T> &_expr)
{
    return _expr + _val; // commutative
}

template <class T> InnerExpression<T> operator+(InnerExpression<T> _expr, const T &_obj)
{
    return _expr += _obj; // uses copy of _expr to speed things up
}

template <class T> InnerExpression<T> operator+(const T &_obj, const InnerExpression<T> &_expr)
{
    return _expr + _obj; // commutative
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(InnerExpression<parent_type> _expr, const Child &_child)
{
    return _expr += _child; // uses copy of _expr to speed things up
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(const Child &_child, const InnerExpression<parent_type> &_expr)
{
    return _expr + _child; // commutative
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(InnerExpression<Child> _expr, const parent_type &_parent)
{
    return _expr += _parent; // uses copy of _expr to speed things up
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(const parent_type &_parent, const InnerExpression<Child> &_expr)
{
    return _expr + _parent; // commutative
}

template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(InnerExpression<Child2> _expr, const Child1 &_child)
{
    return _expr += _child; // uses copy of _expr to speed things up
}

template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(const Child1 &_child, const InnerExpression<Child2> &_expr)
{
    return _expr + _child; // commutative
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(InnerExpression<parent_type> _expr, const InnerExpression<Child> &_child)
{
    return _expr += _child; // uses copy of _expr to speed things up
}

template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type> operator+(const InnerExpression<Child> &_child, InnerExpression<parent_type> _expr)
{
    return _expr + _child; // commutative
}

template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(InnerExpression<Child1> _expr1, const InnerExpression<Child2> &_expr2)
{
    return _expr1 += _expr2; // uses copy of _expr to speed things up
}
