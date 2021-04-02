#include "symbol/Index.h"
#include "symbol/NewExpression.h"
#include "symbol/Variable.h"
#include "gtest/gtest.h"

using or2l::Constant;
using or2l::Index;
using or2l::IndexedSymbol;
using or2l::InnerExpression;
using or2l::Variable;
using or2l::VariableType;

TEST(NewExpressionOperators, InnerExpressionSum1)
{
    // two different variables (as IndexedSymbols) + a scalar (implicit InnerExpression<T>) should yield three different
    // spots inside the map
    Variable x("x");
    Variable y("y");
    auto expr = x + y + 7.00;
    ASSERT_EQ(expr[x], 1.00);
    ASSERT_EQ(expr[y], 1.00);
    ASSERT_EQ(expr[{}], 7.00);
}

TEST(NewExpressionOperators, InnerExpressionSum2)
{
    // two equal IndexedSymbols should yield one unique entry in the map
    Variable a("a");
    Variable b("a");
    auto expr = a + b;
    ASSERT_EQ(expr[a], 2.00);
    ASSERT_EQ(expr[b], 2.00);
}

TEST(NewExpressionOperators, InnerExpressionSum3)
{
    // three variables, two of them differing by their type, should yield two spots on the map, since as IndexSymbols
    // they are the same (compares name and indexes)
    Variable a("a");
    Variable b("b", or2l::VariableType::CONTINUOUS);
    Variable c("b", or2l::VariableType::BINARY);
    InnerExpression<IndexedSymbol> expr = a + b + c;
    ASSERT_EQ(expr[a], 1.00);
    ASSERT_EQ(expr[b], 2.00); // as a IndexedSymbol, both are the same
    ASSERT_EQ(expr[c], 2.00); // as a IndexedSymbol, both are the same

    InnerExpression<Variable> expr2 = a + b + c;
    ASSERT_EQ(expr2[a], 1.00);
    ASSERT_EQ(expr2[b], 1.00); // as a Variable, they are different
    ASSERT_EQ(expr2[c], 1.00); // as a Variable, they are different
}

TEST(NewExpressionOperators, InnerExpressionSum4)
{
    // considering that an IndexedSymbol is the parent of Variable and Constant, an sum between the two should be viable
    Variable a("a");
    Constant b("b");
    auto expr = a + b;
    ASSERT_EQ(expr[a], 1.00);
    ASSERT_EQ(expr[b], 1.00);
}

TEST(NewExpressionOperators, InnerExpressionSum5)
{
    // doing operations with random classes - string works, char converts to int (which does not work)
    std::string aba = "aba";
    std::string bbb = "bbb";
    std::string cdd = "bbb";
    InnerExpression<std::string> expr =
        InnerExpression<std::string>(aba) + InnerExpression<std::string>(bbb) +
        InnerExpression<std::string>(cdd); // if I cast it normally, it sums everything up first, since there is a
                                           // default operator for std::string summation
    ASSERT_EQ(expr[aba], 1.00);
    ASSERT_EQ(expr[bbb], 2.00);
    ASSERT_EQ(expr[cdd], 2.00);
    // there are many things to work (and learn) in terms of templates and good practices
}

TEST(NewExpressionOperators, InnerExpressionSum6)
{
    // summation of InnerExpressions
    Index i("i", 0, 20);
    Index j("j", 0, 6);
    Variable x("x", VariableType::INTEGER, {i, j});
    Variable y("y", VariableType::CONTINUOUS, {j});

    auto expr = x + x + y + y + y + 14.3;
    auto expr2 = x + x + 5.7;
    auto expr3 = expr + expr2;
    ASSERT_EQ(expr3[x], 4);
    ASSERT_EQ(expr3[y], 3);
    ASSERT_EQ(expr3[{}], 20.0);
}

TEST(NewExpressionOperators, InnerExpressionSum7)
{
    // summation of Indexes - this is important for the future
    Index i("i", 0, 20);
    Index j("j", 0, 6);
    Index k("k", 0, 10);
    Index l("k", 0, 10);

    auto expr = i + j + k + l + 7.29358239852348753489089089493492344;
    ASSERT_EQ(expr[i], 1.00);
    ASSERT_EQ(expr[j], 1.00);
    ASSERT_EQ(expr[k], 2.00);
    ASSERT_EQ(expr[l], 2.00);
    ASSERT_EQ(expr[{}], 7.29358239852348753489089089493492344);
}

