#pragma once
#include <iostream>

namespace DEMALIB
{
	namespace BASE_TYPES
	{
		template<class T = double>
		class Coordinates
		{
		public:
			std::string Id = "";
			T x;
			T y;

			Coordinates(const std::string pId, const T px, const T py) : Id(pId), x(px), y(py) {}
			Coordinates() {}

			bool operator==(const Coordinates<T>& B) const // the comparisson will target the coordinates themselves, not ids
			{
				return this->x == B.x && this->y == B.y;
			};
		private:
			//shared_ptr dsda;
		};
	}
}