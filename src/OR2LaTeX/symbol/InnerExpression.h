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

template <class T, class coefficient_type = double> class InnerExpression
{

  public:
    InnerExpression() = default;
    InnerExpression(const double _val)
    {
        this->coefficient_map[{}] = _val;
    }
    InnerExpression(const T &_obj)
    {
        this->coefficient_map[{}] = 0.00;
        this->coefficient_map[_obj] = 1.00;
    }

    template <class numeric_type, typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
    InnerExpression<T, coefficient_type> &operator+=(const numeric_type &_val)
    {
        this->operator[]({}) += _val;
        return *this;
    }

    InnerExpression<T, coefficient_type> &operator+=(const T &_obj)
    {
        this->operator[](static_cast<T>(_obj)) += 1.00; // our current problem is that objects are getting inserted as scalars instead of actual objects when dealing with coefficient_type = InnerExpression<Constant>. This happens due to this declaration, which accesses the InnerExpression<Constant> and adds a scalar into it. In theory, it should be passed as an object, but I am not able to "forward" the object into the nested InnerExpression. Maybe try to specialize the template?*******************
        return *this;
    }

    template <class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<inheritance_traits<parent_type, T>::inherits_from()>::type>
    InnerExpression<parent_type, coefficient_type> operator+=(const parent_type &_obj)
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
    InnerExpression<parent_type, coefficient_type> operator+=(const Child &_obj)
    {
        InnerExpression<parent_type> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(pair.first)] += pair.second;
        }
        ret[static_cast<parent_type>(_obj)] += 1.00;
        return ret;
    }

    template <class Child, typename = typename std::enable_if<inheritance_traits<T, Child>::inherits_from()>::type>
    InnerExpression<T, coefficient_type> &operator+=(const InnerExpression<Child, coefficient_type> &_expr)
    {
        for (const auto &pair : _expr)
        {
            this->operator[](static_cast<T>(pair.first)) += pair.second;
        }
        return *this;
    }

    InnerExpression<T, coefficient_type> &operator+=(const InnerExpression<T, coefficient_type> &_expr)
    {
        for (const auto &pair : _expr)
        {
            this->operator[](pair.first) += pair.second;
        }
        return *this;
    }

    template <class parent_type,
              typename = typename std::enable_if<inheritance_traits<parent_type, T>::inherits_from()>::type>
    InnerExpression<parent_type, coefficient_type> operator+=(
        const InnerExpression<parent_type, coefficient_type> &_expr)
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
    InnerExpression<parent_type, coefficient_type> operator+=(const InnerExpression<Child, coefficient_type> &_expr)
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
    auto &operator[](const T &_obj)
    {
        return this->coefficient_map[static_cast<T>(_obj)];
    }
    auto operator[](const T &_obj) const
    {
        return this->coefficient_map.at(static_cast<T>(_obj));
    }
    std::size_t GetSize() const
    {
        return this->coefficient_map.size();
    }

    template <
        class target_type, class target_coefficient,
        typename = typename std::enable_if<std::is_base_of<target_type, T>::value &&
                                           std::is_convertible<coefficient_type, target_coefficient>::value>::type>
    operator InnerExpression<target_type, target_coefficient>()
    {
        InnerExpression<target_type, target_coefficient> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<target_type>(pair.first)] = static_cast<target_coefficient>(pair.second);
        }
        return ret;
    }

    bool operator==(const InnerExpression<T, coefficient_type> &_expr) const
    {
        if (this->GetSize() != _expr.GetSize())
        {
            return false;
        }
        for (const auto &pair : *this)
        {
            if (this->operator[](pair.first) != _expr.operator[](pair.first))
            {
                return false;
            }
        }
        return true;
    }

  private:
    using map_type = std::unordered_map<T, coefficient_type, absl::Hash<T>>;
    map_type coefficient_map = {{{}, 0.00}};
};

// -----------------------------------------

