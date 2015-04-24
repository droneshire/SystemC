#include "mux.h"

Mux::Mux(sc_module_name _nm): sc_module(_nm)
{
	SC_METHOD(action);
		sensitive << in0 << in1 << in2 << sel;
}

void Mux::action()
{
	switch(sel) {
		case 0:
			out1 = in0;
			break;
		case 1:
			out1 = in1;
			break;
		case 2:
			out1 = in2;
			break;
		default:
			out1 = -1;
			break;
		
	}
}
