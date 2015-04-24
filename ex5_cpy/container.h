#ifndef CONTAINER_H
#define CONTAINER_H

#include "systemc"
using namespace sc_core;

//#include "stim.h"
//#include "sorter.h"
//#include "mon.h"
#include "queue.h"
#include "producer.h"
#include "consumer.h"

SC_MODULE(Container)
{

  sc_export<queue_if> producer1_exp;
  sc_export<queue_if> producer2_exp;
  sc_export<queue_if> consumer1_exp;
  sc_export<queue_if> consumer2_exp;

  Queue queue1;
  Queue queue2;

  SC_CTOR(Container)
  : queue1("queue1",4), queue2("queue2", 4)
  {
	producer1_exp.bind(queue1);
	consumer1_exp.bind(queue1);
	producer2_exp.bind(queue2);
	consumer2_exp.bind(queue2);
  }

};

#endif