template <class T, class coefficient_type = double, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T, coefficient_type> operator+(const T &_obj, const numeric_type &_val)
{
    InnerExpression<T> ret(_obj);
    return ret += _val;
}
template <class T, class coefficient_type = double, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T, coefficient_type> operator+(const numeric_type &_val, const T &_obj)
{
    return _obj + _val; // commutative
}

template <class T, class coefficient_type = double>
InnerExpression<T, coefficient_type> operator+(const T &_lhs, const T &_rhs)
{
    InnerExpression<T, coefficient_type> ret(_lhs);
    return ret += _rhs;
}

template <class T, class coefficient_type = double>
InnerExpression<T, coefficient_type> operator+(InnerExpression<T, coefficient_type> _expr1,
                                               const InnerExpression<T, coefficient_type> &_expr2)
{
    return _expr1 += _expr2; // uses copy of _expr to speed things up
}

template <class Child1, class Child2, class coefficient_type = double,
          class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const Child1 &_child1, const Child2 &_child2)
{
    InnerExpression<parent_type, coefficient_type> ret(static_cast<parent_type>(_child1));
    return ret += _child2;
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const parent_type &_parent, const Child &_child)
{
    InnerExpression<parent_type, coefficient_type> ret(_parent);
    return ret += _child;
}
template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const Child &_child, const parent_type &_parent)
{
    return _parent + _child; // commutative
}

template <class T, class coefficient_type = double, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T, coefficient_type> operator+(InnerExpression<T, coefficient_type> _expr, const numeric_type &_val)
{
    return _expr += _val; // uses copy of _expr to speed things up
}

template <class T, class coefficient_type = double, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T, coefficient_type> operator+(const numeric_type &_val,
                                               const InnerExpression<T, coefficient_type> &_expr)
{
    return _expr + _val; // commutative
}

template <class T, class coefficient_type = double>
InnerExpression<T, coefficient_type> operator+(InnerExpression<T, coefficient_type> _expr, const T &_obj)
{
    return _expr += _obj; // uses copy of _expr to speed things up
}

template <class T, class coefficient_type = double>
InnerExpression<T, coefficient_type> operator+(const T &_obj, const InnerExpression<T, coefficient_type> &_expr)
{
    return _expr + _obj; // commutative
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(InnerExpression<parent_type, coefficient_type> _expr,
                                                         const Child &_child)
{
    return _expr += _child; // uses copy of _expr to speed things up
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const Child &_child,
                                                         const InnerExpression<parent_type, coefficient_type> &_expr)
{
    return _expr + _child; // commutative
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(InnerExpression<Child, coefficient_type> _expr,
                                                         const parent_type &_parent)
{
    return _expr += _parent; // uses copy of _expr to speed things up
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const parent_type &_parent,
                                                         const InnerExpression<Child, coefficient_type> &_expr)
{
    return _expr + _parent; // commutative
}

template <class Child1, class Child2, class coefficient_type = double,
          class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type, coefficient_type> operator+(InnerExpression<Child2, coefficient_type> _expr,
                                                         const Child1 &_child)
{
    return _expr += _child; // uses copy of _expr to speed things up
}

template <class Child1, class Child2, class coefficient_type = double,
          class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const Child1 &_child,
                                                         const InnerExpression<Child2, coefficient_type> &_expr)
{
    return _expr + _child; // commutative
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(InnerExpression<parent_type, coefficient_type> _expr,
                                                         const InnerExpression<Child, coefficient_type> &_child)
{
    return _expr += _child; // uses copy of _expr to speed things up
}

template <class Child, class coefficient_type = double, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<inheritance_traits<parent_type, Child>::inherits_from()>::type>
InnerExpression<parent_type, coefficient_type> operator+(const InnerExpression<Child, coefficient_type> &_child,
                                                         InnerExpression<parent_type, coefficient_type> _expr)
{
    return _expr + _child; // commutative
}

template <class Child1, class Child2, class coefficient_type = double,
          class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type, coefficient_type> operator+(InnerExpression<Child1, coefficient_type> _expr1,
                                                         const InnerExpression<Child2, coefficient_type> &_expr2)
{
    return _expr1 += _expr2; // uses copy of _expr to speed things up
}
