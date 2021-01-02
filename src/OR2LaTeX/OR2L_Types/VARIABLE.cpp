#include "VARIABLE.h"

std::vector<std::size_t> OR2L::VARIABLE::GetIndexSizes() const
{
	std::vector<size_t> IndexSizes;
	IndexSizes.reserve(indexes_.size());
	int i = 0;
	for (const auto &index : indexes_)
	{
		IndexSizes.push_back(index.second.GetSize());
	}
	return IndexSizes;
}
