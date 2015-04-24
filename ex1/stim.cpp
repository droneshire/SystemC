#include "stim.h"

void Stim::action()
{

  wait();
  a = 100;
  b = 200;
  wait();
  a = -10;
  b = 23;
  wait();
  a = 25;
  b = -3;
  wait();
  a = 5000;
  b = -5000;
  wait();

  sc_stop();
}
