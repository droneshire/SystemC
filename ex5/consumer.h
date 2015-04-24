#ifndef CONSUMER_H
#define CONSUMER_H

#include "systemc"
#include "queue_if.h"

using namespace sc_core;
using std::ostringstream;
using std::string;

class Consumer: public sc_module {
public:
	sc_port<queue_if> in;
	void get_read();

	Consumer(sc_module_name _nm);
	SC_HAS_PROCESS(Consumer);
};
#endif
