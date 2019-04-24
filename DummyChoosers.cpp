#include "DummyChoosers.hpp"
#include <stdlib.h>

std::string RandomChooser::choose(size_t length)
{
	std::string r = "";
	for (size_t i = 0; i < length; ++i)
	{
		char c = '0' + (rand() % 10);
		r += c;
	}
	return r;
}
