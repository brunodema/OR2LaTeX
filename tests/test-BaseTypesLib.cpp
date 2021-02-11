#include "Coordinates.h"
#include "ModuleTester.h"
#include "Vecxd.h"
#include <cassert>
#include <utility>

using or2l::base_types::ModuleTester;

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
      // tests default constructor and default initialization
      Vecxd<std::string> test({1, 5}, "a");
      Vecxd<double> test1({13, 42}, 23.4);
      Vecxd<int> test2({4, 1}, 5);
      Vecxd<int> test3({1, 23, 4, 6, 67, 54, 5}, 0);
    },
    []() {
      // tests the 'resizecontents' and 'fillwith' functions
      Vecxd<size_t> test;
      test.ReserveContents({1, 2, 4, 5});
      test.ResizeContents({1, 2, 4, 5}, 10);

      assert(test.at(0).at(0) == (size_t)10);
      assert(test.at(1).at(1) == (size_t)10);
      assert(test.at(2).at(2) == (size_t)10);
      assert(test.at(3).at(3) == (size_t)10);
    },
    []() {
      // tests the same functions above, but now using a custom class as
      // argument for the multi-vector class
      Vecxd<RandomStruct> test;
      test.ResizeContents({1, 2, 3, 4}, {});

      RandomStruct sample = {1, 5.66, "this_is_a_test"};
      test.FillWith(sample);

      assert(test.at(0).at(0) == sample);
      assert(test.at(1).at(1) == sample);
      assert(test.at(2).at(2) == sample);
      assert(test.at(3).at(3) == sample);
    },
    []() {
      // tests the multi-vector class with the 'coordinates' class.
      Vecxd<Coordinates<double>> test;
      Coordinates coord1("1", 12.00, 56.33);
      std::initializer_list<size_t> ContentsSizes = {3, 10, 100, 10, 15, 16};
      test.ResizeContents(ContentsSizes, coord1);

      assert(test.at(0).at(0) == coord1);
      assert(test.at(1).at(1) == coord1);
      assert(test.at(2).at(2) == coord1);
      assert(test.at(3).at(3) == coord1);
    },
    []() {
      // temporary tests with the new dynamic multi-array
      MultiArray<double> test1({1});
      test1[{0}] = 10;
      // test1[{1}] = 100;  // must give runtime error: OK!
      assert(test1.dims()[0] == 1);
      assert(test1[{0}] == 10);

      MultiArray<double> test2({10, 10, 3});
      assert((test2.dims() == std::vector<int>{10, 10, 3}));
      test2[{1, 1, 2}] = 10;
      test2[{9, 9, 2}] = 100;
      // test2[{1, 1}] = 10;  // must give runtime error: OK
      // test2[{11, 1, 1}] = 10;  // must give runtime error: OK
      assert((test2[{1, 1, 2}] == 10));
      assert((test2[{9, 9, 2}] == 100));
    }};

int main() { return ModuleTester::Run(); }