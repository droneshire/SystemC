#ifndef CSP_CHAN_H
#define CSP_CHAN_H

#include "systemc"
#include "csp_out_if.h"
#include "csp_in_if.h"

using namespace sc_core;
using std::endl;
using std::cout;

template<typename T>
class csp_chan : public csp_out_if<T>, public csp_in_if<T>
{
private:
	T data;
	bool outflag;
public:
	sc_event in_ev, out_ev;
	csp_chan(char* nm);
	virtual void out(const T& d);
	virtual const T& in(void);
};
#endif
