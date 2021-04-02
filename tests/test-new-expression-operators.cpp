#include "symbol/Index.h"
#include "symbol/NewExpression.h"
#include "symbol/Variable.h"
#include "gtest/gtest.h"

using or2l::Index;
using or2l::InnerExpression;
using or2l::Variable;
using or2l::IndexedSymbol;
using or2l::Constant;
using or2l::VariableType;

//TEST(NewExpressionOperators, EnsureThatVariablesAreCorrectlyHashed)
//{
//    Index i("i", 0, 20);
//    Variable x("x");
//    Variable y("y", or2l::VariableType::CONTINUOUS, {i});
//    Variable z("z", or2l::VariableType::CONTINUOUS, {i});
//
//    IndexedCoefficient a;
//    IndexedCoefficient b;
//    IndexedCoefficient c;
//    IndexedCoefficient d;
//
//    a.object = x;
//    a.coefficient = 3.00;
//
//    b.object = x;
//    b.coefficient = 1.00;
//
//    c.object = y;
//    c.coefficient = 1.00;
//
//    d.object = y;
//    d.coefficient = 1.00;
//
//    std::unordered_map<IndexedCoefficient, double, absl::Hash<IndexedCoefficient>> map;
//    map[a] = a.coefficient;
//    map[b] = b.coefficient;
//    map[c] = c.coefficient;
//    map[d] = d.coefficient;
//
//    // Expects only three entries, since 'a' and 'b' variables are the same, and 'c' and 'd' differ by its name
//    ASSERT_EQ(map.size(), 3);
//}

TEST(NewExpressionOperators, InnerExpressionSum1)
{
    // two different variables (as IndexedSymbols) + a scalar (implicit InnerExpression<T>) should yield three different spots inside the map
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
    // three variables, two of them differing by their type, should yield two spots on the map, since as IndexSymbols they are the same (compares name and indexes)
    Variable a("a");
    Variable b("b", or2l::VariableType::CONTINUOUS);
    Variable c("b",or2l::VariableType::BINARY);
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
        InnerExpression<std::string>(aba) + InnerExpression<std::string>(bbb) + InnerExpression<std::string>(cdd); // if I cast it normally, it sums everything up first, since there is a default operator for std::string summation
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
    // summation of InnerExpressions
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