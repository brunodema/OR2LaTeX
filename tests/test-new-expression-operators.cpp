#include "symbol/Index.h"
#include "symbol/NewExpression.h"
#include "symbol/Variable.h"
#include "gtest/gtest.h"

using or2l::ExpandedExpression;
using or2l::ExpressionCoefficient;
using or2l::Index;
using or2l::InnerExpression;
using or2l::NewExpression;
using or2l::Variable;
using or2l::operators::ExpressionOperatorType;

TEST(NewExpressionOperators, EnsureThatVariablesAreCorrectlyHashed)
{
    Index i("i", 0, 20);
    Variable x("x");
    Variable y("y", or2l::VariableType::CONTINUOUS, {i});
    Variable z("z", or2l::VariableType::CONTINUOUS, {i});

    ExpressionCoefficient a;
    ExpressionCoefficient b;
    ExpressionCoefficient c;
    ExpressionCoefficient d;

    a.variable = x;
    a.coefficient = 3.00;

    b.variable = x;
    b.coefficient = 1.00;

    c.variable = y;
    c.coefficient = 1.00;

    d.variable = z;
    d.coefficient = 1.00;

    std::unordered_map<Variable, double, absl::Hash<Variable>> map;
    map[a.variable] = a.coefficient;
    map[b.variable] = b.coefficient;
    map[c.variable] = c.coefficient;
    map[d.variable] = d.coefficient;

    // Expects only three entries, since 'a' and 'b' variables are the same, and 'c' and 'd' differ by its name
    ASSERT_EQ(map.size(), 3);
}

TEST(NewExpressionOperators, InnerExpressionSumOperators)
{
    Variable x("x");
    Variable y("y");

    ExpressionCoefficient a(3.50, x);
    ExpressionCoefficient b(1.00, x);
    ExpressionCoefficient c(y);
    ExpressionCoefficient d(7.00);

    auto test1 = a + b;
    auto test2 = a + c;
    auto test3 = a + d + 11.25;
    auto test4 = a + b + c + d;

    ASSERT_EQ(test1[x], 4.50);

    ASSERT_EQ(test2[x], 3.50);
    ASSERT_EQ(test2[y], 1.00);

    ASSERT_EQ(test3[x], 3.50);
    ASSERT_EQ(test3[{}], 18.25);

    ASSERT_EQ(test4[x], 4.50);
    ASSERT_EQ(test4[y], 1.00);
    ASSERT_EQ(test4[{}], 7.00);

    InnerExpression inner1(x + y + 60);
    InnerExpression inner2(y + 30);
    auto test5 = inner1 + inner2;
    ASSERT_EQ(test5[x], 1.00);
    ASSERT_EQ(test5[y], 2.00);
    ASSERT_EQ(test5[{}], 90.00);
}

TEST(NewExpressionOperators, ExpandedExpressionTests1)
{
    Index i("i", 0, 20);
    Index j("j", 0, 10);
    Variable x("x", or2l::VariableType::CONTINUOUS, {i, j});
    Variable y("y", or2l::VariableType::CONTINUOUS, {i});

    ExpandedExpression exp_expr1(ExpressionOperatorType::SUMMATION, x + y + 1, {i, j});
    ExpandedExpression exp_expr2(ExpressionOperatorType::SUMMATION, y + x + 1, {i, j});
    ExpandedExpression exp_expr3(ExpressionOperatorType::SUMMATION, x, {i, j});

    auto test1 = exp_expr1 + exp_expr2 + exp_expr3;
    ASSERT_EQ(test1.GetExpandableExpressionCoeff(exp_expr1), 2.00);
    ASSERT_EQ(test1.GetExpandableExpressionCoeff(exp_expr3), 1.00);
    ASSERT_EQ(test1.GetExpandableExpressionCoeff({}), 0.00);
    ASSERT_EQ(test1[y], 0.00);
    ASSERT_EQ(test1[x], 0.00);
    ASSERT_EQ(test1[{}], 0.00);
}

TEST(NewExpressionOperators, NewExpressionTest)
{
    Index i("i", 0, 3);
    Index j("j", 0, 6);
    Variable x("x", or2l::VariableType::CONTINUOUS, {i, j});
    Variable y("y", or2l::VariableType::CONTINUOUS, {i});

    NewExpression expr1(x + y);
    NewExpression expr2(7.00 + x);
    NewExpression expr3(y + y + y + x + 3.00);
    ExpandedExpression expr4(ExpressionOperatorType::SUMMATION, x, {i, j});
    ExpandedExpression expr5(ExpressionOperatorType::SUMMATION, x, {i, j});
    ExpandedExpression expr6(ExpressionOperatorType::SUMMATION, x + y, {i, j});

    auto test1 = expr1 + expr2 + expr3 + expr4 + expr5 + expr6;

    ASSERT_EQ(test1[x], 3.00);
    ASSERT_EQ(test1[y], 4.00);
    ASSERT_EQ(test1[{}], 10.00);
    ASSERT_EQ(test1.GetExpandableExpressionCoeff(expr4), 2.00);
    ASSERT_EQ(test1.GetExpandableExpressionCoeff(expr5), 2.00);
    ASSERT_EQ(test1.GetExpandableExpressionCoeff(expr6), 1.00);

    //auto test1 = expr1 + expr2 + expr3 + expr4 + x + y + 5.00;
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}