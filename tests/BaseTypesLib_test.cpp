#include "pch.h"
#include "../../BaseTypesLib/BaseTypesLib/inc/Vecxd.h"


TEST(DefaultConstructor, Base)
{
    DEMALIB::BASE_TYPES::Vecxd<std::string> test({ 1, 5 }, "a");
    DEMALIB::BASE_TYPES::Vecxd<double> test1({ 13, 42 }, 23.4);
    DEMALIB::BASE_TYPES::Vecxd<int> test2({ 4, 1 }, 5);
    DEMALIB::BASE_TYPES::Vecxd<int> test3({ 1,23,4,6,67,54,5 });
    EXPECT_TRUE(true);
}


TEST(DefaultConstructor, ResizeFunctions)
{
    DEMALIB::BASE_TYPES::Vecxd<size_t> test;
    //test.ResizeContents(1, 2, 4, 5);
    test.FillWith(10);
    EXPECT_EQ(test.at(1).at(1), (size_t)11);
}