#ifndef STIM_H
#define STIM_H

#include "systemc"
using namespace sc_core;

SC_MODULE(Stim)
{
  sc_in<bool> clk;
  sc_out<int> a;
  sc_out<int> b;

  void action();

  SC_CTOR(Stim) {
    SC_THREAD(action);
    sensitive << clk.pos();
  }
};

#endif
