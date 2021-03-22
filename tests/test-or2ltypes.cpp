#include "Bounds.h"
#include "Constraint.h"
#include "Exception.h"
#include "Expression.h"
#include "Index.h"
#include "MathExpression.h"
#include "Model.h"
#include "ModuleTester.h"
#include "OperatorTypes.h"
#include "RegexString.h"
#include "SymbolComponent.h"
#include "SymbolType.h"
#include "Variable.h"
#include "VariableType.h"
#include "Vecxd.h"
#include "solver_objects/Solver.h"
#include <cassert>
#include <cstddef>
#include <memory>
#include <ortools/linear_solver/linear_solver.h>
#include <stdexcept>
#include <string>

using base_types::ModuleTester;
using base_types::MultiArray;
using or2l::Constraint;
using or2l::Expression;
using or2l::Index;
using or2l::MathExpression;
using or2l::MathExpressionOperatorTypes;
using or2l::Model;
using or2l::SymbolComponent;
using or2l::SymbolType;
using or2l::Variable;
using or2l::VariableType;

std::vector<std::function<void()>> ModuleTester::tests_ = {
    []() {
        // tests the multi-vector class with the 'index' class
        MultiArray<Index> indexes;

        std::initializer_list<size_t> sizes = {7, 6};
        Index dflt_init = Index("i", 0, 20);

        indexes.ResizeContents(sizes);
        indexes.FillWith(dflt_init);
        assert((indexes[{0, 0}] == dflt_init));
        assert((indexes[{1, 1}] == dflt_init));
        assert((indexes[{2, 2}] == dflt_init));
        assert((indexes[{3, 3}] == dflt_init));
        assert((indexes[{4, 4}] == dflt_init));
    },
    []() {
        // tests the default initializer for the multi-vector class, using the
        // 'index' class
        MultiArray<Index> indexes;
        indexes.ResizeContents({1, 2, 3, 4, 5});
        Index sample("i", 0, 20);
        indexes.FillWith(sample);
        assert((indexes[{0, 0, 0, 0, 0}] == sample));
        assert((indexes[{0, 1, 1, 1, 1}] == sample));
        assert((indexes[{0, 1, 2, 2, 2}] == sample));
        assert((indexes[{0, 1, 2, 3, 3}] == sample));
        assert((indexes[{0, 1, 2, 3, 4}] == sample));
    },
    []() {
        // tests the constructor for the 'variable' class. Also tests the
        // multi-vector class default initialization using a 'variable' object
        Index i("i", 0, 20);
        Index j("j", 0, 10);
        Index k("k", 1110, 23210);
        Variable var = Variable("X", VariableType::CONTINUOUS, {i, j, k});
        MultiArray<Variable> variables({30, 30, 30});
        variables.FillWith(var);
        assert((variables[{3, 5, 4}] == var));
        assert((variables[{1, 1, 1}] == var));
        assert((variables[{2, 20, 20}] == var));
        assert((variables[{15, 14, 11}] == var));
        assert((variables[{2, 13, 23}] == var));
    },
    []() {
        // tests direct initialization of the multi-vector class using the
        // 'variable' class as template argument
        Index i("i", 0, 20);
        Index j("j", 0, 10);
        MultiArray<Variable> variables({10, 20});
        variables.FillWith(Variable("X", VariableType::CONTINUOUS, {i, j}));
        assert((variables[{0, 0}] == Variable("X", VariableType::CONTINUOUS, {i, j})));
        assert((variables[{1, 1}] == Variable("X", VariableType::CONTINUOUS, {i, j})));
        assert((variables[{2, 2}] == Variable("X", VariableType::CONTINUOUS, {i, j})));
        assert((variables[{3, 3}] == Variable("X", VariableType::CONTINUOUS, {i, j})));
        assert((variables[{4, 4}] == Variable("X", VariableType::CONTINUOUS, {i, j})));
    },
    []() {
        // tests the following operators of the 'expression' class:
        // Expression& operator+=(Expression) ok
        // Expression& operator-=(Expression) ok
        // Expression& operator+=(double) ok
        // Expression& operator-=(double) ok
        // Expression& operator+=(Variable) ok
        // Expression& operator-=(Variable) ok
        // Expression& operator*=(double) ok
        // Expression& operator/=(double) ok

        // Expression& operator+(Expression) ok
        // Expression& operator-(Expression) ok
        // Expression& operator+(Variable) ok
        // Expression& operator-(Variable) ok

        // Expression operator-(Variable,Variable) ok
        // Expression operator+(Variable,Variable) ok
        // both variants of Expression operator*(Variable, double) ok
        // both variants of Expression operator/(Variable, double) ok

        Index i("i", 0, 20);
        Index j("j", 0, 10);
        Index k("k", 5, 30);

        Variable C_ijk("Cost", VariableType::CONTINUOUS, {i, j, k});
        Variable V_i("Velocity", VariableType::CONTINUOUS, {i});

        double coeff1 = 5.45;

        Expression expr1 = C_ijk + V_i;
        assert(expr1.ContainsVariable(C_ijk) == true);
        assert(expr1.ContainsVariable(V_i) == true);
        assert(fabs(expr1.GetCoefficient(C_ijk) - 1.00) <= or2l::EPSILON);
        assert(fabs(expr1.GetCoefficient(V_i) - 1.00) <= or2l::EPSILON);
        assert(expr1.GetConstant() == 0.00);

        Expression expr2 = C_ijk + V_i + coeff1;
        assert(expr2.ContainsVariable(C_ijk) == true);
        assert(expr2.ContainsVariable(V_i) == true);
        assert(fabs(expr2.GetCoefficient(C_ijk) - 1.00) <= or2l::EPSILON);
        assert(fabs(expr2.GetCoefficient(V_i) - 1.00) <= or2l::EPSILON);
        assert(expr2.GetConstant() == 5.45);

        Expression expr3 = expr1 + C_ijk;
        assert(expr3.ContainsVariable(C_ijk) == true);
        assert(expr3.ContainsVariable(V_i) == true);
        assert(fabs(expr3.GetCoefficient(C_ijk) - 2.00) <= or2l::EPSILON);
        assert(fabs(expr3.GetCoefficient(V_i) - 1.00) <= or2l::EPSILON);
        assert(expr3.GetConstant() == 0.00);

        Expression expr4 = C_ijk - V_i;
        assert(expr4.ContainsVariable(C_ijk) == true);
        assert(expr4.ContainsVariable(V_i) == true);
        assert(fabs(expr4.GetCoefficient(C_ijk) - 1.00) <= or2l::EPSILON);
        assert(fabs(expr4.GetCoefficient(V_i) + 1.00) <= or2l::EPSILON);
        assert(expr4.GetConstant() == 0.00);

        Expression expr5 = expr4 - coeff1;
        assert(expr4.ContainsVariable(C_ijk) == true);
        assert(expr4.ContainsVariable(V_i) == true);
        assert(fabs(expr4.GetCoefficient(C_ijk) - 1.00) <= or2l::EPSILON);
        assert(fabs(expr4.GetCoefficient(V_i) + 1.00) <= or2l::EPSILON);
        assert(expr4.GetConstant() == -5.45);

        Expression expr6;
        Variable T("T", VariableType::CONTINUOUS, {i});
        Expression expr6_1 = 2.00;
        expr6 += expr6_1;
        assert(expr6.ContainsVariable(T) == false);
        try
        {
            expr6.GetCoefficient(T);
        }
        catch (const std::out_of_range &e)
        {
        }
        assert(expr6.GetConstant() - 2.00 <= or2l::EPSILON);
        expr6 += T;
        assert(expr6.ContainsVariable(T) == true);
        assert(expr6.GetCoefficient(T) - 1.00 <= or2l::EPSILON);
        assert(expr6.GetConstant() - 2.00 <= or2l::EPSILON);
        expr6 -= T;
        assert(expr6.ContainsVariable(T) == false);
        try
        {
            expr6.GetCoefficient(T);
        }
        catch (const std::out_of_range &e)
        {
        }
        assert(expr6.GetConstant() - 2.00 <= or2l::EPSILON);
        expr6 -= expr6;
        assert(expr6.ContainsVariable(T) == false);
        try
        {
            expr6.GetCoefficient(T);
        }
        catch (const std::out_of_range &e)
        {
        }
        assert(expr6.GetConstant() - 0.00 <= or2l::EPSILON);

        Expression expr7 = Variable("Dummy1", VariableType::CONTINUOUS, {i});
        Variable var7_1 = Variable("Dummy2", VariableType::CONTINUOUS, {i});
        expr7 = expr7 - var7_1;
        assert(expr7.ContainsVariable(var7_1) == true);
        assert(expr7.GetCoefficient(var7_1) + 1.00 <= or2l::EPSILON);
        assert(expr7.GetConstant() - 0.00 <= or2l::EPSILON);
        // expr7 *= var7_1; //fails to compile, as expected
        expr7 *= 2.00;
        assert(expr7.ContainsVariable(Variable("Dummy1", VariableType::CONTINUOUS, {i})) == true);
        assert(expr7.ContainsVariable(var7_1) == true);
        assert(expr7.GetCoefficient(Variable("Dummy1", VariableType::CONTINUOUS, {i})) - 2.00 <= or2l::EPSILON);
        assert(expr7.GetCoefficient(var7_1) + 2.00 <= or2l::EPSILON);
        assert(expr7.GetConstant() - 0.00 <= or2l::EPSILON);
        expr7 /= 2.00;
        assert(expr7.ContainsVariable(Variable("Dummy1", VariableType::CONTINUOUS, {i})) == true);
        assert(expr7.ContainsVariable(var7_1) == true);
        assert(expr7.GetCoefficient(Variable("Dummy1", VariableType::CONTINUOUS, {i})) - 1.00 <= or2l::EPSILON);
        assert(expr7.GetCoefficient(var7_1) + 1.00 <= or2l::EPSILON);
        assert(expr7.GetConstant() - 0.00 <= or2l::EPSILON);

        Variable var1("var1", VariableType::CONTINUOUS, {i, j});
        Expression expr8 = 2.00 * var1;
        Expression expr8_1 = var1 * 2;
        // assert(expr8 == expr8_1);
        assert(expr8_1.ContainsVariable(var1) == true);
        assert(expr8_1.GetCoefficient(var1) - 2.00 <= or2l::EPSILON);
        assert(expr8_1.GetConstant() - 0.00 <= or2l::EPSILON);
        Expression expr8_2 = var1 / 2;
        assert(expr8_2.ContainsVariable(var1) == true);
        assert(expr8_2.GetCoefficient(var1) - 0.50 <= or2l::EPSILON);
        assert(expr8_2.GetConstant() - 0.00 <= or2l::EPSILON);
        Expression expr8_3 = 2 / var1;
        assert(expr8_3.ContainsVariable(var1) == true);
        assert(expr8_3.GetCoefficient(var1) - pow(2, -1) <= or2l::EPSILON);
        assert(expr8_3.GetConstant() - 0.00 <= or2l::EPSILON);

        // the tests for the following operators are missing:
        //
        // Expression operator+(double, variable);
        // Expression operator+(variable, double);
        // Expression operator-(double, variable);
        // Expression operator-(variable, double);
        //
        // even though they are not here, they were tested in a previous commit,
        // which was lost during development. Implement them back in the future
    },
    []() {
        // tests related to 'MathExpression'
        Expression expr1 = 2.00;
        Expression expr2 = 3.00;
        MathExpression mexpr(expr1, MathExpressionOperatorTypes::EQUAL, expr2);
    },
    []() {
        // tests related to the new string wrapper (used to avoid invalid chars in
        // LaTeX)
        RegexString str1 = "var1";
        RegexString str2 = "I";
        RegexString str4 = "Test";
        RegexString str5 = "aVariable";

        try
        {
            RegexString str6 = "A_Variable";
        }
        catch (const std::invalid_argument &e)
        {
        }
        try
        {
            RegexString str7 = "215%!56&8*9331!";
        }
        catch (const std::invalid_argument &e)
        {
        }
        try
        {
            RegexString str8 = "$Var1";
        }
        catch (const std::invalid_argument &e)
        {
        }
    },
    []() {
        // test if function that use 'RegexString' have the regex on the
        // constructors working
        Variable var1("var1", VariableType::CONTINUOUS);
        const SymbolComponent &symb1(var1);

        ASSERT_THROW(SymbolComponent symb2("$var1", SymbolType::VARIABLE), std::invalid_argument);
    },
    []() {
        std::unique_ptr<Model> model = std::make_unique<Model>("ValidName");
        Index dummy1("i", 0, 100);
        Index dummy2("j", 15, 300);
        Variable x1("x1");
        Variable x2("x2");
        Variable x3("x3");
        MathExpression expr1(x1, MathExpressionOperatorTypes::LESS_EQUAL, 7);
        Constraint R1("R1", expr1);
        Constraint R2("R2", MathExpression(x2, MathExpressionOperatorTypes::LESS_EQUAL, 3));
        Constraint R3("R3", MathExpression(x3, MathExpressionOperatorTypes::LESS_EQUAL, 5));

        model->AddIndex(dummy1);
        model->AddIndex(dummy2);
        model->AddVariable(x1);
        model->AddVariable(x2);
        model->AddVariable(x3);
        model->AddConstraint(R1);

        auto *cstr1 = model->Get("x1");
        auto *cstr2 = model->Get("j");
        auto *cstr3 = model->Get("R1");
        model->RemoveIndex(dummy2);
        model->RemoveSymbol("x1");
        model->RemoveVariable(x2);
        model->RemoveConstraint(R1);

        ASSERT_THROW(std::unique_ptr<Model> model = std::make_unique<Model>("_invalid_name"), std::invalid_argument);
        ASSERT_THROW(Variable x4("$%!GSE#"), std::invalid_argument);
        ASSERT_THROW(Constraint R3("_$_#_#", MathExpression(x3, MathExpressionOperatorTypes::LESS_EQUAL, 5)),
                     std::invalid_argument);
        ASSERT_THROW(auto *cstr4 = model->Get("N/A"), std::invalid_argument);
        ASSERT_THROW(auto *cstr5 = model->Get("x4"), std::out_of_range);
        ASSERT_THROW(auto *cstr6 = model->Get("dummy2"), std::out_of_range);
        ASSERT_THROW(auto *cstr7 = model->Get("dummy2"), std::out_of_range);
        ASSERT_THROW(auto *cstr8 = model->Get("x2"), std::out_of_range);
        ASSERT_THROW(auto *cstr9 = model->Get("R1"), std::out_of_range);
    },
    []() {
        using base_types::Bounds;
        // test the Index -> Bounds conversion
        Index i("i", 0, 20);
        Index j("j", 5, 17);
        Index k("k", 50, 225);

        const Bounds &ii = Bounds(i);
        const Bounds &jj = Bounds(j);
        const Bounds &kk = Bounds(k);

        assert(i.GetUB() == ii.ub && i.GetLB() == ii.lb);
        assert(j.GetUB() == jj.ub && j.GetLB() == jj.lb);
        assert(k.GetUB() == kk.ub && k.GetLB() == kk.lb);
    },
    []() {
        // trying to understand how the map with key = 'VariableIndexPair' works
        std::map<std::pair<std::string, std::string>, int> a = {{std::make_pair("hello", "there"), 1},
                                                                {std::make_pair("hello", "again"), 2},
                                                                {std::make_pair("there", "hello"), 3}};

        assert(a[std::make_pair("hello", "there")] == 1);

        std::map<std::pair<Variable, std::string>, int> b = {{std::make_pair(Variable(), "there"), 1},
                                                             {std::make_pair(Variable(), "again"), 2},
                                                             {std::make_pair(Variable(), "hello"), 3}};

        assert(b[std::make_pair(Variable(), "there")] == 1);

        std::map<std::pair<Variable, std::vector<std::size_t>>, int> c = {
            {std::make_pair(Variable(), std::vector<std::size_t>{1}), 1},
            {std::make_pair(Variable(), std::vector<std::size_t>{2}), 2},
            {std::make_pair(Variable(), std::vector<std::size_t>{3}), 3}};

        assert(c[std::make_pair(Variable(), std::vector<std::size_t>{1})] == 1);

        auto d1 = std::make_pair(Variable(), std::vector<std::size_t>{1, 2, 3});
        auto d2 = std::make_pair(Variable(), std::vector<std::size_t>{1, 2, 4});
        auto d3 = std::make_pair(Variable(), std::vector<std::size_t>{2, 0, 0});

        auto v1 = std::make_shared<int>(1);
        auto v2 = std::make_shared<int>(2);
        auto v3 = std::make_shared<int>(3);

        std::map<std::pair<Variable, std::vector<std::size_t>>, std::weak_ptr<int>> d = {{d1, v1}, {d2, v2}, {d3, v3}};

        auto const val1 = *d[d1].lock();
        assert(val1 == 1);
        auto const val2 = *d[d2].lock();
        assert(val2 == 2);
        auto const val3 = *d[d3].lock();
        assert(val3 == 3);
    }};
// discover what the fuck is going on over here

int main()
{
    return ModuleTester::Run();
}