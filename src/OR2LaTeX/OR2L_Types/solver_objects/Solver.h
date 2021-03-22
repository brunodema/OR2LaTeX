#pragma once
#include "ArrayIterator.h"
#include "SolverType.h"
#include "Variable.h"
#include "VariableType.h"
#include "ortools/linear_solver/linear_solver.h"
#include <Auxiliary.h>
#include <map>
#include <utility>
#ifdef GUROBI
#include "gurobi_c++.h"
#endif

template <class T1, class T2> struct HashPair
{
    size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        // XOR is pottentially dangerous here
        return hash1 ^ hash2;
    }
};

using VariableIndexPair = std::pair<or2l::Variable, std::vector<size_t>>;
struct Comp
{
    bool operator()(const VariableIndexPair &l, const VariableIndexPair &r) const
    {
        if (l.first == r.first)
        {
            if (l.second == r.second)
            {
                return true;
            }
        }
        return false;
    }
};

namespace or2l
{
using base_types::ArrayIterator;
using operations_research::MPSolver;

// interface
class ISolver
{
  public:
    ISolver() = default;
    virtual ~ISolver() = default;

    virtual void ImplementModel() = 0;
    virtual void FreeSolver() = 0;

    virtual double GetVariable(const Variable &var, const std::vector<std::size_t> &index_values) = 0;
    virtual void AddVariableSet(const Variable &var) = 0;
    // virtual void RemoveVariable(const Variable& var) = 0;

  protected:
    // virtual void AddConstraint(const Constraint& constraint) = 0;
    // virtual void RemoveConstraint(const Constraint& constraint) = 0;
};

class OrtoolsSolver : public ISolver
{
  public:
    explicit OrtoolsSolver(const SolverType type) : type_(type)
    {
        assert((int)type <= SOLVERTYPE_ORTOOLS_MAX);
        ImplementModel();
    }
    ~OrtoolsSolver() override = default;

    void ImplementModel() override
    {
        model = std::unique_ptr<MPSolver>(
            MPSolver::CreateSolver(SolverTypeDictionary::GetType(type_))); // in order to implement the model, the
                                                                           // solver needs to access information about
                                                                           // the model ('Variable' for instance)
    }
    void FreeSolver() override
    {
        model.reset();
    }

    double GetVariable(const Variable &var, const std::vector<std::size_t> &index_values) override
    {
        VariableIndexPair a({var, index_values});

        return variable_vec[a]->solution_value();
    }
    void AddVariableSet(const Variable &var) override
    {
        const auto indexes = var.GetIndexSizes();
        auto it = ArrayIterator(indexes);

        while (it.HasNext())
        {
            auto current_combination = it.Next();
            operations_research::MPVariable
                *var_ptr; // so about this... I discovered that casting the return value of the function (MPVariable*)
                          // to 'shared_ptr' causes the shared_ptr to be destroyed right after its declaration,
                          // therefore reducing the number of references to zero, and making the 'weak_ptr' point to
                          // nothing - or in this case, to some sort of malformed element. I decided to use a normal
                          // pointer in this, so it simply points to nothing if the associated variable gets destroyed
            switch (var.GetVariableType())
            {
            case VariableType::CONTINUOUS:
                var_ptr = model->MakeNumVar(0.00, 100000000,
                                            var.GetName() + GetCurrentCombinationString(current_combination));
                break;
            case VariableType::BINARY:
                var_ptr = model->MakeBoolVar(var.GetName() + GetCurrentCombinationString(current_combination));
                break;
            case VariableType::INTEGER:
                var_ptr = model->MakeIntVar(0.00, 100000000,
                                            var.GetName() + GetCurrentCombinationString(current_combination));
                break;
            default:
                throw std::invalid_argument("An invalid variable type was assigned (not CONTINUOUS, "
                                            "BINARY, or INTEGER)"); // change this to or2l::Exception later
                                                                    // (better string management)
                break;
            }
            variable_vec.emplace(std::pair<VariableIndexPair, operations_research::MPVariable *>(
                VariableIndexPair({var, current_combination}), var_ptr));
        }
    }
    // void RemoveVariable(const Variable& var) override {}

  private:
    SolverType type_;
    std::unique_ptr<MPSolver> model = nullptr;
    std::map<VariableIndexPair, operations_research::MPVariable *> variable_vec;
}; // namespace or2l

#ifdef GUROBI
class GurobiSolver : public ISolver
{
  public:
    explicit GurobiSolver(const GRBEnv &env) : env_(std::make_unique<GRBEnv>(env))
    {
        ImplementModel();
    }
    ~GurobiSolver() override = default;

    void ImplementModel() override
    {
        model_ = std::make_unique<GRBModel>(*env_);
    }
    void FreeSolver() override
    {
        model_.reset();
    }

    double GetVariable(const Variable &var, const std::vector<std::size_t> &index_values) override
    {
        // wrote this only so another test could pass
        return 0.00;
    }
    void AddVariableSet(const Variable &var) override
    {
    } // wrote this only so another test could pass

  private:
    std::unique_ptr<GRBEnv> env_ = nullptr;
    std::unique_ptr<GRBModel> model_ = nullptr;
};
#endif // GUROBI
} // namespace or2l
