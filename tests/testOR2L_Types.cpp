#include "../src/BaseTypesLib/ModuleTester.h"
#include "../src/BaseTypesLib/Vecxd.h"
#include "../src/OR2LaTeX/OR2L_Types/INDEX.h"
#include "../src/OR2LaTeX/OR2L_Types/VARIABLE.h"
#include "../src/OR2LaTeX/OR2L_Types/EXPRESSION.h"
#include <cassert>

#define EPSILON 0.0000001

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
		VARIABLE var = VARIABLE({i, j, k}, "X");
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
		Vecxd<VARIABLE> variables({1, 2, 3, 4, 5}, VARIABLE({i, j}, "X"));
		assert(variables.at(0).at(0) == VARIABLE({i, j}, "X"));
		assert(variables.at(1).at(1) == VARIABLE({i, j}, "X"));
		assert(variables.at(2).at(2) == VARIABLE({i, j}, "X"));
		assert(variables.at(3).at(3) == VARIABLE({i, j}, "X"));
		assert(variables.at(4).at(4) == VARIABLE({i, j}, "X"));
	},
	[]() {
		// tests the following operators of the 'expression' class: 
		// EXPRESSION operator+(VARIABLE,VARIABLE);
		// EXPRESSION& operator+(EXPRESSION);
		// EXPRESSION& operator+(VARIABLE);
		// EXPRESSION operator-(VARIABLE,VARIABLE);	
		// EXPRESSION& operator-(EXPRESSION);		
		INDEX i(0, 20, "i");
		INDEX j(0, 10, "j");
		INDEX k(5, 30, "k");

		VARIABLE C_ijk({i, j, k}, "Cost");
		VARIABLE V_i({i}, "Velocity");

		double coeff1 = 5.45;

		EXPRESSION expr1 = C_ijk + V_i;
		assert(expr1.ContainsVariable(C_ijk) == true);
		assert(expr1.ContainsVariable(V_i) == true);
		assert(abs(expr1.GetCoefficient(C_ijk) - 1.00) <= EPSILON);
		assert(abs(expr1.GetCoefficient(V_i) - 1.00) <= EPSILON);
		assert(expr1.GetConstant() == 0.00);

		EXPRESSION expr2 = C_ijk + V_i + coeff1;
		assert(expr2.ContainsVariable(C_ijk) == true);
		assert(expr2.ContainsVariable(V_i) == true);
		assert(abs(expr2.GetCoefficient(C_ijk) - 1.00) <= EPSILON);
		assert(abs(expr2.GetCoefficient(V_i) - 1.00) <= EPSILON);
		assert(expr2.GetConstant() == 5.45);

		EXPRESSION expr3 = expr1 + C_ijk;
		assert(expr3.ContainsVariable(C_ijk) == true);
		assert(expr3.ContainsVariable(V_i) == true);
		assert(abs(expr3.GetCoefficient(C_ijk) - 2.00) <= EPSILON);
		assert(abs(expr3.GetCoefficient(V_i) - 1.00) <= EPSILON);
		assert(expr3.GetConstant() == 0.00);

		EXPRESSION expr4 = C_ijk - V_i;
		assert(expr4.ContainsVariable(C_ijk) == true);
		assert(expr4.ContainsVariable(V_i) == true);
		assert(abs(expr4.GetCoefficient(C_ijk) - 1.00) <= EPSILON);
		assert(abs(expr4.GetCoefficient(V_i) + 1.00) <= EPSILON);
		assert(expr4.GetConstant() == 0.00);

		EXPRESSION expr5 = expr4 - coeff1;
		assert(expr4.ContainsVariable(C_ijk) == true);
		assert(expr4.ContainsVariable(V_i) == true);
		assert(abs(expr4.GetCoefficient(C_ijk) - 1.00) <= EPSILON);
		assert(abs(expr4.GetCoefficient(V_i) + 1.00) <= EPSILON);
		assert(expr4.GetConstant() == -5.45);
	} };

int main()
{
	return ModuleTester::Run();
}