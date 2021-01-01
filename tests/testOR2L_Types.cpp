#include "ModuleTester.h"
#include "Vecxd.h"
#include "INDEX.h"
#include "VARIABLE.h"
#include "EXPRESSION.h"
#include "MATH_EXPRESSION.h"
#include "MODEL.h"
#include "REGEX_STRING.h"
#include "SYMBOL_COMPONENT.h"
#include <cassert>

using namespace DEMALIB::BASE_TYPES;
using namespace OR2L;

std::vector<std::function<void()>> ModuleTester::tests =
	{
		[]() {
			// tests the multi-vector class with the 'index' class
			Vecxd<INDEX> indexes;

			std::initializer_list<size_t> sizes = {1, 2, 3, 4, 5};
			INDEX dflt_init = INDEX("i", 0, 20);

			indexes.ResizeContents(sizes, dflt_init);
			assert(indexes.at(0).at(0) == dflt_init);
			assert(indexes.at(1).at(1) == dflt_init);
			assert(indexes.at(2).at(2) == dflt_init);
			assert(indexes.at(3).at(3) == dflt_init);
			assert(indexes.at(4).at(4) == dflt_init);
		},
		[]() {
			// tests the default initializer for the multi-vector class, using the 'index' class
			Vecxd<INDEX> indexes({1, 2, 3, 4, 5}, INDEX("i", 0, 20));
			assert(indexes.at(0).at(0) == INDEX("i", 0, 20));
			assert(indexes.at(1).at(1) == INDEX("i", 0, 20));
			assert(indexes.at(2).at(2) == INDEX("i", 0, 20));
			assert(indexes.at(3).at(3) == INDEX("i", 0, 20));
			assert(indexes.at(4).at(4) == INDEX("i", 0, 20));
		},
		[]() {
			// tests the constructor for the 'variable' class. Also tests the multi-vector class default initialization using a 'variable' object
			INDEX i("i", 0, 20);
			INDEX j("j", 0, 10);
			INDEX k("k", 1110, 23210);
			VARIABLE var = VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j, k});
			Vecxd<VARIABLE> variables({1, 2, 3, 4, 5}, var);
			assert(variables.at(0).at(0) == var);
			assert(variables.at(1).at(1) == var);
			assert(variables.at(2).at(2) == var);
			assert(variables.at(3).at(3) == var);
			assert(variables.at(4).at(4) == var);
		},
		[]() {
			// tests direct initialization of the multi-vector class using the 'variable' class as template argument
			INDEX i("i", 0, 20);
			INDEX j("j", 0, 10);
			Vecxd<VARIABLE> variables({1, 2, 3, 4, 5}, VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j}));
			assert(variables.at(0).at(0) == VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j}));
			assert(variables.at(1).at(1) == VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j}));
			assert(variables.at(2).at(2) == VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j}));
			assert(variables.at(3).at(3) == VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j}));
			assert(variables.at(4).at(4) == VARIABLE("X", VARIABLE_TYPE::CONTINUOUS, {i, j}));
		},
		[]() {
			// tests the following operators of the 'expression' class:
			// EXPRESSION& operator+=(EXPRESSION) ok
			// EXPRESSION& operator-=(EXPRESSION) ok
			// EXPRESSION& operator+=(double) ok
			// EXPRESSION& operator-=(double) ok
			// EXPRESSION& operator+=(VARIABLE) ok
			// EXPRESSION& operator-=(VARIABLE) ok
			// EXPRESSION& operator*=(double) ok
			// EXPRESSION& operator/=(double) ok

			// EXPRESSION& operator+(EXPRESSION) ok
			// EXPRESSION& operator-(EXPRESSION) ok
			// EXPRESSION& operator+(VARIABLE) ok
			// EXPRESSION& operator-(VARIABLE) ok

			// EXPRESSION operator-(VARIABLE,VARIABLE) ok
			// EXPRESSION operator+(VARIABLE,VARIABLE) ok
			// both variants of EXPRESSION operator*(VARIABLE, double) ok
			// both variants of EXPRESSION operator/(VARIABLE, double) ok

			INDEX i("i", 0, 20);
			INDEX j("j", 0, 10);
			INDEX k("k", 5, 30);

			VARIABLE C_ijk("Cost", VARIABLE_TYPE::CONTINUOUS, {i, j, k});
			VARIABLE V_i("Velocity", VARIABLE_TYPE::CONTINUOUS, {i});

			double coeff1 = 5.45;

			EXPRESSION expr1 = C_ijk + V_i;
			assert(expr1.ContainsVariable(C_ijk) == true);
			assert(expr1.ContainsVariable(V_i) == true);
			assert(abs(expr1.GetCoefficient(C_ijk) - 1.00) <= OR2L::EPSILON);
			assert(abs(expr1.GetCoefficient(V_i) - 1.00) <= OR2L::EPSILON);
			assert(expr1.GetConstant() == 0.00);

			EXPRESSION expr2 = C_ijk + V_i + coeff1;
			assert(expr2.ContainsVariable(C_ijk) == true);
			assert(expr2.ContainsVariable(V_i) == true);
			assert(abs(expr2.GetCoefficient(C_ijk) - 1.00) <= OR2L::EPSILON);
			assert(abs(expr2.GetCoefficient(V_i) - 1.00) <= OR2L::EPSILON);
			assert(expr2.GetConstant() == 5.45);

			EXPRESSION expr3 = expr1 + C_ijk;
			assert(expr3.ContainsVariable(C_ijk) == true);
			assert(expr3.ContainsVariable(V_i) == true);
			assert(abs(expr3.GetCoefficient(C_ijk) - 2.00) <= OR2L::EPSILON);
			assert(abs(expr3.GetCoefficient(V_i) - 1.00) <= OR2L::EPSILON);
			assert(expr3.GetConstant() == 0.00);

			EXPRESSION expr4 = C_ijk - V_i;
			assert(expr4.ContainsVariable(C_ijk) == true);
			assert(expr4.ContainsVariable(V_i) == true);
			assert(abs(expr4.GetCoefficient(C_ijk) - 1.00) <= OR2L::EPSILON);
			assert(abs(expr4.GetCoefficient(V_i) + 1.00) <= OR2L::EPSILON);
			assert(expr4.GetConstant() == 0.00);

			EXPRESSION expr5 = expr4 - coeff1;
			assert(expr4.ContainsVariable(C_ijk) == true);
			assert(expr4.ContainsVariable(V_i) == true);
			assert(abs(expr4.GetCoefficient(C_ijk) - 1.00) <= OR2L::EPSILON);
			assert(abs(expr4.GetCoefficient(V_i) + 1.00) <= OR2L::EPSILON);
			assert(expr4.GetConstant() == -5.45);

			EXPRESSION expr6;
			VARIABLE T("T", VARIABLE_TYPE::CONTINUOUS, {i});
			EXPRESSION expr6_1 = 2.00;
			expr6 += expr6_1;
			assert(expr6.ContainsVariable(T) == false);
			try
			{
				expr6.GetCoefficient(T);
			}
			catch (const std::out_of_range &e)
			{
			}
			assert(expr6.GetConstant() - 2.00 <= OR2L::EPSILON);
			expr6 += T;
			assert(expr6.ContainsVariable(T) == true);
			assert(expr6.GetCoefficient(T) - 1.00 <= OR2L::EPSILON);
			assert(expr6.GetConstant() - 2.00 <= OR2L::EPSILON);
			expr6 -= T;
			assert(expr6.ContainsVariable(T) == false);
			try
			{
				expr6.GetCoefficient(T);
			}
			catch (const std::out_of_range &e)
			{
			}
			assert(expr6.GetConstant() - 2.00 <= OR2L::EPSILON);
			expr6 -= expr6;
			assert(expr6.ContainsVariable(T) == false);
			try
			{
				expr6.GetCoefficient(T);
			}
			catch (const std::out_of_range &e)
			{
			}
			assert(expr6.GetConstant() - 0.00 <= OR2L::EPSILON);

			EXPRESSION expr7 = VARIABLE("Dummy1", VARIABLE_TYPE::CONTINUOUS, {i});
			VARIABLE var7_1 = VARIABLE("Dummy2", VARIABLE_TYPE::CONTINUOUS, {i});
			expr7 = expr7 - var7_1;
			assert(expr7.ContainsVariable(var7_1) == true);
			assert(expr7.GetCoefficient(var7_1) + 1.00 <= OR2L::EPSILON);
			assert(expr7.GetConstant() - 0.00 <= OR2L::EPSILON);
			//expr7 *= var7_1; //fails to compile, as expected
			expr7 *= 2.00;
			assert(expr7.ContainsVariable(VARIABLE("Dummy1", VARIABLE_TYPE::CONTINUOUS, {i})) == true);
			assert(expr7.ContainsVariable(var7_1) == true);
			assert(expr7.GetCoefficient(VARIABLE("Dummy1", VARIABLE_TYPE::CONTINUOUS, {i})) - 2.00 <= OR2L::EPSILON);
			assert(expr7.GetCoefficient(var7_1) + 2.00 <= OR2L::EPSILON);
			assert(expr7.GetConstant() - 0.00 <= OR2L::EPSILON);
			expr7 /= 2.00;
			assert(expr7.ContainsVariable(VARIABLE("Dummy1", VARIABLE_TYPE::CONTINUOUS, {i})) == true);
			assert(expr7.ContainsVariable(var7_1) == true);
			assert(expr7.GetCoefficient(VARIABLE("Dummy1", VARIABLE_TYPE::CONTINUOUS, {i})) - 1.00 <= OR2L::EPSILON);
			assert(expr7.GetCoefficient(var7_1) + 1.00 <= OR2L::EPSILON);
			assert(expr7.GetConstant() - 0.00 <= OR2L::EPSILON);

			VARIABLE var1("var1", VARIABLE_TYPE::CONTINUOUS, {i, j});
			EXPRESSION expr8 = 2.00 * var1;
			EXPRESSION expr8_1 = var1 * 2;
			//assert(expr8 == expr8_1);
			assert(expr8_1.ContainsVariable(var1) == true);
			assert(expr8_1.GetCoefficient(var1) - 2.00 <= OR2L::EPSILON);
			assert(expr8_1.GetConstant() - 0.00 <= OR2L::EPSILON);
			EXPRESSION expr8_2 = var1 / 2;
			assert(expr8_2.ContainsVariable(var1) == true);
			assert(expr8_2.GetCoefficient(var1) - 0.50 <= OR2L::EPSILON);
			assert(expr8_2.GetConstant() - 0.00 <= OR2L::EPSILON);
			EXPRESSION expr8_3 = 2 / var1;
			assert(expr8_3.ContainsVariable(var1) == true);
			assert(expr8_3.GetCoefficient(var1) - pow(2, -1) <= OR2L::EPSILON);
			assert(expr8_3.GetConstant() - 0.00 <= OR2L::EPSILON);
		},
		[]() {
			// tests related to 'MATH_EXPRESSION'
			EXPRESSION expr1 = 2.00;
			EXPRESSION expr2 = 3.00;
			MATH_EXPRESSION mexpr(expr1, EXPRESSION_OPERATORS_TYPE::EQUAL, expr2);
		},
		[]() {
			// tests related to the new string wrapper (used to avoid invalid chars in LaTeX)
			REGEX_STRING str1 = "var1";
			REGEX_STRING str2 = "I";
			REGEX_STRING str4 = "Test";
			REGEX_STRING str5 = "aVariable";

			try
			{
				REGEX_STRING str6 = "A_Variable";
			}
			catch (const OR2LEXCEPTION &e)
			{
			}
			try
			{
				REGEX_STRING str7 = "215%!56&8*9331!";
			}
			catch (const OR2LEXCEPTION &e)
			{
			}
			try
			{
				REGEX_STRING str8 = "$Var1";
			}
			catch (const OR2LEXCEPTION &e)
			{
			}
		},
		[]() {
			// test if function that use 'REGEX_STRING' have the regex on the constructors working
			VARIABLE var1("var1", VARIABLE_TYPE::CONTINUOUS);
			SYMBOL_COMPONENT symb1(var1);

			ASSERT_THROW(SYMBOL_COMPONENT symb2("$var1", SYMBOL_TYPE::VARIABLE), OR2LEXCEPTION);
		},
		[]() {
			// some tests related to the 'MODEL' class
			// Template problem:
			// 						x1 + x2 + x3 ≥ 15
			// 						x1 ≤ 7
			// 						x2 ≤ 3
			// 						x3 ≤ 5
			// 						Clearly the only way that all of these constraints can be satisfied is if x1 = 7, x2 = 3, and x3 =5
			MODEL model("ValidName");
			INDEX dummy1("i", 0, 100), dummy2("j", 15, 300);
			VARIABLE x1("x1"), x2("x2"), x3("x3");
			MATH_EXPRESSION expr1(x1, EXPRESSION_OPERATORS_TYPE::LESS_EQUAL, 7);
			CONSTRAINT R1("R1", expr1);
			CONSTRAINT R2("R2", MATH_EXPRESSION(x2, EXPRESSION_OPERATORS_TYPE::LESS_EQUAL, 3));
			CONSTRAINT R3("R3", MATH_EXPRESSION(x3, EXPRESSION_OPERATORS_TYPE::LESS_EQUAL, 5));

			model.AddIndex(dummy1);
			model.AddIndex(dummy2);
			model.AddVariable(x1);
			model.AddVariable(x2);
			model.AddVariable(x3);
			model.AddConstraint(R1);

			auto cstr1 = model.Get("x1");
			auto cstr2 = model.Get("j");
			auto cstr3 = model.Get("R1");
			model.RemoveIndex(dummy2);
			model.Remove("x1");
			model.RemoveVariable(x2);
			model.RemoveConstraint(R1);

			ASSERT_THROW(MODEL model("_invalid_name"), OR2L::OR2LEXCEPTION);
			ASSERT_THROW(VARIABLE x4("$%!GSE#"), OR2L::OR2LEXCEPTION);
			ASSERT_THROW(CONSTRAINT R3("_$_#_#", MATH_EXPRESSION(x3, EXPRESSION_OPERATORS_TYPE::LESS_EQUAL, 5)), OR2L::OR2LEXCEPTION);
			ASSERT_THROW(auto cstr4 = model.Get("N/A"), OR2L::OR2LEXCEPTION);
			ASSERT_THROW(auto cstr5 = model.Get("x4"), std::out_of_range);
			ASSERT_THROW(auto cstr6 = model.Get("dummy2"), std::out_of_range);
			ASSERT_THROW(auto cstr7 = model.Get("dummy2"), std::out_of_range);
			ASSERT_THROW(auto cstr8 = model.Get("x2"), std::out_of_range);
			ASSERT_THROW(auto cstr9 = model.Get("R1"), std::out_of_range);
		}};

int main()
{
	return ModuleTester::Run();
}