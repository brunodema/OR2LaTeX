#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <cassert>
#include <exception>

#define ASSERT_THROW(STATEMENT, EXCEPTION_TYPE) try { STATEMENT; throw; } catch(const EXCEPTION_TYPE& e) {}
#define ASSERT_THROW_ALL(STATEMENT) try { STATEMENT; throw; } catch(...) {}

namespace DEMALIB
{
	namespace BASE_TYPES
	{
		class ModuleTester : std::vector<std::function<void()>>
		{
		public:
			static std::vector< std::function<void()>> tests;

			static int Run()
			{
				std::cout << tests.size() << " tests detected.\n";
				for (auto& test : tests)
				{
					test();
					std::cout << "test executed.\n";
				}
				return 0;
			}
		};
	}
}


