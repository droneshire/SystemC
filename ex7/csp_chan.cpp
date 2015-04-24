#include "csp_chan.h"

template<typename T>
csp_chan::csp_chan(char * nm) : sc_object(nm)
{}

template<typename T>
void csp_chan<T>::out(const T& d)
{
	outflag = true;
	data = d;
	out_ev.notify();
	wait(in_ev);
	outflag = false;
	out_ev.notify();
	wait(in_ev);
}

template<typename T>
const T& csp_chan<T>::in()
{
	if(!outflag)
		wait(out_ev);
	in_ev.notify();
	T& d = data;
	wait(out_ev);
	in_ev.notify();
	return d;
}

