#include "comparator.h"

Comparator::Comparator(sc_module_name _nm): sc_module(_nm)
{
        SC_METHOD(compare);
                sensitive << a << b;
}

void Comparator::compare()
{
	f = (a > b);
}


