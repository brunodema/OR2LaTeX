#include "symbol/Index.h"
#include "symbol/NewExpression.h"
#include "symbol/Variable.h"
#include "gtest/gtest.h"

#define INFO(msg)

// #define INFO(msg) fprintf(stderr, "info: %s:%d: %s\n", __FILE__, __LINE__,
// __PRETTY_FUNCTION__);

class Symb
{
  public:
    Symb() = default;
};

class Random
{
  public:
    Random() = default;
};

class Vari : public Symb
{
  public:
    Vari() = default;
};

class Cons : public Symb
{
  public:
    Cons() = default;
};

template <class T> struct type_traits
{
    using parent = void;
};
template <> struct type_traits<Vari>
{
    using parent = Symb;
};
template <> struct type_traits<Cons>
{
    using parent = Symb;
};
// template <> struct type_traits<Random> { using parent = Symb; };

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

template <class T> class IE
{
  public:
    IE() = default;
    // solves seventh batch
    // IE(const T &obj);

    // solves fifth batch
    template <class numeric_type, typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
    IE<T> operator+(const numeric_type &lhs)
    {
        INFO("");
        return IE<T>();
    }
    IE<T> operator+(const T &lhs)
    {
        INFO("");
        return IE<T>();
    }
    // solves sixth batch
    template <class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<std::is_base_of<parent_type, T>::value>::type>
    IE<parent_type> operator+(const parent_type &lhs)
    {
        INFO("");
        return IE<parent_type>();
    }
    template <class parent_type = typename type_traits<T>::parent, class Child,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    IE<parent_type> operator+(const Child &lhs)
    {
        INFO("");
        return IE<parent_type>();
    }
    // solves eighth batch
    template <class Child, typename = typename std::enable_if<std::is_base_of<T, Child>::value>::type>
    IE<T> operator+(const IE<Child> &lhs)
    {
        INFO("");
        return IE<T>();
    }
    template <class parent_type, typename = typename std::enable_if<std::is_base_of<parent_type, T>::value>::type>
    IE<parent_type> operator+(const IE<parent_type> &lhs)
    {
        INFO("");
        return IE<parent_type>();
    }
    template <class Child, class parent_type = typename type_traits<T>::parent,
              typename = typename std::enable_if<inheritance_traits<T, Child>::has_same_parent()>::type>
    IE<parent_type> operator+(const IE<Child> &lhs)
    {
        INFO("");
        return IE<parent_type>();
    }
    // solves ninth batch
    IE<T> operator+(const IE<T> &lhs)
    {
        INFO("");
        return IE<T>();
    }
};

