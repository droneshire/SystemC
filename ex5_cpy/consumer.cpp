#include "consumer.h"

Consumer::Consumer(sc_module_name _nm) : sc_module(_nm), in("in")
{
	SC_THREAD(get_read);
}

void Consumer::get_read()
{
	std::ostringstream oss;
	char in_c;

	for(;;){
		sc_core::wait(SC_ZERO_TIME);
		in_c = in->read();
		oss << "read: " << in_c << " @ " << sc_time_stamp();
		SC_REPORT_INFO("CONSUMER", oss.str().c_str());
		oss.str("");
		if(in_c == 'z')
			sc_stop();
	}
}
