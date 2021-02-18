#include "ArrayIterator.h"
#include "Bounds.h"
#include "Coordinates.h"
#include "ModuleTester.h"
#include "Vecxd.h"
#include <c++/9/bits/c++config.h>
#include <cassert>
#include <cstddef>
#include <utility>

using or2l::base_types::ModuleTester;
using or2l::base_types::MultiArray;

struct RandomStruct {
  RandomStruct(int a, double b, std::string str = "")
      : _a(a), _b(b), _str(std::move(str)) {}

  RandomStruct() = default;

  int _a;
  double _b;
  std::string _str;

  constexpr bool operator==(const RandomStruct& B) const {
    return (this->_a == B._a && this->_b == B._b && this->_str == B._str);
  }
};

std::vector<std::function<void()>> ModuleTester::tests_ = {
    []() {
      // tests default constructor
      MultiArray<std::string> test({1, 2});
      MultiArray<double> test1({13, 42});
      MultiArray<int> test2({4, 1});
      MultiArray<int64_t> test3({1, 23, 4, 6, 67, 54, 5});
    },
    []() {
      // tests the 'resizecontents' and 'fillwith' functions
      MultiArray<size_t> test;
      test.ResizeContents({1, 2, 4, 5});
      test.FillWith(10);

      assert((test[{0, 0, 0, 0}] == (size_t)10));
      assert((test[{0, 1, 1, 1}] == (size_t)10));
      assert((test[{0, 1, 2, 2}] == (size_t)10));
      assert((test[{0, 1, 3, 4}] == (size_t)10));
    },
    []() {
      // tests the same functions above, but now using a custom class as
      // argument for the multi-vector class
      MultiArray<RandomStruct> test;
      test.ResizeContents({1, 2, 3, 4});

      RandomStruct sample = {1, 5.66, "this_is_a_test"};
      test.FillWith(sample);

      assert((test[{0, 0, 0, 0}] == sample));
      assert((test[{0, 1, 1, 1}] == sample));
      assert((test[{0, 1, 2, 2}] == sample));
      assert((test[{0, 1, 2, 3}] == sample));
    },
    []() {
      // tests the multi-vector class with the 'coordinates' class.
      MultiArray<Coordinates<double>> test;
      Coordinates coord1("1", 12.00, 56.33);
      std::initializer_list<size_t> ContentsSizes = {3, 10, 100, 10, 15, 16};
      test.ResizeContents(ContentsSizes);
      test.FillWith(coord1);

      assert((test[{2, 2, 1, 3, 2, 1}] == coord1));
      assert((test[{2, 5, 4, 1, 3, 2}] == coord1));
      assert((test[{1, 3, 4, 2, 5, 1}] == coord1));
      assert((test[{1, 9, 1, 1, 1, 1}] == coord1));
    },
    []() {
      // temporary tests with the new dynamic multi-array
      MultiArray<double> test1({1});
      test1[{0}] = 10;
      // test1[{1}] = 100;  // must give runtime error: OK!
      assert(test1.dims()[0] == 1);
      assert(test1[{0}] == 10);

      MultiArray<double> test2({10, 10, 3});
      assert((test2.dims() == std::vector<std::size_t>{10, 10, 3}));
      test2[{1, 1, 2}] = 10;
      test2[{9, 9, 2}] = 100;
      // test2[{1, 1}] = 10;  // must give runtime error: OK
      // test2[{11, 1, 1}] = 10;  // must give runtime error: OK
      assert((test2[{1, 1, 2}] == 10));
      assert((test2[{9, 9, 2}] == 100));
    },
    []() {
      // test 'ArrayIterator'
      using or2l::base_types::Bounds;

      std::vector<Bounds> bnds1{{0, 2}, {0, 2}};
      ArrayIterator it1(bnds1);
      auto it1_combs = it1.Iterate();

      assert((it1_combs[0] == std::vector<std::size_t>{0, 0}));
      assert((it1_combs.back() == std::vector<std::size_t>{1, 1}));

      std::vector<Bounds> bnds2{{1, 10}, {0, 2}, {0, 30}};
      ArrayIterator it2(bnds2);
      auto it2_combs = it2.Iterate();

      assert((it2_combs[0] == std::vector<std::size_t>{1, 0, 0}));
      assert((it2_combs.back() == std::vector<std::size_t>{9, 1, 29}));

      // should be the same as above, except the overload assumes a 0 lower
      // bound
      std::vector<std::size_t> bnds3{10, 2, 30};
      ArrayIterator it3(bnds3);
      auto it3_combs = it3.Iterate();

      assert((it3_combs[1] == std::vector<std::size_t>{0, 0, 1}));
      assert((it3_combs.back() == std::vector<std::size_t>{9, 1, 29}));
    }};

int main() { return ModuleTester::Run(); }