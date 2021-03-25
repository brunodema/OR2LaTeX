#include "symbol/Expression.h"
#include "symbol/Index.h"
#include "symbol/Variable.h"
#include "gtest/gtest.h"

using or2l::ExpressionCoefficient;
using or2l::Index;
using or2l::Variable;

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
    auto test3 = a + d;
    auto test4 = a + b + c + d;

    ASSERT_EQ(test1[x], 4.50);

    ASSERT_EQ(test2[x], 3.50);
    ASSERT_EQ(test2[y], 1.00);

    ASSERT_EQ(test3[x], 3.50);
    ASSERT_EQ(test3[{}], 7.00);

    ASSERT_EQ(test4[x], 4.50);
    ASSERT_EQ(test4[y], 1.00);
    ASSERT_EQ(test4[{}], 7.00);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}