// solves the first batch
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
IE<T> operator+(const T &lhs, const numeric_type &rhs)
{
    INFO("");
    return IE<T>();
}
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
IE<T> operator+(const numeric_type &lhs, const T &rhs)
{
    INFO("");
    return IE<T>();
}
// solves the second batch
template <class T> IE<T> operator+(const T &lhs, const T &rhs)
{
    INFO("");
    return IE<T>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
IE<parent_type> operator+(const Child &lhs, const parent_type &rhs)
{
    INFO("");
    return IE<parent_type>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
IE<parent_type> operator+(const parent_type &lhs, const Child &rhs)
{
    INFO("");
    return IE<parent_type>();
}
template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
IE<parent_type> operator+(const Child1 &lhs, const Child2 &rhs)
{
    INFO("");
    return IE<parent_type>();
}

// solves tenth batch
template <class T, class numeric_type,
          typename = typename std::enable_if<std::is_arithmetic<numeric_type>::value>::type>
IE<T> operator+(const numeric_type &lhs, const IE<T> &rhs)
{
    INFO("");
    return IE<T>();
}

// solves eleventh batch
template <class T> IE<T> operator+(const T &lhs, const IE<T> &rhs)
{
    INFO("");
    return IE<T>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
IE<parent_type> operator+(const Child &lhs, const IE<parent_type> &rhs)
{
    INFO("");
    return IE<parent_type>();
}
template <class Child, class parent_type = typename type_traits<Child>::parent,
          typename = typename std::enable_if<std::is_base_of<parent_type, Child>::value>::type>
IE<parent_type> operator+(const parent_type &lhs, const IE<Child> &rhs)
{
    INFO("");
    return IE<parent_type>();
}
template <class Child1, class Child2, class parent_type = typename type_traits<Child1>::parent,
          typename = typename std::enable_if<inheritance_traits<Child1, Child2>::has_same_parent()>::type>
IE<parent_type> operator+(const Child1 &lhs, const IE<Child2> &rhs)
{
    INFO("");
    return IE<parent_type>();
}

const Random r;
const Symb s;
const Vari v;
const Cons c;

TEST(test, t1)
{

    // first batch
    auto expr1 = 1 + v;
    auto expr2 = 1.00 + s;
    auto expr3 = 1.00000000000000 + r;
    auto expr4 = v + 1;
    auto expr5 = s + 1.00;
    auto expr6 = r + 1.00000000000000;
}
TEST(test, t2)
{

    // second batch
    auto expr1 = v + v;
    auto expr2 = v + s;
    auto expr3 = v + c;
    auto expr4 = c + c;
    auto expr5 = s + v;
    auto expr6 = c + v;
}
TEST(test, t3)
{
    // third batch (automatically passes)
    auto expr1 = 1 + v + 1.00;
    auto expr2 = 1.00 + s + 1.000000000;
    auto expr3 = 1.00000000000000 + r + 1;
    auto expr4 = v + 1 + 1.00;
    auto expr5 = s + 1.00 + 1.000000000;
    auto expr6 = r + 1.00000000000000 + 1;
}
TEST(test, t4)
{
    // fourth batch (automatically passes)
    auto expr1 = v + v + 1;
    auto expr2 = v + s + 1.00;
    auto expr3 = v + c + 1.0000000;
    auto expr4 = c + c + 1.0000000;
    auto expr5 = s + v + 1.00;
    auto expr6 = c + v + 1;
}

TEST(test, t5)
{
    // fifth batch
    auto expr1 = v + v + 1 + v;
    auto expr2 = v + s + 1.00 + v;
    auto expr3 = v + c + 1.0000000 + v;
    auto expr4 = c + c + 1.0000000 + c;
    auto expr5 = s + v + 1.00 + s;
    auto expr6 = c + v + 1 + c;
}

TEST(test, t6)
{
    // sixth batch
    auto expr1 = 1 + c + s + v + 1;
    auto expr2 = 1 + s + c + v + 1;
    auto expr3 = 1.0000 + c + 1 + s + 1.00 + v + 1;
    auto expr4 = 1.0000 + 1 + s + c + 1.00 + v + 1;
    auto expr5 = v + v + c + c + s + s;
    auto expr6 = c + c + s + s + v + v;
    auto expr7 = s + s + c + c + v + v + 1.0000 + 1.00 + 1;
}

TEST(test, t7)
{
    // seventh batch
    IE<Random> expr1 = 1 + r + 1;
    IE<Symb> expr2 = 1 + s + 1;
    IE<Cons> expr3 = 1 + c + 1;
    IE<Vari> expr4 = 1 + v + 1;
}

TEST(test, t8)
{
    // eighth batch
    IE<Random> expr1 = 1 + r + 1;
    IE<Symb> expr2 = 1 + s + 1;
    IE<Cons> expr3 = 1 + c + 1;
    IE<Vari> expr4 = 1 + v + 1;

    // the first three can not compile, since the types are not compatible
    // auto expr5 = expr1 + expr2;
    // auto expr6 = expr1 + expr3;
    // auto expr7 = expr1 + expr4;

    auto expr8 = expr2 + expr3;
    auto expr9 = expr2 + expr4;
    auto expr10 = expr3 + expr4;

    auto expr11 = expr2 + 1 + expr3 + v;
    auto expr12 = expr2 + 1.0000 + expr4 + c;
    auto expr13 = expr3 + 'a' + expr4 + s;
    auto expr14 = expr3 + expr2;
    auto expr15 = expr4 + expr2;
}
TEST(test, t9)
{
    // ninth batch
    IE<Random> expr1 = r + 1;
    IE<Symb> expr2 = 1 + s;
    IE<Cons> expr3 = c + 1;
    IE<Vari> expr4 = v + v;

    auto expr5 = /*expr1* +*/ expr2 + expr3 + expr4;
    auto expr6 = expr4 + expr3 + expr2;
    auto expr7 = expr2 + expr4 + expr3;
    auto expr8 = expr3 + expr4 + expr2;
    auto expr9 = expr3 + expr2 + expr4;
    auto expr10 = expr4 + expr2 + expr3;
}
TEST(test, t10)
{
    // tenth batch
    IE<Random> expr1 = r + 1;
    IE<Symb> expr2 = 1 + s;
    IE<Cons> expr3 = c + 1;
    IE<Vari> expr4 = v + v;

    auto expr5 = /*expr1* +*/ expr2 + expr3 + expr4 + 1;
    auto expr6 = 1 + expr4 + expr3 + expr2;
    auto expr7 = expr2 + 1 + expr4 + 1 + expr3;
    auto expr8 = 1 + expr3 + expr4 + expr2 + 1;
    auto expr9 = 1 + expr3 + 1.000 + expr2 + 'b' + expr4 + 1;
    auto expr10 = expr1 + expr1;
    auto expr11 = expr2 + 1;
    auto expr12 = 1 + expr3;
}
TEST(test, t11)
{
    // eleventh batch
    IE<Random> expr1 = r + 1;
    IE<Symb> expr2 = 1 + s;
    IE<Cons> expr3 = c + 1;
    IE<Vari> expr4 = v + v;

    auto expr5 = r + expr1;
    auto expr6 = s + expr2;
    auto expr7 = c + expr3;
    auto expr8 = v + expr4;

    auto expr9 = expr1 + r;
    auto expr10 = expr2 + s;
    auto expr11 = expr3 + c;
    auto expr12 = expr4 + v;
}
TEST(test, t12)
{
    // twelveth batch
    IE<Random> expr1 = r + 1;
    IE<Symb> expr2 = 1 + s;
    IE<Cons> expr3 = c + 1;
    IE<Vari> expr4 = v + v;

    auto expr5 = r + expr1 + r;

    auto expr6 = s + expr2 + v;
    auto expr7 = v + expr2 + s;
    auto expr8 = v + expr3 + s;
    auto expr9 = s + expr3 + v;
    auto expr10 = v + expr4 + s;
    auto expr11 = s + expr4 + v;

    auto expr16 = 1 + s + 1 + expr2 + 1 + c + v;
    auto expr17 = c + 1 + v + expr2 + 1 + s + 1;
    auto expr18 = 1 + s + 1 + expr3 + 1 + c + v;
    auto expr19 = c + 1 + v + expr4 + 1 + s + 1;
}
TEST(test, t13)
{
    // thirteenth batch (automatically passes)
    IE<Random> expr1 = r + 1;
    IE<Symb> expr2 = 1 + s;
    IE<Cons> expr3 = c + 1;
    IE<Vari> expr4 = v + v;

    auto expr5 = expr2 + expr2;
    auto expr6 = expr2 + expr3;
    auto expr7 = expr3 + expr2;
    auto expr8 = expr2 + expr4;
    auto expr9 = expr4 + expr2;
}
TEST(test, t14)
{
    // fourteenth batch (automatically passes)
    IE<Random> expr1 = r + 1;
    IE<Symb> expr2 = 1 + s;
    IE<Cons> expr3 = c + 1;
    IE<Vari> expr4 = v + v;

    auto expr5 = 1.000 + r + 1 + expr1 + 1;
    auto expr6 = expr1 + 1 + r + r + expr1;
    auto expr7 = 1.00 + expr2 + expr2 + s;
    auto expr8 = expr2 + s + expr2 + c + v;
    auto expr9 = v + c + expr2 + s + expr2;
    auto expr10 = expr2 + 1.00 + c + 1 + v + expr3 + s + 1 + expr4 + s + v + 'a' + c + 1.000;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}