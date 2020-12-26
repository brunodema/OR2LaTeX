#include "VARIABLE_SET.h"

void OR2L::VARIABLE_SET::PopulateSet() // rework to 'actually' make V.O.
{
	std::vector<size_t> index_lengths = this->template_variable_.GetIndexSizes();
	int i = 0;
	for (auto length : index_lengths)
	{
		this->variable_objects.at(i++).resize(length); // prone to errors... verify this later
	}
}
