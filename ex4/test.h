#ifndef TEST_H
#define TEST_H

#include "systemc"
using namespace sc_core;
using std::cout;
using std::ostringstream;
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
    std::ostringstream logger;
    if (!fifo.nb_write(count))
        SC_REPORT_ERROR("PRODUCER", "Error writing from fifo");
    logger << "Produced    " << count;
    SC_REPORT_INFO("PRODUCER", logger.str().c_str());
    ++ count;
  }

  void consumer()
  {
    std::ostringstream logger;
    if (odd)
    {
      if (!fifo.nb_read(data))
        SC_REPORT_ERROR("CONSUMER", "Error reading from fifo");
      logger << "Received    " << data;
      SC_REPORT_INFO("CONSUMER", logger.str().c_str());
      if (data > 19) sc_stop();
    }
    odd = !odd;
  }
};

#endif
