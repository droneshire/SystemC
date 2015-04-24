#ifndef QUEUE_H
#define QUEUE_H

#include "queue_if.h"
#include "systemc"
using namespace sc_core;

class Queue : public queue_if, public sc_object
{
    public:
	sc_event read_e, write_e;
	Queue(char* nm, int _sz);
	void write(char c);
	char read();
    private:
	char* data;
	int sz, w, r, n;
};

#endif 
