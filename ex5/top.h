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

SC_MODULE(Top)
{

  Consumer   *consumer;
  Producer   *producer;
  Queue queue;

  SC_CTOR(Top)
  : queue("queue",10)
  {
    consumer = new Consumer("consumer");
    producer   = new Producer( "producer");

    // stimulus instance
    consumer->in(queue);
    producer->out(queue);
  }
};

#endif

