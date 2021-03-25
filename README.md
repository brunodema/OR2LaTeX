[![CMake](https://github.com/brunodema/OR2LaTeX/workflows/CMake/badge.svg?branch=master)](https://github.com/brunodema/OR2LaTeX/actions)

# OR2LaTeX
A (concept) project to facilitate the integration of O.R. tools (Operations Research) and LaTeX.

## Latest Updates

(25/03/2021) Currently, the project is focusing on the first half of roadmap: the solver encapsulation into a generic mathematical programming platform. It is currently being tested the creation of variables and constraints into this new format, and its implementation in different solver libraries. I am currently stuck at the abstractio layer of the constraint object. I am trying to refactor the code related to the symbolic operations between `Variable` and constants, and also implement `ExpandableExpressions`(summations, for instance).

## Goals

The idea of this project is two-fold:

1. Encapsulate popular solver libraries into a common interface, with the goal of operating more on a mathematical level than a programmatic one.
2. Offer two-way parsing for mathematical models and LaTeX files. This would enable developers to quickly try mathematical models presented in journals, which usually are presented using LaTeX. The other way around is also valid: developers can spend less time writing their code in another language, and also achieve a higher level of safety when adapting the data from one media to another.

While the first point aims to decouple mathematical models from specific libraries, allowing more freedom for researchers to test their models with different ones, the second aims to reduce the time (and annoyance) involved in transitioning models from/to the text format.

Given that one of the core ideas is to allow developers to use multiple solver interfaces, this brings us to our first topic: dependencies.

## Dependencies

The current dependencies of the project are the following:

* [BaseTypesLib](https://github.com/brunodema/BaseTypesLib): The goal of this library is to provide common types for general usage. Contains wrappers for regex classes, multi-dimensional arrays, test frameworks, and so on. This library is also developed by me, which means that it is pretty "hand-made" :)

* [or-tools](https://github.com/google/or-tools): *If a library for something already exists, it is probably better than whatever you were planning to do in the first place.* OK, this sentence was made up by myself, but I find it pretty valid for this case. OR-Tools is a library developed by Google + its community, which is designed to offer pretty much the same goal of point (1) of this project. Not only this library offer wrappers for multiple solvers (seriously, there is a bunch of solvers comtemplated by this library), but it also presents actual algorithms for well-known problems, like TSPs, VRP, Bin-packing, etc. One major point about this library is that the compiled code can be very "heavy" (storage-wise), and that its releases contain (currently), only release mode binaries. [Let's see if this change in the future](https://github.com/google/or-tools/issues/2351).

* [GoogleTest](https://github.com/google/googletest): One of the most popular testing frameworks, GoogleTest is starting to be implemented in this project in order to avoid issues with assertions and testing in general. Given the popularity of this library (for good reasons), this will eventually replace the hand-made testing framework from `BaseTypesLib`.

* (optional) [Gurobi](https://www.gurobi.com/): Given my previous experiences with Gurobi, initial tests are also being designed with its academic library, in order to test the 'cross-solver' concept of this library. It is important to note that this library aims to directly wrap the Gurobi solver, meaning that it does not use the `or-tools` wrapper for it (this might change in the future), which can potentially impact performance in a good way.

## Installing

This library was built based on [CMake](https://cmake.org/). It is also recommended to use [git](https://git-scm.com/), for obvious reasons. This library supports cross-compilation (Windows/Ubuntu), so any problems with this should be reported. Additionally, [clang-format](https://clang.llvm.org/docs/ClangFormat.html), [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), and [cmake-format](https://pypi.org/project/cmake-format/0.2.0/), are used as auxiliary tools for code formatting/analysis.

It should be noted that:

* If debug capabilites are desired, **it is necessary to download and build the Debug version of `or-tools` manually.** Otherwise, compilation errors will happen when building the code. This might be changed in the future, by setting `or-tools` as a `FetchContent`dependency again (see [this](https://cmake.org/cmake/help/latest/module/FetchContent.html)). As a workaroung, you can try building it with using the 'RelWithDebugInfo' category from CMake, which enables partial debugging capabilities on Release mode. 
* This library offers some sort of support for the `Find<module>.cmake` syntax, even going out of his way to try to locate libraries on the host. What this means is that the procedure in these files will, when possible, download dependencies and compile them as part of the CMake compilation flow. In other cases this is not possible, since some dependencies are not open-source, or even hosted on Github (like Gurobi). **The main example is consuming `or-tools` in Release mode. This library will attempt to download the latest binaries using `FetchContent` instead of manually building the entire library.**

First, clone the repository

```
git clone https://github.com/brunodema/OR2LaTeX.git
```

After ensuring that all dependencies are installed, the following should be enough to create the build files (assuming that you are inside the `OR2LaTeX` folder):

```
cmake . -DBUILD_TESTING=ON -DUSE_GUROBI=ON -DCMAKE_PREFIX_PATH="C:\Program Files (x86)\ortools"
```

The example above compiles tests, searches for the Gurobi libraries (which are not obligatory), and sets the search path for the `or-tools` dependency (for example, if you are using Debug mode). Please note that, depending on the dependency, different installation options will be available for each of them. Please explore the source files inside the `cmake` folder (and change them if necessary).

The last thing remaining is to build the library:

```
cmake --build build
```

There you go, eveything should be set now.

## Concept

The following lines showcases what this library aims to achieve with the help of some 'imaginary' code (not all of it though!). Let's start with a simple bin-packing model:

![bin-packing](https://i.stack.imgur.com/KJmQO.png)

Here, we have all the classic elements in an O.R mathematical model: objective function, variables, indexes, constraints, constraint domains, and so on. These elements could be declared as follows in `OR2LaTeX`:

```C++
#include "OR2L_Types/Model.h"
#include "OR2L_Types/Variable.h"
#include "OR2L_Types/Index.h"

int main()
{
  or2l::Model model("NomeDoModelo");
  
  or2l::Index i("i", 0, 20);
  or2l::Index j("i", 0, 20);
  
  or2l::Variable x("x", or2l::VariableType::BINARY, {i, j});
  or2l::Variable y("y", or2l::VariableType::BINARY, {i});
  
  model.AddVariable(x);
  model.AddVariable(y);
  
  model.DefineModel(or2l::SolverType::CBC);
  model.ImplementeModel();
}
```

The snippet above declares a model, indexes, and variables, which are posteriorly added to the model. Note that, in order to achieve logical sense when converting the code into LaTeX, and to the general text format, all symbols must have unique names/identifiers. A symbols is defined as a model, an index, a variable, and so on. After all, it makes no sense to have an index and a variable called 'x' in the same model. 

Just as an index is declared with a name and bounds (lower and upper), a variable must have a name, a type (continuous, binary, integer), and associated indexes. After declaring these symbols, they can be added to a model. Finally, a model can be defined (in this case [CBC](https://projects.coin-or.org/Cbc)), and the model implemented. Note that this example, just as the entire project, is a big WIP.

## About Me

Even though I have been messing with coding in general since I was 15, my first actual experiences with programming were between 2011 - 2017, while I was graduating in Chemical Engineering. Most of these experiences were related with engineering tools like Aspen Plus, COMSOL, Matlab, Fortran, VBA and C++. In 2018, I started working with Operations Reasearch, focusing on mathematical models designed for the optimization of integrated logistic systems. Most of my work in this area was related to algorithm framework development using CLI C/C++ apps. During this period, I also worked as full-stack developer, in a Outsystems based project. More recently, I started working as a software developer, where I deal with C# development (.NET Framework, .NET Core), C/C++ (Win32), CMake, SQL, network management, and so many other recurring tools in the world of development. I also have a pet project called [FlashMEMO](https://brunodema.outsystemscloud.com/Main/Welcome), which is a learning platform based on Flashcards and the SRS method. All these personal projects of mine have the goal of extend my knowledge of programming tools, and also to learn and apply the most recent architecture and coding guidelines.     

## Contribute

**Even though this is a private project, I am very open, and also encourage, other people to contribute to the idea of this project. If you have any ideas, feedback, or will to help, do not hesitate to contact me!**
