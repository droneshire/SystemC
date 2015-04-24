#ifndef MUX_H
#define MUX_H

#include "systemc"
using namespace sc_core;

class Mux: public sc_module {

public:
	sc_in<int> in0;
	sc_in<int> in1;
	sc_in<int> in2;
	sc_in<int> sel;
	sc_out<int> out1;

	Mux(sc_module_name _mn);
	SC_HAS_PROCESS(Mux);
	void action();
};

#endif
