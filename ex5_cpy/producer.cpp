#include "producer.h"

Producer::Producer(sc_module_name _nm) : sc_module(_nm), out("out")
{
	SC_THREAD(send_write);
}

void Producer::send_write()
{
	std::ostringstream oss;
	std::string txt = "abcdefghijklmnopqrstuvwxyz";

	for(int i = 0; i < txt.length(); i++) {
		out->write(txt[i]);
		oss << "write: " << txt[i] << " @ " << sc_time_stamp();
		SC_REPORT_INFO("PRODUCER", oss.str().c_str());
		oss.str("");
	}
}
