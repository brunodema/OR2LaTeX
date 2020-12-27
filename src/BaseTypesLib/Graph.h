#pragma once
#include <vector>
#include <functional>

#include "Coordinates.h"

namespace DEMALIB
{
	namespace BASE_TYPES
	{
		template<class T>
		class IGraph
		{
		public:
			virtual void CalculateDistanceMatrix() = 0;
			virtual T GetDistance(const Coordinates<T>& a, const Coordinates<T>& b) const { return distanceFunction(a, b); };

			IGraph() = delete;
			IGraph(IGraph&&) = default;
			virtual IGraph& operator=(const IGraph&) = default;
			virtual IGraph& operator=(IGraph&&) = default;
			virtual ~IGraph() = default;
		protected:


			std::vector<Coordinates<T>> coordinates;
			std::function<T(Coordinates<T>, Coordinates<T>)> distanceFunction;
		};

		template<class T>
		class Graph : public IGraph<T>
		{
		public:
			Graph(std::vector<Coordinates<T>> coords, std::function<T(Coordinates<T>, Coordinates<T>)> dfunc = {})
			{
				this->coordinates = coords;
				this->distanceFunction = dfunc;
			}
		};

	}
}