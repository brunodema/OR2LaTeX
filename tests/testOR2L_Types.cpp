#include "../src/BaseTypesLib/ModuleTester.h"
#include "../src/BaseTypesLib/Vecxd.h"
#include "../src/OR2LaTeX/OR2L_Types/INDEX.h"
#include "../src/OR2LaTeX/OR2L_Types/VARIABLE.h"
#include "../src/OR2LaTeX/OR2L_Types/EXPRESSION.h"
#include <cassert>

using namespace DEMALIB::BASE_TYPES;
using namespace OR2L;

std::vector<std::function<void()>> ModuleTester::tests =
	{
		[]() {
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
			Vecxd<INDEX> indexes({1, 2, 3, 4, 5}, INDEX(0, 20, "i"));
			assert(indexes.at(0).at(0) == INDEX(0, 20, "i"));
			assert(indexes.at(1).at(1) == INDEX(0, 20, "i"));
			assert(indexes.at(2).at(2) == INDEX(0, 20, "i"));
			assert(indexes.at(3).at(3) == INDEX(0, 20, "i"));
			assert(indexes.at(4).at(4) == INDEX(0, 20, "i"));
		},
		[]() {
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
			INDEX i(0, 20, "i");
			INDEX j(0, 10, "j");
			INDEX k(5, 30, "k");

			VARIABLE C_ijk({i, j, k}, "Cost");
			VARIABLE V_i({i}, "Velocity");

			double coeff1 = 5.45;

			EXPRESSION expr1 = C_ijk + V_i;
			EXPRESSION expr2 = C_ijk + V_i + coeff1;
			EXPRESSION expr3 = expr1 + C_ijk;

			EXPRESSION expr4 = C_ijk - V_i;
			EXPRESSION expr5 = expr4 - coeff1;

			//assert(variables.at(0).at(0) == VARIABLE({ i,j }, "X"));
			//assert(variables.at(1).at(1) == VARIABLE({ i,j }, "X"));
			//assert(variables.at(2).at(2) == VARIABLE({ i,j }, "X"));
			//assert(variables.at(3).at(3) == VARIABLE({ i,j }, "X"));
			//assert(variables.at(4).at(4) == VARIABLE({ i,j }, "X"));
		}};

int main()
{
	return ModuleTester::Run();
}