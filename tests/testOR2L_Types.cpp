#include "ModuleTester.h"
#include "Vecxd.h"
#include "INDEX.h"
#include "VARIABLE.h"
#include "EXPRESSION.h"
#include "MATH_EXPRESSION.h"
#include <cassert>

using namespace DEMALIB::BASE_TYPES;
using namespace OR2L;

std::vector<std::function<void()>> ModuleTester::tests =
{
	[]() {
		// tests the multi-vector class with the 'index' class
		Vecxd<INDEX> indexes;
		std::initializer_list<size_t> sizes = {1, 2, 3, 4, 5};
		INDEX dflt_init = INDEX(0, 20, "i");

		indexes.ResizeContents(sizes);
		indexes.FillWith(dflt_init);
		assert(indexes.at(0).at(0) == dflt_init);
		assert(indexes.at(1).at(1) == dflt_init);
		assert(indexes.at(2).at(2) == dflt_init);
		assert(indexes.at(3).at(3) == dflt_init);
		assert(indexes.at(4).at(4) == dflt_init);
	},
	[]() {
		// tests the default initializer for the multi-vector class, using the 'index' class
		Vecxd<INDEX> indexes({1, 2, 3, 4, 5}, INDEX(0, 20, "i"));
		assert(indexes.at(0).at(0) == INDEX(0, 20, "i"));
		assert(indexes.at(1).at(1) == INDEX(0, 20, "i"));
		assert(indexes.at(2).at(2) == INDEX(0, 20, "i"));
		assert(indexes.at(3).at(3) == INDEX(0, 20, "i"));
		assert(indexes.at(4).at(4) == INDEX(0, 20, "i"));
	},
	[]() {
		// tests the constructor for the 'variable' class. Also tests the multi-vector class default initialization using a 'variable' object
		INDEX i(0, 20, "i");
		INDEX j(0, 10, "j");
		INDEX k(1110, 23210, "k");
		VARIABLE var = VARIABLE({ i, j, k }, {}, "X");
		Vecxd<VARIABLE> variables({1, 2, 3, 4, 5}, var);
		assert(variables.at(0).at(0) == var);
		assert(variables.at(1).at(1) == var);
		assert(variables.at(2).at(2) == var);
		assert(variables.at(3).at(3) == var);
		assert(variables.at(4).at(4) == var);
	},
	[]() {
		// tests direct initialization of the multi-vector class using the 'variable' class as template argument
		INDEX i(0, 20, "i");
		INDEX j(0, 10, "j");
		Vecxd<VARIABLE> variables({ 1, 2, 3, 4, 5 }, VARIABLE({ i, j }, {}, "X"));
		assert(variables.at(0).at(0) == VARIABLE({ i, j }, {}, "X"));
		assert(variables.at(1).at(1) == VARIABLE({ i, j }, {}, "X"));
		assert(variables.at(2).at(2) == VARIABLE({ i, j }, {}, "X"));
		assert(variables.at(3).at(3) == VARIABLE({ i, j }, {}, "X"));
		assert(variables.at(4).at(4) == VARIABLE({ i, j }, {}, "X"));
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
		// both variants of EXPRESSION operator*(VARIABLE, double) being tested
		// both variants of EXPRESSION operator/(VARIABLE, double) being tested

		INDEX i(0, 20, "i");
		INDEX j(0, 10, "j");
		INDEX k(5, 30, "k");

		VARIABLE C_ijk({ i, j, k }, {}, "Cost");
		VARIABLE V_i({ i }, {}, "Velocity");

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
		VARIABLE T({ i }, {}, "T");
		EXPRESSION expr6_1 = 2.00;
		expr6 += expr6_1;
		assert(expr6.ContainsVariable(T) == false);
		try
		{
			expr6.GetCoefficient(T);
		}
		catch (const std::out_of_range e) {}
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
		catch (const std::out_of_range e) {}
		assert(expr6.GetConstant() - 2.00 <= OR2L::EPSILON);
		expr6 -= expr6;
		assert(expr6.ContainsVariable(T) == false);
		try
		{
			expr6.GetCoefficient(T);
		}
		catch (const std::out_of_range e) {}
		assert(expr6.GetConstant() - 0.00 <= OR2L::EPSILON);

		EXPRESSION expr7 = VARIABLE({ i }, {}, "Dummy1");
		VARIABLE var7_1 = VARIABLE({ i }, {}, "Dummy2");
		expr7 = expr7 - var7_1;
		assert(expr7.ContainsVariable(var7_1) == true);
		assert(expr7.GetCoefficient(var7_1) + 1.00 <= OR2L::EPSILON);
		assert(expr7.GetConstant() - 0.00 <= OR2L::EPSILON);
		//expr7 *= var7_1; //fails to compile, as expected
		expr7 *= 2.00;
		assert(expr7.ContainsVariable(VARIABLE({ i }, {}, "Dummy1")) == true);
		assert(expr7.ContainsVariable(var7_1) == true);
		assert(expr7.GetCoefficient(VARIABLE({ i }, {}, "Dummy1")) - 2.00 <= OR2L::EPSILON);
		assert(expr7.GetCoefficient(var7_1) + 2.00 <= OR2L::EPSILON);
		assert(expr7.GetConstant() - 0.00 <= OR2L::EPSILON);
		expr7 /= 2.00;
		assert(expr7.ContainsVariable(VARIABLE({ i }, {}, "Dummy1")) == true);
		assert(expr7.ContainsVariable(var7_1) == true);
		assert(expr7.GetCoefficient(VARIABLE({ i }, {}, "Dummy1")) - 1.00 <= OR2L::EPSILON);
		assert(expr7.GetCoefficient(var7_1) + 1.00 <= OR2L::EPSILON);
		assert(expr7.GetConstant() - 0.00 <= OR2L::EPSILON);

		VARIABLE var1({ i,j }, {}, "");
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
	[]()
	{
		// tests related to 'MATH_EXPRESSION'
		EXPRESSION expr1 = 2.00;
		EXPRESSION expr2 = 3.00;
		MATH_EXPRESSION mexpr(expr1, EXPRESSION_OPERATORS_TYPE::EQUAL, expr2);
	}
};

int main()
{
	return ModuleTester::Run();
}