TEST(NewExpressionOperators, InnerExpressionSum8)
{
    // extra tests with the base_types class... Bounds did not work since there is a is_class restriction on the
    // definition (that does not warn the user about its existence)
    InnerExpression<base_types::RegexString> expr =
        InnerExpression<base_types::RegexString>{"a"} + InnerExpression<base_types::RegexString>{"b"} +
        InnerExpression<base_types::RegexString>{"c"} + InnerExpression<base_types::RegexString>{"d"} +
        InnerExpression<base_types::RegexString>{"d"};

    ASSERT_EQ(expr["a"], 1.00);
    ASSERT_EQ(expr["b"], 1.00);
    ASSERT_EQ(expr["c"], 1.00);
    ASSERT_EQ(expr["d"], 2.00);
    ASSERT_EQ(expr[""], 0.0);
}

TEST(NewExpressionOperators, InnerExpressionSum9)
{
    // summation of InnerExpressions with different template types (one is base of another). This is also another
    // important test
    Index i("i", 0, 1000);
    Index j("j", 6, 600);

    Variable x("x", VariableType::CONTINUOUS, {i, j});
    Variable y("y", VariableType::BINARY, {i, j});
    Constant c("c", {j});
    const double scalar = 556.44;

    auto expr_var = x + y + scalar;
    auto expr_symbol = c + y + 443.56;
    auto expr_mix = expr_symbol + expr_var;
    auto expr_mix2 = expr_var + expr_symbol;

    ASSERT_EQ(expr_mix, expr_mix2);
    ASSERT_EQ(expr_mix[x], 1.00);
    ASSERT_EQ(expr_mix[y], 2.00);
    ASSERT_EQ(expr_mix[c], 1.00);
    ASSERT_EQ(expr_mix[{}], 1000.00);
}
//
// TEST(NewExpressionOperators, ExpandedExpressionTests1)
//{
//    Index i("i", 0, 20);
//    Index j("j", 0, 10);
//    Variable x("x", or2l::VariableType::CONTINUOUS, {i, j});
//    Variable y("y", or2l::VariableType::CONTINUOUS, {i});
//
//    ExpandedExpression<IndexedCoefficient> exp_expr1(ExpressionOperatorType::SUMMATION, x + y + 1, {i, j});
//    ExpandedExpression<IndexedCoefficient> exp_expr2(ExpressionOperatorType::SUMMATION, y + x + 1, {i, j});
//    ExpandedExpression<IndexedCoefficient> exp_expr3(ExpressionOperatorType::SUMMATION, x, {i, j});
//
//    auto test1 = exp_expr1 + exp_expr2 + exp_expr3;
//    ASSERT_EQ(test1.GetExpandableExpressionCoeff(exp_expr1), 2.00);
//    ASSERT_EQ(test1.GetExpandableExpressionCoeff(exp_expr3), 1.00);
//    ASSERT_EQ(test1.GetExpandableExpressionCoeff({}), 0.00);
//    ASSERT_EQ(test1[y], 0.00);
//    ASSERT_EQ(test1[x], 0.00);
//    ASSERT_EQ(test1[{}], 0.00);
//}
//
// TEST(NewExpressionOperators, NewExpressionTest)
//{
//    Index i("i", 0, 3);
//    Index j("j", 0, 6);
//    Variable x("x", or2l::VariableType::CONTINUOUS, {i, j});
//    Variable y("y", or2l::VariableType::CONTINUOUS, {i});
//
//    NewExpression<IndexedCoefficient> expr1(x + y);
//    NewExpression<IndexedCoefficient> expr2(7.00 + x);
//    NewExpression<IndexedCoefficient> expr3(y + y + y + x + 3.00);
//    ExpandedExpression<IndexedCoefficient> expr4(ExpressionOperatorType::SUMMATION, x, {i, j});
//    ExpandedExpression<IndexedCoefficient> expr5(ExpressionOperatorType::SUMMATION, x, {i, j});
//    ExpandedExpression<IndexedCoefficient> expr6(ExpressionOperatorType::SUMMATION, x + y, {i, j});
//
//    auto test1 = expr1 + expr2 + expr3 + expr4 + expr5 + expr6;
//
//    ASSERT_EQ(test1[x], 3.00);
//    ASSERT_EQ(test1[y], 4.00);
//    ASSERT_EQ(test1[{}], 10.00);
//    ASSERT_EQ(test1.GetExpandableExpressionCoeff(expr4), 2.00);
//    ASSERT_EQ(test1.GetExpandableExpressionCoeff(expr5), 2.00);
//    ASSERT_EQ(test1.GetExpandableExpressionCoeff(expr6), 1.00);
//
//    //auto test1 = expr1 + expr2 + expr3 + expr4 + x + y + 5.00;
//}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}