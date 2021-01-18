#include "SolverType.h"

namespace or2l {
std::map<ORTSolverType, std::string> SolverType::types_ = {
    {ORTSolverType::CBC, "CBC"}, {ORTSolverType::SCIP, "SCIP"}};
}  // namespace or2l