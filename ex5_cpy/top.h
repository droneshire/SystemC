#ifndef TOP_H
#define TOP_H

#include "systemc"
using namespace sc_core;

//#include "stim.h"
//#include "sorter.h"
//#include "mon.h"
#include "queue.h"
#include "producer.h"
#include "consumer.h"
#include "container.h"

SC_MODULE(Top)
{

  Consumer   *consumer;
  Producer   *producer;
  Container *container;

  SC_CTOR(Top)
  {
    consumer = new Consumer("consumer");
    producer   = new Producer( "producer");
    container = new Container("container");

    // stimulus instance
    consumer->in(container->producer1_exp);
    producer->out(container->consumer1_exp);
  }
};

#endif

