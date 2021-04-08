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

    template <class numeric_type, typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
    InnerExpression<T> operator+(const numeric_type &lhs)
    {

        return InnerExpression<T>();
    }

    InnerExpression<T> operator+(const T &lhs)
    {

        return InnerExpression<T>();
    }

    template <class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<std::is_base_of<parent_type, T>::value>::type>
    InnerExpression<parent_type> operator+(const parent_type &lhs)
    {

        return InnerExpression<parent_type>();
    }

    template <class parent_type = typename type_traits<T>::parent, class Child,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    InnerExpression<parent_type> operator+(const Child &lhs)
    {

        return InnerExpression<parent_type>();
    }

    template <class Child, typename = typename std::enable_if<std::is_base_of<T, Child>::value>::type>
    InnerExpression<T> operator+(const InnerExpression<Child> &lhs)
    {

        return InnerExpression<T>();
    }

    template <class parent_type, typename = typename std::enable_if<std::is_base_of<parent_type, T>::value>::type>
    InnerExpression<parent_type> operator+(const InnerExpression<parent_type> &lhs)
    {

        return InnerExpression<parent_type>();
    }

    template <class Child, class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    InnerExpression<parent_type> operator+(const InnerExpression<Child> &lhs)
    {

        return InnerExpression<parent_type>();
    }

    InnerExpression<T> operator+(const InnerExpression<T> &lhs)
    {

        return InnerExpression<T>();
    }

    using map_type = std::unordered_map<T, double, absl::Hash<T>>;
    using iterator_type = typename map_type::iterator;

  private:
};

// solves the first batch
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const T &lhs, const numeric_type &rhs)
{

    return InnerExpression<T>();
}
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const numeric_type &lhs, const T &rhs)
{

    return InnerExpression<T>();
}
// solves the second batch
template <class T> InnerExpression<T> operator+(const T &lhs, const T &rhs)
{

    return InnerExpression<T>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
InnerExpression<parent_type> operator+(const Child &lhs, const parent_type &rhs)
{

    return InnerExpression<parent_type>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
InnerExpression<parent_type> operator+(const parent_type &lhs, const Child &rhs)
{

    return InnerExpression<parent_type>();
}
template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
InnerExpression<parent_type> operator+(const Child1 &lhs, const Child2 &rhs)
{

    return InnerExpression<parent_type>();
}

// solves tenth batch
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
InnerExpression<T> operator+(const numeric_type &lhs, const InnerExpression<T> &rhs)
{

    return InnerExpression<T>();
}

// solves eleventh batch
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