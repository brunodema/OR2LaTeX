#pragma once
#include <vector>
#include <iostream>
#include <initializer_list>
#include <optional>

namespace DEMALIB
{
	namespace BASE_TYPES
	{
		template <class T>
		class Vecxd : public std::vector<std::vector<T>>
		{
		public:
			Vecxd(std::initializer_list<size_t> sizes, const T& default_initializer) // the default initializer never did anything here or below... fix it
			{
				this->resize(sizes.size());
				int i = 0;
				for (auto sz : sizes)
				{
					this->at(i).resize(sz, default_initializer);
					++i;
				}
			}

			Vecxd(std::initializer_list<size_t> sizes)
			{
				this->resize(sizes.size());
				int i = 0;
				for (auto sz : sizes)
				{
					this->at(i).resize(sz);
					++i;
				}
			}

			Vecxd() {}

			void FillWith(const T& content)
			{
				for (auto& vec : *this)
				{
					std::fill(vec.begin(), vec.end(), content);
				}
			};

			void ReserveContents(const std::initializer_list<size_t> sizes)
			{
				this->resize(sizes.size()); // this one HAS to be a resize, otherwise the positions will not be reachable
				int i = 0;
				for (auto const& size : sizes)
				{
					this->at(i).reserve(size);
					++i;
				}
			};

			void ResizeContents(const std::initializer_list<size_t> sizes, const T& template_object)
			{
				this->resize(sizes.size());
				int i = 0;
				for (auto const& size : sizes)
				{
					this->at(i).resize(size, template_object);
					++i;
				}
			};

		private:
			inline void CheckInitSize(size_t M) const
			{
				if (M <= 0)
				{
					throw;
				}
			}
		};
	} // namespace BASE_TYPES
} // namespace DEMALIB