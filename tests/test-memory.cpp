#include "Constraint.h"
#include "MathExpression.h"
#include "Model.h"
#include "ModuleTester.h"
#include "OperatorTypes.h"
#include "Variable.h"

using or2l::Constraint;
using or2l::MathExpression;
using or2l::MathExpressionOperatorTypes;
using or2l::Model;
using or2l::Variable;

std::vector<std::function<void()>> base_types::ModuleTester::tests = {
    []() {
        // these tests are supposed to be run locally with valgrind...
        // 'ModuleTester' was tested by itself on 30/01/2021 for memory leaks
        // (nothing detected)
        Model model1("test1");
        {
            std::unique_ptr<Model> model2(new Model("CBC"));
        }
        std::unique_ptr<Model> model3(new Model("CBC"));
        model1.AddVariable(Variable("var1"));
        model1.AddVariable(Variable("var2"));
        model3->AddVariable(Variable("var1"));
        model3->AddVariable(Variable("var2"));
    },
    []() {
        std::unique_ptr<Model> model(new Model("test2"));
        model->AddVariable(Variable("var1"));
        model->AddVariable(Variable("var2"));
        // the statement below is only for the madness of it, nothing actually
        // interesting in it
        model->AddConstraint(Constraint("c1", MathExpression(*dynamic_cast<Variable *>(model->Get("var1")),
                                                             MathExpressionOperatorTypes::LESS_EQUAL, 1)));
    }};

int main()
{
    {
        base_types::ModuleTester::Run();
    }
}