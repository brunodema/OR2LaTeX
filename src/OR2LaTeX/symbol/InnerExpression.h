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
};
template <class T, class U> constexpr bool inheritance_traits<T, U>::has_same_parent()
{
    using parent_type = typename type_traits<T>::parent;
    return std::is_base_of<parent_type, T>::value && std::is_base_of<parent_type, U>::value &&
           !std::is_same<parent_type, T>::value && !std::is_same<parent_type, U>::value;
}

template <class T> class InnerExpression
{

  public:
    InnerExpression() = default;
    InnerExpression(const T& _obj)
    {
        this->coefficient_map[_obj] += 1.00;
    }

    template <class numeric_type, typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
    InnerExpression<T>& operator+(const numeric_type &_val)
    {
        this->operator[]({}) += _val;
        return *this;
    }

    InnerExpression<T>& operator+(const T &_obj)
    {
        this->operator[](static_cast<T>(_obj)) += 1.00;
        return *this;
    }

    template <class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<std::is_base_of<parent_type, T>::value>::type>
    InnerExpression<parent_type> operator+(const parent_type &_obj)
    {
        InnerExpression<parent_type> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(pair.first)] += pair.second;
        }
        ret[_obj] += 1.00;
        return InnerExpression<parent_type>();
    }

    template <class parent_type = typename type_traits<T>::parent, class Child,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    InnerExpression<parent_type> operator+(const Child &_obj)
    {
        InnerExpression<parent_type> ret;
        for (const auto &pair : *this)
        {
            ret[static_cast<parent_type>(_obj)] += pair.second;
        }
        ret[static_cast<parent_type>(_obj)] += 1.00;
        return InnerExpression<parent_type>();
    }

    template <class Child, typename = typename std::enable_if<std::is_base_of<T, Child>::value>::type>
    InnerExpression<T>& operator+(InnerExpression<Child> &_expr) // no idea why but I have to drop 'const' here
    {
        for (const auto& pair : _expr)
        {
            this->operator[](static_cast<T>(pair.first)) += pair.second;
        }
        return *this;
    }

    template <class parent_type, typename = typename std::enable_if<std::is_base_of<parent_type, T>::value>::type>
    InnerExpression<parent_type> operator+(const InnerExpression<parent_type> &_expr)
    {
        InnerExpression<parent_type> ret(std::move(_expr));
        for (const auto &pair : *this)
        {
            ret[static_cast<T>(pair.first)] += pair.second;
        }
        return ret;
    }

    template <class Child, class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    InnerExpression<parent_type> operator+(InnerExpression<Child> &_expr) // no idea why but I have to drop 'const' here
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

    InnerExpression<T>& operator+(const InnerExpression<T> &_expr)
    {
        for (const auto &pair : _expr)
        {
            this->operator[](pair.first)  += pair.second;
        }
        return *this;
    }

    using map_type = std::unordered_map<T, double, absl::Hash<T>>;
    //using iterator_type = typename map_type::iterator;
    auto begin()
    {
        return this->coefficient_map.begin();
    }
    auto end() 
    {
        return this->coefficient_map.end();
    }
    double& operator[](const T& _obj)
    {
        return this->coefficient_map[_obj];
    }

  private:
    map_type coefficient_map = {};
};

template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const T &_obj, const numeric_type &_val)
{
    InnerExpression<T> ret(_obj);
    ret[{}] = _val;
    return ret;
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
    ret[_rhs] += 1.00;
    return ret;
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
InnerExpression<parent_type> operator+(const Child &_child, const parent_type &_parent)
{
    InnerExpression<parent_type> ret(_parent);
    ret[_child] += 1.00;
    return ret;
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
InnerExpression<parent_type> operator+(const parent_type &_parent, const Child &_child)
{
    return _child + _parent; // commutative
}
template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(const Child1 &_child1, const Child2 &_child2)
{
    InnerExpression<parent_type> ret(static_cast<parent_type>(_child1));
    return ret + _child2;
}

template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const numeric_type &lhs, const InnerExpression<T> &rhs)
{

    return InnerExpression<T>();
}

template <class T> InnerExpression<T> operator+(const T &lhs, const InnerExpression<T> &rhs)
{

    return InnerExpression<T>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
InnerExpression<parent_type> operator+(const Child &lhs, const InnerExpression<parent_type> &rhs)
{

    return InnerExpression<parent_type>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
InnerExpression<parent_type> operator+(const parent_type &lhs, const InnerExpression<Child> &rhs)
{

    return InnerExpression<parent_type>();
}
template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(const Child1 &lhs, const InnerExpression<Child2> &rhs)
{

    return InnerExpression<parent_type>();
}