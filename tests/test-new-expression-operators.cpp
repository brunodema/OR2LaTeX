#include "symbol/Index.h"
#include "symbol/InnerExpression.h"
#include "symbol/Variable.h"
#include "gtest/gtest.h"

using or2l::Constant;
using or2l::Index;
using or2l::IndexedSymbol;
using or2l::Variable;

const static or2l::Index r("r", 0, 20);
const static or2l::IndexedSymbol s("s", or2l::SymbolType::UNKNOWN, {});
const static or2l::Constant c("c", {r});
const static or2l::Variable v("v", or2l::VariableType::BINARY);

TEST(test, t1)
{

    auto expr1 = 1 + v;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 1.00);
    ASSERT_EQ(expr1[v], 1.00);
    auto expr2 = 1.00 + s;
    ASSERT_EQ(expr2.GetSize(), 2);
    ASSERT_EQ(expr2[{}], 1.00);
    ASSERT_EQ(expr2[s], 1.00);
    auto expr3 = 1.00000000000000 + r;
    ASSERT_EQ(expr3.GetSize(), 2);
    ASSERT_EQ(expr3[{}], 1.00);
    ASSERT_EQ(expr3[r], 1.00);
    auto expr4 = v + 1;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 1.00);
    ASSERT_EQ(expr4[v], 1.00);
    auto expr5 = s + 1.00;
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 1.00);
    ASSERT_EQ(expr5[s], 1.00);
    auto expr6 = r + 1.00000000000000;
    ASSERT_EQ(expr6.GetSize(), 2);
    ASSERT_EQ(expr6[{}], 1.00);
    ASSERT_EQ(expr6[r], 1.00);
}
TEST(test, t2)
{
    auto expr1 = v + v;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 0.00);
    ASSERT_EQ(expr1[v], 2.00);
    auto expr2 = v + s;
    ASSERT_EQ(expr2.GetSize(), 3);
    ASSERT_EQ(expr2[{}], 0.00);
    ASSERT_EQ(expr2[v], 1.00);
    ASSERT_EQ(expr2[s], 1.00);
    auto expr3 = v + c;
    ASSERT_EQ(expr3.GetSize(), 3);
    ASSERT_EQ(expr3[{}], 0.00);
    ASSERT_EQ(expr3[v], 1.00);
    ASSERT_EQ(expr3[c], 1.00);
    auto expr4 = c + c;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 0.00);
    ASSERT_EQ(expr4[c], 2.00);
    auto expr5 = s + v;
    ASSERT_EQ(expr5.GetSize(), 3);
    ASSERT_EQ(expr5[{}], 0.00);
    ASSERT_EQ(expr5[v], 1.00);
    ASSERT_EQ(expr5[s], 1.00);
    auto expr6 = c + v;
    ASSERT_EQ(expr6.GetSize(), 3);
    ASSERT_EQ(expr6[{}], 0.00);
    ASSERT_EQ(expr6[v], 1.00);
    ASSERT_EQ(expr6[c], 1.00);
}
TEST(test, t3)
{
    auto expr1 = 1 + v + 1.00;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 2.00);
    ASSERT_EQ(expr1[v], 1.00);
    auto expr2 = 1.00 + s + 1.000000000;
    ASSERT_EQ(expr2.GetSize(), 2);
    ASSERT_EQ(expr2[{}], 2.00);
    ASSERT_EQ(expr2[s], 1.00);
    auto expr3 = 1.00000000000000 + r + 1;
    ASSERT_EQ(expr3.GetSize(), 2);
    ASSERT_EQ(expr3[{}], 2.00);
    ASSERT_EQ(expr3[r], 1.00);
    auto expr4 = v + 1 + 1.00;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 2.00);
    ASSERT_EQ(expr4[v], 1.00);
    auto expr5 = s + 1.00 + 1.000000000;
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 2.00);
    ASSERT_EQ(expr5[s], 1.00);
    auto expr6 = r + 1.00000000000000 + 1;
    ASSERT_EQ(expr6.GetSize(), 2);
    ASSERT_EQ(expr6[{}], 2.00);
    ASSERT_EQ(expr6[r], 1.00);
}
TEST(test, t4)
{
    auto expr1 = v + v + 1;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 1.00);
    ASSERT_EQ(expr1[v], 2.00);
    auto expr2 = v + s + 1.00;
    ASSERT_EQ(expr2.GetSize(), 3);
    ASSERT_EQ(expr2[{}], 1.00);
    ASSERT_EQ(expr2[v], 1.00);
    ASSERT_EQ(expr2[s], 1.00);
    auto expr3 = v + c + 1.0000000;
    ASSERT_EQ(expr3.GetSize(), 3);
    ASSERT_EQ(expr3[{}], 1.00);
    ASSERT_EQ(expr3[v], 1.00);
    ASSERT_EQ(expr3[c], 1.00);
    auto expr4 = c + c + 1.0000000;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 1.00);
    ASSERT_EQ(expr4[c], 2.00);
    auto expr5 = s + v + 1.00;
    ASSERT_EQ(expr5.GetSize(), 3);
    ASSERT_EQ(expr5[{}], 1.00);
    ASSERT_EQ(expr5[v], 1.00);
    ASSERT_EQ(expr5[s], 1.00);
    auto expr6 = c + v + 1;
    ASSERT_EQ(expr6.GetSize(), 3);
    ASSERT_EQ(expr6[{}], 1.00);
    ASSERT_EQ(expr6[v], 1.00);
    ASSERT_EQ(expr6[c], 1.00);
}
TEST(test, t5)
{
    auto expr1 = v + v + 1 + v;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 1.00);
    ASSERT_EQ(expr1[v], 3.00);
    auto expr2 = v + s + 1.00 + v;
    ASSERT_EQ(expr2.GetSize(), 3);
    ASSERT_EQ(expr2[{}], 1.00);
    ASSERT_EQ(expr2[v], 2.00);
    ASSERT_EQ(expr2[s], 1.00);
    auto expr3 = v + c + 1.0000000 + v;
    ASSERT_EQ(expr3.GetSize(), 3);
    ASSERT_EQ(expr3[{}], 1.00);
    ASSERT_EQ(expr3[v], 2.00);
    ASSERT_EQ(expr3[c], 1.00);
    auto expr4 = c + c + 1.0000000 + c;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 1.00);
    ASSERT_EQ(expr4[c], 3.00);
    auto expr5 = s + v + 1.00 + s;
    ASSERT_EQ(expr5.GetSize(), 3);
    ASSERT_EQ(expr5[{}], 1.00);
    ASSERT_EQ(expr5[s], 2.00);
    ASSERT_EQ(expr5[v], 1.00);
    auto expr6 = c + v + 1 + c;
    ASSERT_EQ(expr6.GetSize(), 3);
    ASSERT_EQ(expr6[{}], 1.00);
    ASSERT_EQ(expr6[c], 2.00);
    ASSERT_EQ(expr6[v], 1.00);
}
TEST(test, t6)
{
    // sixth batch
    auto expr1 = 1 + c + s + v + 1;
    ASSERT_EQ(expr1.GetSize(), 4);
    ASSERT_EQ(expr1[{}], 2.00);
    ASSERT_EQ(expr1[c], 1.00);
    ASSERT_EQ(expr1[v], 1.00);
    ASSERT_EQ(expr1[s], 1.00);
    auto expr2 = 1 + s + c + v + 1;
    ASSERT_EQ(expr2.GetSize(), 4);
    ASSERT_EQ(expr2[{}], 2.00);
    ASSERT_EQ(expr2[c], 1.00);
    ASSERT_EQ(expr2[v], 1.00);
    ASSERT_EQ(expr2[s], 1.00);
    auto expr3 = 1.0000 + c + 1 + s + 1.00 + v + 1;
    ASSERT_EQ(expr3.GetSize(), 4);
    ASSERT_EQ(expr3[{}], 4.00);
    ASSERT_EQ(expr3[c], 1.00);
    ASSERT_EQ(expr3[v], 1.00);
    ASSERT_EQ(expr3[s], 1.00);
    auto expr4 = 1.0000 + 1 + s + c + 1.00 + v + 1;
    ASSERT_EQ(expr4.GetSize(), 4);
    ASSERT_EQ(expr4[{}], 4.00);
    ASSERT_EQ(expr4[c], 1.00);
    ASSERT_EQ(expr4[v], 1.00);
    ASSERT_EQ(expr4[s], 1.00);
    auto expr5 = v + v + c + c + s + s; // casting problem here
    ASSERT_EQ(expr5.GetSize(), 4);
    ASSERT_EQ(expr5[{}], 0.00);
    ASSERT_EQ(expr5[c], 2.00);
    ASSERT_EQ(expr5[v], 2.00);
    ASSERT_EQ(expr5[s], 2.00);
    auto expr6 = c + c + s + s + v + v;
    ASSERT_EQ(expr6.GetSize(), 4);
    ASSERT_EQ(expr6[{}], 0.00);
    ASSERT_EQ(expr6[c], 2.00);
    ASSERT_EQ(expr6[v], 2.00);
    ASSERT_EQ(expr6[s], 2.00);
    auto expr7 = s + s + c + c + v + v + 1.0000 + 1.00 + 1;
    ASSERT_EQ(expr7.GetSize(), 4);
    ASSERT_EQ(expr7[{}], 3.00);
    ASSERT_EQ(expr7[c], 2.00);
    ASSERT_EQ(expr7[v], 2.00);
    ASSERT_EQ(expr7[s], 2.00);
}
TEST(test, t7)
{
    InnerExpression<Index> expr1 = 1 + r + 1;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 2.00);
    ASSERT_EQ(expr1[r], 1.00);
    InnerExpression<IndexedSymbol> expr2 = 1 + s + 1;
    ASSERT_EQ(expr2.GetSize(), 2);
    ASSERT_EQ(expr2[{}], 2.00);
    ASSERT_EQ(expr2[s], 1.00);
    InnerExpression<Constant> expr3 = 1 + c + 1;
    ASSERT_EQ(expr3.GetSize(), 2);
    ASSERT_EQ(expr3[{}], 2.00);
    ASSERT_EQ(expr3[c], 1.00);
    InnerExpression<Variable> expr4 = 1 + v + 1;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 2.00);
    ASSERT_EQ(expr4[v], 1.00);
}
TEST(test, t8)
{
    InnerExpression<Index> expr1 = 1 + r + 1;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 2.00);
    ASSERT_EQ(expr1[r], 1.00);
    InnerExpression<IndexedSymbol> expr2 = 1 + s + 1;
    ASSERT_EQ(expr2.GetSize(), 2);
    ASSERT_EQ(expr2[{}], 2.00);
    ASSERT_EQ(expr2[s], 1.00);
    InnerExpression<Constant> expr3 = 1 + c + 1;
    ASSERT_EQ(expr3.GetSize(), 2);
    ASSERT_EQ(expr3[{}], 2.00);
    ASSERT_EQ(expr3[c], 1.00);
    InnerExpression<Variable> expr4 = 1 + v + 1;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 2.00);
    ASSERT_EQ(expr4[v], 1.00);

    // the first three can not compile, since the types are not compatible
    // auto expr5 = expr1 + expr2;
    // auto expr6 = expr1 + expr3;
    // auto expr7 = expr1 + expr4;

    auto expr8 = expr2 + expr3;
    ASSERT_EQ(expr8.GetSize(), 3);
    ASSERT_EQ(expr8[{}], 4.00);
    ASSERT_EQ(expr8[s], 1.00);
    ASSERT_EQ(expr8[c], 1.00);
    auto expr9 = expr2 + expr4;
    ASSERT_EQ(expr9.GetSize(), 3);
    ASSERT_EQ(expr9[{}], 4.00);
    ASSERT_EQ(expr9[s], 1.00);
    ASSERT_EQ(expr9[v], 1.00);
    auto expr10 = expr3 + expr4;
    ASSERT_EQ(expr10.GetSize(), 3);
    ASSERT_EQ(expr10[{}], 4.00);
    ASSERT_EQ(expr10[v], 1.00);
    ASSERT_EQ(expr10[c], 1.00);

    auto expr11 = expr2 + 1 + expr3 + v;
    ASSERT_EQ(expr11.GetSize(), 4);
    ASSERT_EQ(expr11[{}], 5.00);
    ASSERT_EQ(expr11[s], 1.00);
    ASSERT_EQ(expr11[c], 1.00);
    ASSERT_EQ(expr11[v], 1.00);
    auto expr12 = expr2 + 1.0000 + expr4 + c;
    ASSERT_EQ(expr12.GetSize(), 4);
    ASSERT_EQ(expr12[{}], 5.00);
    ASSERT_EQ(expr12[s], 1.00);
    ASSERT_EQ(expr12[c], 1.00);
    ASSERT_EQ(expr12[v], 1.00);
    auto expr13 = expr3 + 'a' + expr4 + s;
    ASSERT_EQ(expr13.GetSize(), 4);
    ASSERT_EQ(expr13[{}], 101.00);
    ASSERT_EQ(expr13[s], 1.00);
    ASSERT_EQ(expr13[c], 1.00);
    ASSERT_EQ(expr13[v], 1.00);
    auto expr14 = expr3 + expr2;
    ASSERT_EQ(expr14.GetSize(), 3);
    ASSERT_EQ(expr14[{}], 4.00);
    ASSERT_EQ(expr14[s], 1.00);
    ASSERT_EQ(expr14[c], 1.00);
    auto expr15 = expr4 + expr2;
    ASSERT_EQ(expr15.GetSize(), 3);
    ASSERT_EQ(expr15[{}], 4.00);
    ASSERT_EQ(expr15[s], 1.00);
    ASSERT_EQ(expr15[v], 1.00);
}
TEST(test, t9)
{
    // won't bother testing this base declarations
    InnerExpression<Index> expr1 = r + 1;
    InnerExpression<IndexedSymbol> expr2 = 1 + s;
    InnerExpression<Constant> expr3 = c + 1;
    InnerExpression<Variable> expr4 = v + v;

    auto expr5 = /*expr1* +*/ expr2 + expr3 + expr4;
    ASSERT_EQ(expr5.GetSize(), 4);
    ASSERT_EQ(expr5[{}], 2.00);
    ASSERT_EQ(expr5[s], 1.00);
    ASSERT_EQ(expr5[c], 1.00);
    ASSERT_EQ(expr5[v], 2.00);
    auto expr6 = expr4 + expr3 + expr2;
    ASSERT_EQ(expr6.GetSize(), 4);
    ASSERT_EQ(expr6[{}], 2.00);
    ASSERT_EQ(expr6[s], 1.00);
    ASSERT_EQ(expr6[c], 1.00);
    ASSERT_EQ(expr6[v], 2.00);
    auto expr7 = expr2 + expr4 + expr3;
    ASSERT_EQ(expr7.GetSize(), 4);
    ASSERT_EQ(expr7[{}], 2.00);
    ASSERT_EQ(expr7[s], 1.00);
    ASSERT_EQ(expr7[c], 1.00);
    ASSERT_EQ(expr7[v], 2.00);
    auto expr8 = expr3 + expr4 + expr2;
    ASSERT_EQ(expr5.GetSize(), 4);
    ASSERT_EQ(expr8[{}], 2.00);
    ASSERT_EQ(expr8[s], 1.00);
    ASSERT_EQ(expr8[c], 1.00);
    ASSERT_EQ(expr8[v], 2.00);
    auto expr9 = expr3 + expr2 + expr4;
    ASSERT_EQ(expr9.GetSize(), 4);
    ASSERT_EQ(expr9[{}], 2.00);
    ASSERT_EQ(expr9[s], 1.00);
    ASSERT_EQ(expr9[c], 1.00);
    ASSERT_EQ(expr9[v], 2.00);
    auto expr10 = expr4 + expr2 + expr3;
    ASSERT_EQ(expr10.GetSize(), 4);
    ASSERT_EQ(expr10[{}], 2.00);
    ASSERT_EQ(expr10[s], 1.00);
    ASSERT_EQ(expr10[c], 1.00);
    ASSERT_EQ(expr10[v], 2.00);
}
TEST(test, t10)
{
    // won't bother testing this base declarations
    InnerExpression<Index> expr1 = r + 1;
    InnerExpression<IndexedSymbol> expr2 = 1 + s;
    InnerExpression<Constant> expr3 = c + 1;
    InnerExpression<Variable> expr4 = v + v;

    auto expr5 = /*expr1* +*/ expr2 + expr3 + expr4 + 1;
    ASSERT_EQ(expr5.GetSize(), 4);
    ASSERT_EQ(expr5[{}], 3.00);
    ASSERT_EQ(expr5[s], 1.00);
    ASSERT_EQ(expr5[c], 1.00);
    ASSERT_EQ(expr5[v], 2.00);
    auto expr6 = 1 + expr4 + expr3 + expr2;
    ASSERT_EQ(expr6.GetSize(), 4);
    ASSERT_EQ(expr6[{}], 3.00);
    ASSERT_EQ(expr6[s], 1.00);
    ASSERT_EQ(expr6[c], 1.00);
    ASSERT_EQ(expr6[v], 2.00);
    auto expr7 = expr2 + 1 + expr4 + 1 + expr3;
    ASSERT_EQ(expr7.GetSize(), 4);
    ASSERT_EQ(expr7[{}], 4.00);
    ASSERT_EQ(expr7[s], 1.00);
    ASSERT_EQ(expr7[c], 1.00);
    ASSERT_EQ(expr7[v], 2.00);
    auto expr8 = 1 + expr3 + expr4 + expr2 + 1;
    ASSERT_EQ(expr8.GetSize(), 4);
    ASSERT_EQ(expr8[{}], 4.00);
    ASSERT_EQ(expr8[s], 1.00);
    ASSERT_EQ(expr8[c], 1.00);
    ASSERT_EQ(expr8[v], 2.00);
    auto expr9 = 1 + expr3 + 1.000 + expr2 + 'b' + expr4 + 1;
    ASSERT_EQ(expr9.GetSize(), 4);
    ASSERT_EQ(expr9[{}], 103.00);
    ASSERT_EQ(expr9[s], 1.00);
    ASSERT_EQ(expr9[c], 1.00);
    ASSERT_EQ(expr9[v], 2.00);
    auto expr10 = expr1 + expr1;
    ASSERT_EQ(expr10.GetSize(), 2);
    ASSERT_EQ(expr10[{}], 2.00);
    ASSERT_EQ(expr10[r], 2.00);
    auto expr11 = expr2 + 1;
    ASSERT_EQ(expr11.GetSize(), 2);
    ASSERT_EQ(expr11[{}], 2.00);
    ASSERT_EQ(expr11[s], 1.00);
    auto expr12 = 1 + expr3;
    ASSERT_EQ(expr12.GetSize(), 2);
    ASSERT_EQ(expr12[{}], 2.00);
    ASSERT_EQ(expr12[c], 1.00);
}
TEST(test, t11)
{
    // won't bother testing this base declarations
    InnerExpression<Index> expr1 = r + 1;
    InnerExpression<IndexedSymbol> expr2 = 1 + s;
    InnerExpression<Constant> expr3 = c + 1;
    InnerExpression<Variable> expr4 = v + v;

    auto expr5 = r + expr1;
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 1.00);
    ASSERT_EQ(expr5[r], 2.00);
    auto expr6 = s + expr2;
    ASSERT_EQ(expr6.GetSize(), 2);
    ASSERT_EQ(expr6[{}], 1.00);
    ASSERT_EQ(expr6[s], 2.00);
    auto expr7 = c + expr3;
    ASSERT_EQ(expr7.GetSize(), 2);
    ASSERT_EQ(expr7[{}], 1.00);
    ASSERT_EQ(expr7[c], 2.00);
    auto expr8 = v + expr4;
    ASSERT_EQ(expr8.GetSize(), 2);
    ASSERT_EQ(expr8[{}], 0.00);
    ASSERT_EQ(expr8[v], 3.00);

    auto expr9 = expr1 + r;
    ASSERT_EQ(expr9.GetSize(), 2);
    ASSERT_EQ(expr9[{}], 1.00);
    ASSERT_EQ(expr9[r], 2.00);
    auto expr10 = expr2 + s;
    ASSERT_EQ(expr10.GetSize(), 2);
    ASSERT_EQ(expr10[{}], 1.00);
    ASSERT_EQ(expr10[s], 2.00);
    auto expr11 = expr3 + c;
    ASSERT_EQ(expr11.GetSize(), 2);
    ASSERT_EQ(expr11[{}], 1.00);
    ASSERT_EQ(expr11[c], 2.00);
    auto expr12 = expr4 + v;
    ASSERT_EQ(expr12.GetSize(), 2);
    ASSERT_EQ(expr12[{}], 0.00);
    ASSERT_EQ(expr12[v], 3.00);
}
TEST(test, t12)
{
    // won't bother testing this base declarations
    InnerExpression<Index> expr1 = r + 1;
    InnerExpression<IndexedSymbol> expr2 = 1 + s;
    InnerExpression<Constant> expr3 = c + 1;
    InnerExpression<Variable> expr4 = v + v;

    auto expr5 = r + expr1 + r;
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 1.00);
    ASSERT_EQ(expr5[r], 3.00);

    auto expr6 = s + expr2 + v;
    ASSERT_EQ(expr6.GetSize(), 3);
    ASSERT_EQ(expr6[{}], 1.00);
    ASSERT_EQ(expr6[s], 2.00);
    ASSERT_EQ(expr6[v], 1.00);
    auto expr7 = v + expr2 + s;
    ASSERT_EQ(expr7.GetSize(), 3);
    ASSERT_EQ(expr7[{}], 1.00);
    ASSERT_EQ(expr7[s], 2.00);
    ASSERT_EQ(expr7[v], 1.00);
    auto expr8 = v + expr3 + s;
    ASSERT_EQ(expr8.GetSize(), 4);
    ASSERT_EQ(expr8[{}], 1.00);
    ASSERT_EQ(expr8[s], 1.00);
    ASSERT_EQ(expr8[v], 1.00);
    ASSERT_EQ(expr8[c], 1.00);
    auto expr9 = s + expr3 + v;
    ASSERT_EQ(expr9.GetSize(), 4);
    ASSERT_EQ(expr9[{}], 1.00);
    ASSERT_EQ(expr9[s], 1.00);
    ASSERT_EQ(expr9[v], 1.00);
    ASSERT_EQ(expr9[c], 1.00);
    auto expr10 = v + expr4 + s;
    ASSERT_EQ(expr10.GetSize(), 3);
    ASSERT_EQ(expr10[{}], 0.00);
    ASSERT_EQ(expr10[s], 1.00);
    ASSERT_EQ(expr10[v], 3.00);
    auto expr11 = s + expr4 + v;
    ASSERT_EQ(expr11.GetSize(), 3);
    ASSERT_EQ(expr11[{}], 0.00);
    ASSERT_EQ(expr11[s], 1.00);
    ASSERT_EQ(expr11[v], 3.00);

    auto expr12 = 1 + s + 1 + expr2 + 1 + c + v;
    ASSERT_EQ(expr12.GetSize(), 4);
    ASSERT_EQ(expr12[{}], 4.00);
    ASSERT_EQ(expr12[s], 2.00);
    ASSERT_EQ(expr12[v], 1.00);
    ASSERT_EQ(expr12[c], 1.00);
    auto expr13 = c + 1 + v + expr2 + 1 + s + 1;
    ASSERT_EQ(expr13.GetSize(), 4);
    ASSERT_EQ(expr13[{}], 4.00);
    ASSERT_EQ(expr13[s], 2.00);
    ASSERT_EQ(expr13[v], 1.00);
    ASSERT_EQ(expr13[c], 1.00);
    auto expr14 = 1 + s + 1 + expr3 + 1 + c + v;
    ASSERT_EQ(expr14.GetSize(), 4);
    ASSERT_EQ(expr14[{}], 4.00);
    ASSERT_EQ(expr14[s], 1.00);
    ASSERT_EQ(expr14[v], 1.00);
    ASSERT_EQ(expr14[c], 2.00);
    auto expr15 = c + 1 + v + expr4 + 1 + s + 1;
    ASSERT_EQ(expr15.GetSize(), 4);
    ASSERT_EQ(expr15[{}], 3.00);
    ASSERT_EQ(expr15[s], 1.00);
    ASSERT_EQ(expr15[v], 3.00);
    ASSERT_EQ(expr15[c], 1.00);
}
TEST(test, t13)
{
    // won't bother testing this base declarations
    InnerExpression<Index> expr1 = r + 1;
    InnerExpression<IndexedSymbol> expr2 = 1 + s;
    InnerExpression<Constant> expr3 = c + 1;
    InnerExpression<Variable> expr4 = v + v;

    auto expr5 = expr2 + expr2;
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 2.00);
    ASSERT_EQ(expr5[s], 2.00);
    auto expr6 = expr2 + expr3;
    ASSERT_EQ(expr6.GetSize(), 3);
    ASSERT_EQ(expr6[{}], 2.00);
    ASSERT_EQ(expr6[s], 1.00);
    ASSERT_EQ(expr6[c], 1.00);
    auto expr7 = expr3 + expr2;
    ASSERT_EQ(expr7.GetSize(), 3);
    ASSERT_EQ(expr7[{}], 2.00);
    ASSERT_EQ(expr7[s], 1.00);
    ASSERT_EQ(expr7[c], 1.00);
    auto expr8 = expr2 + expr4;
    ASSERT_EQ(expr8.GetSize(), 3);
    ASSERT_EQ(expr8[{}], 1.00);
    ASSERT_EQ(expr8[s], 1.00);
    ASSERT_EQ(expr8[v], 2.00);
    auto expr9 = expr4 + expr2;
    ASSERT_EQ(expr9.GetSize(), 3);
    ASSERT_EQ(expr9[{}], 1.00);
    ASSERT_EQ(expr9[s], 1.00);
    ASSERT_EQ(expr9[v], 2.00);
}
TEST(test, t14)
{
    // won't bother testing this base declarations
    InnerExpression<Index> expr1 = r + 1;
    InnerExpression<IndexedSymbol> expr2 = 1 + s;
    InnerExpression<Constant> expr3 = c + 1;
    InnerExpression<Variable> expr4 = v + v;

    auto expr5 = 1.000 + r + 1 + expr1 + 1;
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 4.00);
    ASSERT_EQ(expr5[r], 2.00);
    auto expr6 = expr1 + 1 + r + r + expr1;
    ASSERT_EQ(expr6.GetSize(), 2);
    ASSERT_EQ(expr6[{}], 3.00);
    ASSERT_EQ(expr6[r], 4.00);
    auto expr7 = 1.00 + expr2 + expr2 + s;
    ASSERT_EQ(expr7.GetSize(), 2);
    ASSERT_EQ(expr7[{}], 3.00);
    ASSERT_EQ(expr7[s], 3.00);
    auto expr8 = expr2 + s + expr2 + c + v;
    ASSERT_EQ(expr8.GetSize(), 4);
    ASSERT_EQ(expr8[{}], 2.00);
    ASSERT_EQ(expr8[s], 3.00);
    ASSERT_EQ(expr8[v], 1.00);
    ASSERT_EQ(expr8[c], 1.00);
    auto expr9 = v + c + expr2 + s + expr2;
    ASSERT_EQ(expr9.GetSize(), 4);
    ASSERT_EQ(expr9[{}], 2.00);
    ASSERT_EQ(expr9[s], 3.00);
    ASSERT_EQ(expr9[v], 1.00);
    ASSERT_EQ(expr9[c], 1.00);
    auto expr10 = expr2 + 1.00 + c + 1 + v + expr3 + s + 1 + expr4 + s + v + 'a' + c + 1.000;
    ASSERT_EQ(expr10.GetSize(), 4);
    ASSERT_EQ(expr10[{}], 103.00);
    ASSERT_EQ(expr10[s], 3.00);
    ASSERT_EQ(expr10[v], 4.00);
    ASSERT_EQ(expr10[c], 3.00);
}

