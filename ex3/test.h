#ifndef TEST_H
#define TEST_H

#include "systemc"
using namespace sc_core;
using std::cout;
using std::endl;

SC_MODULE(Test)
{
  // Declare fifo channel
  
  sc_fifo<int> fifo;  
  sc_in<bool> clk;

  SC_CTOR(Test) : fifo("fifo",4), clk("clk"){
    SC_THREAD(producer);
	sensitive << clk.pos();
    SC_THREAD(consumer);
	sensitive << clk.pos();
  }

  void producer() {
    for (int i = 0; i < 20; i++) {
      wait();
      if(!fifo.nb_write(i)){
	i--;
	cout << "Error nb returned false" << endl;
      }
      else
	cout << "Produced " << i << endl;
    }
  }

  void consumer() {
    for (;;) {
      int data;
      wait();
      wait();
      if(!fifo.nb_read(data)){
	cout << "Error nb returned false" << endl;
	}

      cout << "Received    " << data << endl;
      if(data == 19)
	sc_stop();
    }
  }
};

#endif
