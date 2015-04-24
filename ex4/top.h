#ifndef TOP_H
#define TOP_H

#include "test.h"

SC_MODULE(Top)
{

  Test test;
  sc_clock clock;
  sc_trace_file *filehandle;

  SC_CTOR(Top)
  : test("test"),
    clock("clock", 10, SC_NS)
  {
    test.clock.bind(clock);
    sc_report_handler::set_actions("PRODUCER", SC_ERROR, SC_DISPLAY | SC_CACHE_REPORT);
  
    sc_report_handler::set_actions("PRODUCER", SC_INFO, SC_LOG);

    sc_report_handler::set_actions("CONSUMER", SC_INFO, SC_LOG);
    sc_report_handler::set_log_file_name("log.txt");
    sc_report_handler::set_actions("CONSUMER", SC_ERROR, SC_DISPLAY | SC_CACHE_REPORT);
  }
  void start_of_simulation()
  {
    filehandle = sc_create_vcd_trace_file("filename");
    sc_trace(filehandle, clock, "clock");
    sc_trace(filehandle, test.count, "count");
    sc_trace(filehandle, test.data, "data");
    sc_trace(filehandle, test.odd, "odd");
  }

};

#endif
