#ifndef MON_H
#define MON_H

#include "systemc"
using namespace sc_core;

SC_MODULE(Mon)
{
  // ports
  sc_in<int> a;
  sc_in<int> b;
  sc_in<int> f;
  sc_in<bool> clk;

  void monitor();

  SC_CTOR(Mon) {
    SC_THREAD(monitor);
    sensitive << clk.neg();
  }
};

#endif
