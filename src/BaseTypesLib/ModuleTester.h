#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <cassert>

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


