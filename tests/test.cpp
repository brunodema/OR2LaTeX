#include "ModuleTester.h"

using namespace DEMALIB::BASE_TYPES;
using namespace OR2L;

/**
 * Test prototype for a working version of the library
 *
 * Model model()
 * Index ... index(lb, ub, name)
 * Variable ... var(...indexes, type, name)
 * VariableSet varset(...var, name)
 * Constraint ... cstr(expression1, type, expression2, ...forall)
 */

std::vector<std::function<void()>> ModuleTester::tests =
{
    []()
    {

    }
}