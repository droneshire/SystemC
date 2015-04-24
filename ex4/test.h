#ifndef TEST_H
#define TEST_H

#include "systemc"
using namespace sc_core;
using std::cout;
using std::endl;

SC_MODULE(Test)
{
  sc_in<bool>  clock;

  sc_fifo<sc_dt::sc_int<8> > fifo;

  sc_dt::sc_int<8>  count;
  sc_dt::sc_int<8>  data;

  bool odd;

  SC_CTOR(Test)
  : fifo(4), count(0), odd(false)
  {
    SC_METHOD(producer);
      sensitive << clock.pos();
    SC_METHOD(consumer);
      sensitive << clock.pos();
  }


  void producer()
  {
    if (!fifo.nb_write(count))
      cout << "Error writing to fifo" << endl;
    cout << "Produced " << count << endl;
    ++ count;
  }

  void consumer()
  {
    if (odd)
    {
      if (!fifo.nb_read(data))
        cout << "Error reading from fifo" << endl;
      cout << "Received    " << data << endl;
      if (data > 19) sc_stop();
    }
    odd = !odd;
  }
};

#endif
