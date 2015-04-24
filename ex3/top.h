#ifndef TOP_H
#define TOP_H

#include "systemc"
using namespace sc_core;

#include "test.h"

SC_MODULE(Top)
{
  
  Test test;
  sc_clock testclk;

  SC_CTOR(Top)
  : test("test"), testclk("testclk", 10, SC_NS)
  {
	test.clk.bind(testclk);
  }
};

#endif
