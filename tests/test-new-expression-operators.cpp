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
     ASSERT_EQ(expr2.GetSize(), 2);
     ASSERT_EQ(expr2[{}], 0.00);
     ASSERT_EQ(expr2[v], 1.00);
     ASSERT_EQ(expr2[s], 1.00);
     auto expr3 = v + c;
     ASSERT_EQ(expr3.GetSize(), 2);
     ASSERT_EQ(expr3[{}], 0.00);
     ASSERT_EQ(expr3[v], 1.00);
     ASSERT_EQ(expr3[c], 1.00);
     auto expr4 = c + c;
     ASSERT_EQ(expr4.GetSize(), 2);
     ASSERT_EQ(expr4[{}], 0.00);
     ASSERT_EQ(expr4[c], 2.00);
     auto expr5 = s + v;
     ASSERT_EQ(expr5.GetSize(), 2);
     ASSERT_EQ(expr5[{}], 0.00);
     ASSERT_EQ(expr5[v], 1.00);
     ASSERT_EQ(expr5[s], 1.00);
     auto expr6 = c + v;
     ASSERT_EQ(expr2.GetSize(), 2);
     ASSERT_EQ(expr2[{}], 0.00);
     ASSERT_EQ(expr2[v], 1.00);
     ASSERT_EQ(expr2[c], 1.00);
 }
 TEST(test, t3)
 {
     auto expr1 = 1 + v + 1.00;
     auto expr2 = 1.00 + s + 1.000000000;
     auto expr3 = 1.00000000000000 + r + 1;
     auto expr4 = v + 1 + 1.00;
     auto expr5 = s + 1.00 + 1.000000000;
     auto expr6 = r + 1.00000000000000 + 1;
 }
 TEST(test, t4)
 {
     auto expr1 = v + v + 1;
     auto expr2 = v + s + 1.00;
     auto expr3 = v + c + 1.0000000;
     auto expr4 = c + c + 1.0000000;
     auto expr5 = s + v + 1.00;
     auto expr6 = c + v + 1;
 }
 TEST(test, t5)
 {
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
     InnerExpression<Index> expr1 = 1 + r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s + 1;
     InnerExpression<Constant> expr3 = 1 + c + 1;
     InnerExpression<Variable> expr4 = 1 + v + 1;
 }
 TEST(test, t8)
 {
     InnerExpression<Index> expr1 = 1 + r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s + 1;
     InnerExpression<Constant> expr3 = 1 + c + 1;
     InnerExpression<Variable> expr4 = 1 + v + 1;

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
     InnerExpression<Index> expr1 = r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s;
     InnerExpression<Constant> expr3 = c + 1;
     InnerExpression<Variable> expr4 = v + v;

     auto expr5 = /*expr1* +*/ expr2 + expr3 + expr4;
     auto expr6 = expr4 + expr3 + expr2;
     auto expr7 = expr2 + expr4 + expr3;
     auto expr8 = expr3 + expr4 + expr2;
     auto expr9 = expr3 + expr2 + expr4;
     auto expr10 = expr4 + expr2 + expr3;
 }
 TEST(test, t10)
 {
     InnerExpression<Index> expr1 = r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s;
     InnerExpression<Constant> expr3 = c + 1;
     InnerExpression<Variable> expr4 = v + v;

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
     InnerExpression<Index> expr1 = r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s;
     InnerExpression<Constant> expr3 = c + 1;
     InnerExpression<Variable> expr4 = v + v;

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
     InnerExpression<Index> expr1 = r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s;
     InnerExpression<Constant> expr3 = c + 1;
     InnerExpression<Variable> expr4 = v + v;

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
     InnerExpression<Index> expr1 = r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s;
     InnerExpression<Constant> expr3 = c + 1;
     InnerExpression<Variable> expr4 = v + v;

     auto expr5 = expr2 + expr2;
     auto expr6 = expr2 + expr3;
     auto expr7 = expr3 + expr2;
     auto expr8 = expr2 + expr4;
     auto expr9 = expr4 + expr2;
 }
 TEST(test, t14)
 {
     InnerExpression<Index> expr1 = r + 1;
     InnerExpression<IndexedSymbol> expr2 = 1 + s;
     InnerExpression<Constant> expr3 = c + 1;
     InnerExpression<Variable> expr4 = v + v;

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