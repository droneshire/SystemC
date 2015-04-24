#include "queue.h"

Queue::Queue(char* nm, int _sz) : sc_object(nm), sz(_sz), w(0), r(0), n(0) 
{
	data = new char[sz];
}

void Queue::write(char c)
{
	if(n++ > sz)
		sc_core::wait(read_e);
	data[w++] = c;
	w %= sz;		
	write_e.notify(SC_ZERO_TIME);
}

char Queue::read()
{
	char c = 0;
	if(n == 0)
		sc_core::wait(write_e);
	n--;
	c = data[r++];
	r %= sz;
	read_e.notify(SC_ZERO_TIME);
	return c;
}
