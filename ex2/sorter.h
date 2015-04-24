#ifndef SORTER_H
#define SORTER_H

#include "systemc"
#include "comparator.h"
#include "mux.h"
#include "decode.h"

using namespace sc_core;

class Sorter: public sc_module {
public:

	Comparator c1, c2, c3;
	Mux mux;
	Decode decode;

	sc_in<int> a;
	sc_in<int> b;
	sc_in<int> c;
	sc_out<int> biggest;
	
	sc_signal<bool> a_gt_b;
	sc_signal<bool> b_gt_c;
	sc_signal<bool> c_gt_a;
	sc_signal<int> select;
	Sorter(sc_module_name _nm);
	SC_HAS_PROCESS(Sorter);
};
#endif
