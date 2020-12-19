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
			Vecxd(std::initializer_list<size_t> sizes, T default_initializer = {})
			{
				this->resize(sizes.size());
				int i = 0;
				for (auto sz : sizes)
				{
					this->at(i).resize(sz);
					++i;
				}
				FillWith(default_initializer);
			}

			Vecxd(std::vector<size_t> sizes, T default_initializer = {})
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

			Vecxd(const Vecxd&) = default;
			Vecxd(Vecxd&&) = default;
			virtual Vecxd& operator=(const Vecxd&) = default;
			virtual Vecxd& operator=(Vecxd&&) = default;
			virtual ~Vecxd() = default;

			void FillWith(const T& content)
			{
				for (auto& vec : *this)
				{
					std::fill(vec.begin(), vec.end(), content);
				}
			};
			void ResizeContents(const std::initializer_list<size_t> sizes)
			{
				this->resize(sizes.size());
				int i = 0;
				for (auto const& size : sizes)
				{
					this->at(i).resize(size);
					++i;
				}
			};
			//void Resize(const std::vector<size_t>& sizes);

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