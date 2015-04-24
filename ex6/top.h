#ifndef TOP_H
#define TOP_H

// top.h
#include "bus.h"
#include "source.h"
//#include "proc.h"
#include "risc.h"
#include "mem.h"

SC_MODULE(Top)
{
  sc_clock clock;
  sc_signal<bool> halt;
  sc_trace_file *trace;

  // Module Instantiations
  Mem ram0;
  Mem ram1;
  // add another ram here and initialize it to start 32, size 32

  // bus
  Bus bus1;

  // data source ID 0
  Source source0;

  // processor, ID = 1
  // destination address starts at 16
//  Proc proc1;
  Risc risc1;

  SC_CTOR(Top)
  : clock( "clock", 100, SC_NS),
    trace(sc_create_vcd_trace_file("bus_system")),

    // memory ram0, start address 0 , size 32
    ram0("ram0", 0, 32, trace),
    ram1("ram1", 32, 32, trace),

    // bus
    bus1("bus1"),

    // data source ID 0
    source0("source0", 0, 24, 0),

    // processor, ID = 1
    // destination address starts at 16
    //proc1("proc1", 0, 32, 24, 1)
    risc1("risc1", "do_proc.asm", trace, 1)
  {

    bus1.clock(clock);
    bus1.slave_port(ram0.mem_xport);
    bus1.slave_port(ram1.mem_xport);

    source0.clock(clock);
    source0.system_bus(bus1);

    risc1.clock(clock);
    risc1.system_bus(bus1);
    risc1.halt(halt);

    // Trace external  pins
    sc_trace(trace, clock,    "clock");
    // Trace ram memory locations
    int i;
    for (i = 0; i < 32; i++)
      ram0.add_trace(i);

    // display ram status
    ram0.status();
    ram1.status();

    // dump ram contents
    ram0.dump();
    ram1.dump();

  }

  void end_of_simulation() {
    // dump slave contents
    ram0.dump();
    ram1.dump();
  }

  ~Top() {
    sc_close_vcd_trace_file(trace);
  }

};

#endif

