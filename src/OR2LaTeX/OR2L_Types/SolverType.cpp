#include "SolverType.h"

namespace or2l
{
std::map<SolverType, std::string> SolverTypeDictionary::types = {{SolverType::ORTOOLS_CBC, "CBC"},
                                                                  {SolverType::ORTOOLS_SCIP, "SCIP"}};
} // namespace or2l