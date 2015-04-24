#ifndef CSP_IN_IF_H
#define CSP_IN_IF_H

#include "systemc"
using namespace sc_core;

template<typename T>
class csp_in_if : virtual public sc_core::sc_interface
{
public:
	virtual const T& in() = 0;
};

#endif