TEST(test, t15)
{
    InnerExpression<Constant> expr1 = 1.00;
    ASSERT_EQ(expr1.GetSize(), 1);
    ASSERT_EQ(expr1[{}], 1.00);
    InnerExpression<Constant> expr2 = c;
    ASSERT_EQ(expr2.GetSize(), 2);
    ASSERT_EQ(expr2[{}], 0.00);
    ASSERT_EQ(expr2[c], 1.00);
    InnerExpression<Variable, InnerExpression<Constant>> expr3 = v + 1 + 1 + v;
    ASSERT_EQ(expr3.GetSize(), 2);
    ASSERT_EQ(expr3[{}], 2.00);
    ASSERT_EQ(expr3[v], 2.00);
    InnerExpression<IndexedSymbol, InnerExpression<Constant>> expr4 = c + v + 1 + s + /* expr3 */ 1 + v;
    ASSERT_EQ(expr4.GetSize(), 4);
    ASSERT_EQ(expr4[{}], 2.00);
    ASSERT_EQ(expr4[v], 2.00);
    ASSERT_EQ(expr4[s], 1.00);
    ASSERT_EQ(expr4[c], 1.00);
    InnerExpression<IndexedSymbol, InnerExpression<Constant>> expr5;
    expr5[v] = 1 + c; // it works :D
    ASSERT_EQ(expr5.GetSize(), 2);
    ASSERT_EQ(expr5[{}], 0.00);
    ASSERT_EQ(expr5[v], 1 + c);
    expr5 += expr4;
    ASSERT_EQ(expr5.GetSize(), 4);
    ASSERT_EQ(expr5[{}], 2.00);
    ASSERT_EQ(expr5[v], c + 3.00);
    ASSERT_EQ(expr5[s], 1.00);
    ASSERT_EQ(expr5[c], 1.00);
}

