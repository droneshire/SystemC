#ifndef PRODUCER_H
#define PRODUCER_H

#include "systemc"
#include "queue_if.h"

using namespace sc_core;
using std::ostringstream;

class Producer: public sc_module {
public:
	sc_port<queue_if> out;
	void send_write();

	Producer(sc_module_name _nm);
	SC_HAS_PROCESS(Producer);
};
#endif
