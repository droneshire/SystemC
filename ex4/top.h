#ifndef TOP_H
#define TOP_H

#include "test.h"

SC_MODULE(Top)
{

  Test test;
  sc_clock clock;

  SC_CTOR(Top)
  : test("test"),
    clock("clock", 10, SC_NS)
  {
    test.clock.bind(clock);
  }

};

#endif
