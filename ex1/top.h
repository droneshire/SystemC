#ifndef TOP_H
#define TOP_H

#include "systemc"
using namespace sc_core;

#include "stim.h"
#include "mult.h"
#include "mon.h"

SC_MODULE(Top)
{
  // signals to wire up the device under test
  sc_signal<int> asig, bsig, fsig;

  // declare a clk for the stimulus process
  sc_clock testclk;

  Stim *stim;
  Mult *mult;
  Mon  *mon;

  SC_CTOR(Top)
  : testclk("testclk", 10, SC_NS)
  {
    // Instantiate the modules
    stim = new Stim("stim");
    mult = new Mult("mult");
    mon  = new Mon("mon");
    
    // Bind the ports
    stim->a(asig);
    stim->b(bsig);
    stim->clk(testclk);

    mult->a(asig);
    mult->b(bsig);
    mult->f(fsig);

    mon->a(asig);
    mon->b(bsig);
    mon->f(fsig);
    mon->clk(testclk);
  }
};

#endif
