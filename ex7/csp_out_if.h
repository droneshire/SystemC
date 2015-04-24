#ifndef CSP_OUT_IF_H
#define CSP_OUT_IF_H

#include "systemc"
using namespace sc_core;

template<typename T>
class csp_out_if : virtual public sc_core::sc_interface
{
public:
	virtual void out(const T& d) = 0;
};

#endif

