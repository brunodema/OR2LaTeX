This README aims to clarify the implementation associated with the files contained in this folder.

# Definitions

The following definitions help define the goals and scope of the implementations present here:

1. **A symbol can be generally defined as an unique mathematical identifier within a delimited context (usually a model)**. Common symbols in these secnarios are variables, indexes, and even contraints. For example, it makes no sense for a model to have an index called `x` and a varable called `x` at the same time.
1. **An indexed symbol is a symbol which has indexes attached to it**. An indexed symbol is the parent class of other classes such as `Variable` and `Constant`, since a general symbol such as those can be extended to further represent multiple others associated to the base one. For example, a `Variable` called `x` can be associated with indexes called `i` and `j`, both with lower bound equal to 0 and upper bound equal to 10. A single symbol can then be extended to 20 other ones, which are represented by the different unique combinations between the indexes.
1. **An index is a symbol which has delimited bounds (ex: 0 to 10) and that can be attached to other symbols to represent multiple unique derived objects**. As mentioned above, an index can be attached to other symbols to extended the representation of a single object to multiple ones - this comes in handy when setting up mathematical models. An example would be an index called `i` with bounds of [0,20].
1. **A constraint is a mathematical relationship between symbols and numeric types which comprises of inner expressions, mathematical operators, and associated indexes.** These are one of the cornerstones of matehmatical programming, since these relationships are usually inserted into mathematical models and must be respected in order to achieve the desired result. Ex: `x_{ij} == 1 for 0 <= i,j <= 20.`  
1. **An inner expression is a mathematical relatioship between different types/coefficients and numeric types.** Inner expressions are used inside constraints, specifically in the LHS and RHS of these expressions. An inner expression will have an associated type, which will be mapped to determine the coefficient values for each unique symbol in it. Considering a variable `x`, and a constant `c`, an example of an inner expression would be `x + 2* y + 3.00`. As it can be noticed, a lot of operator interaction happens between each object, even if this not seem apparent at first sight.
1. **An expression is an inner expression which also considers mutaded inner expressions - i.e., summation operators.** Since these mutaded inner expressions always have an inner expression associated with them, these are uniquely identified by the indexes associated with the operators, so mathematical operations can be done upon them. Ex: SUM_{i = 0}^{10} x_{ij} + SUM_{i = 0}^{10} y_{ij}.
1. **An mathematical expression is the junction of the LHS and RHS expressions, plus a mathematical operator such as `==`, `<=`, or `>=`.** Pretty much, it is a constraint without the final step, which is setting the associated indexes of the entire expression. Note: it is not required to have indexes associated to a constraint though.

As the current files are still being worked on, this set of might change in the future.

# Current efforts

Currently, the relationships between the internal objects of inner expressions are being implemented into the library. Even though a first version was established (an was consolidatet through testing), it was not prooven scalable. Take the following case as an example:

* Let's focus on the LHS and RHS of constraints. These must allow different symbols to be summed/subtracted/multiplied/divided between each other (**according to linear programming rules**). This is done by mapping each unique object - for instance variables `x` and `y`, constant `c`, and a scalar number 3.40 - with its associated coefficient (a numeric value).
* This can be achieved by writing the operators for each possible operation considering the involved types in the process. Taking the example above into consideration and the sum operator (+), functions for `Variable + number`, `Variable + Constant`, `Constant + number`, and so on, would need to be written.
* Three issues arise from this. First, **the goal of the library is to provide an intuitive interface for mathematical programming. Therefore, the user should be able to do these operations on the fly, without any ugly explicit declarations, for example**. An example would be directly declaring a constraint as: 

```C++
Variable x("x");
Constant c("c");

Constraint cstr(x + c + 1.00 <= 5.00, {}); // the empty set '{}' shows that no indexes will be considered during the constraint expasion
```

* Taking the LHS as an example, the `+` operator supersedes constructor operations, which mean that an operator of type `(const Variable& lhs, const Variable& rhs)` will be used. As it can be seen, this operator would apply only if `Variable` objects were being summed, which is not the case (this does not eliminate the need to implement it, though). In our case, an operator such as `(const Variable& lhs, const Constant& rhs)` would need to be implemented. Here comes the second problem: **C++ operators are not commutative by nature.** In other words, a reverse operator `(const Constant& lhs, const Variable& rhs)` would also be required, even though its functionality could be the same as the previous one.
* The final problem is: operations between types also need to established, specially in the case of sibling types (such as `Variable` and `Constant`). This requires the introduction of even more operators and conversion processes.
* **Needless to say, this implementation plan scales HORRIBLY.**
* The obvious and valid case for this situation would be to implement type templates to deal with this. The question is: **how to efficiently implement this, while also enabling the user freedom when using the resulting class?**
* To solve this problem, a new programming sheet was created on https://godbolt.org/ (aka Compiler Explorer) only to test type inheritance and intra-classes' operations. The main goals were to (1) establish the requirements for a templated class to work, (2) determine the minimum number of operator speacialziations to enable all possible operations between the concerned types.
* As of now (04/04/2021), this was achieved by the usage of a new `InnerExpression` class, alongside helper classes such as `or2l::type_traits` and `or2l::inheritance_traits` to set the correct template type deduction out of this operations. Several test classes (+- 14) were set for the sum operator, resulting in 19 different function templates. In the worst case scenario, 19 variations of these operators would need to be implemented, however, many of them (maybe 50%) would be commutative ones.
* This concept is currently being ported to the code, which will also need to consider the actual business rules of each operation, and not only the type/inheritance aspects of them.

This approach was designed entirely by me, so I would say that it definitely can still be improved with expert advice. However, it is already a *feasible* way to fix the previous scalability problems, while also providing an interface for mathematical operations between types, which was not even in the original plan - depending on the final complexity of this part of the project, I might port this to an individual sub-module.

As of 20/02/2021, great advances in terms of doce design was acheived, however, the oversight when considering that objects such as constants can also be coefficients (that is, there is the possibility of nested `InnerExpression` objects), and that exponential expressions are also valid within this context (ex: 1 + c²), it will be necessary to (1) enable support for exponential calculations (probably replace the base type of coefficients from `double` to a struct `PoweredCoefficient` containing the exponential index ()1, 2, 3, ...) and the actual coefficient value (numerica value of an object). It will also be necessary to refactor the tests to eliminate redundant ones (the test file is currently very polluted visually).

All the afore-mentioned details can be observed in the branch called `operator_reformulation`.
