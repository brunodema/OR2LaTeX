#include "VARIABLE_SET.h"

void OR2L::VARIABLE_SET::PopulateSet() // rework to 'actually' make V.O.
{
	std::vector<size_t> index_lengths = this->_variable.GetIndexSizes();
	int i = 0;
	for (auto length : index_lengths)
	{
		this->_variables.at(i++).resize(length);
	}
}
