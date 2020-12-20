#pragma once
#include "../src/BaseTypesLib/ModuleTester.h"
#include "../src/BaseTypesLib/Vecxd.h"
#include "../src/OR2LaTeX/OR2L_Types/INDEX.h"
#include "../src/OR2LaTeX/OR2L_Types/VARIABLE.h"
#include <cassert>

using namespace DEMALIB::BASE_TYPES;

std::vector< std::function<void()>> ModuleTester::tests =
{
[]()
{
	Vecxd<OR2L::INDEX> indexes;
	std::initializer_list<size_t> sizes = { 1,2,3,4,5 };
	OR2L::INDEX dflt_init = OR2L::INDEX(0, 20, "i");

	indexes.ResizeContents(sizes);
	indexes.FillWith(dflt_init);
	assert(indexes.at(0).at(0) == dflt_init);
	assert(indexes.at(1).at(1) == dflt_init);
	assert(indexes.at(2).at(2) == dflt_init);
	assert(indexes.at(3).at(3) == dflt_init);
	assert(indexes.at(4).at(4) == dflt_init);
},
[]()
{
	Vecxd<OR2L::INDEX> indexes({ 1,2,3,4,5 }, OR2L::INDEX(0, 20, "i"));
	assert(indexes.at(0).at(0) == OR2L::INDEX(0, 20, "i"));
	assert(indexes.at(1).at(1) == OR2L::INDEX(0, 20, "i"));
	assert(indexes.at(2).at(2) == OR2L::INDEX(0, 20, "i"));
	assert(indexes.at(3).at(3) == OR2L::INDEX(0, 20, "i"));
	assert(indexes.at(4).at(4) == OR2L::INDEX(0, 20, "i"));
},
[]()
{
	OR2L::INDEX i(0, 20, "i");
	OR2L::INDEX j(0, 10, "j");
	OR2L::INDEX k(1110, 23210, "k");
	OR2L::VARIABLE var = OR2L::VARIABLE("X", { i,j,k });
	Vecxd<OR2L::VARIABLE> variables({ 1,2,3,4,5 }, var);
	assert(variables.at(0).at(0) == var);
	assert(variables.at(1).at(1) == var);
	assert(variables.at(2).at(2) == var);
	assert(variables.at(3).at(3) == var);
	assert(variables.at(4).at(4) == var);
},
[]()
{
	OR2L::INDEX i(0, 20, "i");
	OR2L::INDEX j(0, 10, "j");
	Vecxd<OR2L::VARIABLE> variables({ 1,2,3,4,5 }, OR2L::VARIABLE("C", { i,j }));
	assert(variables.at(0).at(0) == OR2L::VARIABLE("C", { i,j }));
	assert(variables.at(1).at(1) == OR2L::VARIABLE("C", { i,j }));
	assert(variables.at(2).at(2) == OR2L::VARIABLE("C", { i,j }));
	assert(variables.at(3).at(3) == OR2L::VARIABLE("C", { i,j }));
	assert(variables.at(4).at(4) == OR2L::VARIABLE("C", { i,j }));
}
};

int main()
{
	return ModuleTester::Run();
}