TEST(test, t16)
{
    InnerExpression<IndexedSymbol, InnerExpression<Constant>> expr1;
    expr1[v] += c;
    expr1[v] += 1;
    expr1 += 2.00;
    ASSERT_EQ(expr1.GetSize(), 2);
    ASSERT_EQ(expr1[{}], 2.00);
    ASSERT_EQ(expr1[v], c + 1.00);
 
    InnerExpression<IndexedSymbol, InnerExpression<Constant>> expr3 = expr1 + 1 + c;
    ASSERT_EQ(expr3.GetSize(), 3);
    ASSERT_EQ(expr3[{}], 3.00);
    ASSERT_EQ(expr3[v], c + 1.00);
    auto expr4 = 1 + expr1;
    ASSERT_EQ(expr4.GetSize(), 2);
    ASSERT_EQ(expr4[{}], 3.00);
    ASSERT_EQ(expr4[v], c + 1.00);
    auto expr5 = c + expr1;
    ASSERT_EQ(expr5.GetSize(), 3);
    ASSERT_EQ(expr5[{}], 2.00);
    ASSERT_EQ(expr5[v], c + 1.00);
    ASSERT_EQ(expr5[c], 1.00);
}

TEST(test, t17)
{
    // this batch will consist of the tests that are not working at the moment.
    // it is still necessary to enable the "default constructed" inner expressions with 'coefficient_type = double' to
    // auto-convert to more complex types (like 'Constant). since this seems as a corner case at the moment, we will
    // focus on more important/interesting stuff. nevertheless, any corner cases will be included here.

    //auto expr1 = c + c + expr1; // C++ no operator matches these operands operand types are: InnerExpression<or2l::Constant, double> + InnerExpression<or2l::Constant, InnerExpression<or2l::Constant, double>>
    //auto expr2 = 1 + c + expr1; // C++ no operator matches these operands operand types are: InnerExpression<or2l::Constant, double> + InnerExpression<or2l::Constant, InnerExpression<or2l::Constant, double>>

    //InnerExpression<IndexedSymbol, InnerExpression<Constant>> expr3;
    //InnerExpression<IndexedSymbol, double> expr4 = s + v + 1;
    //auto expr7 = expr3 + expr4; // C++ no operator matches these operands operand types are: InnerExpression<or2l::IndexedSymbol, InnerExpression<or2l::Constant, double>> + InnerExpression<or2l::IndexedSymbol, double>
    //auto expr8 = expr4 + expr3; // C++ no operator matches these operands operand types are: InnerExpression<or2l::IndexedSymbol, double> + InnerExpression<or2l::IndexedSymbol, InnerExpression<or2l::Constant, double>>
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
