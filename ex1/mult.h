#ifndef MULT_H
#define MULT_H

#include "systemc"
using namespace sc_core;

SC_MODULE(Mult)
{
  // ports
  sc_in<int>  a;
  sc_in<int>  b;
  sc_out<int> f;

  // process definitions
  void action();

  SC_CTOR(Mult) {
    SC_METHOD(action);
    sensitive << a << b;
  }
};

#endif
