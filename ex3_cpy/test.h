#ifndef TEST_H
#define TEST_H

#include "systemc"
using namespace sc_core;
using std::cout;
using std::endl;

SC_MODULE(Test)
{
  // Declare fifo channel
  private:
        int data_sent;
  public:

  sc_fifo<int> fifo;  
  sc_in<bool> clk;

  SC_CTOR(Test) : fifo("fifo",4), clk("clk"){
    data_sent = 0;
    SC_METHOD(producer);
	sensitive << clk.pos();
    SC_METHOD(consumer);
	sensitive << clk.pos();
  }

  void producer() {
    if(data_sent < 20){
      if(!fifo.nb_write(data_sent)){
	cout << "Error nb returned false" << endl;
      }
      else {
	      data_sent++;
	      cout << "Produced " << data_sent << endl;
      }
    }
    
  }

  void consumer() {
      int data = 0;	
      next_trigger(20, SC_NS);
	    if(!fifo.nb_read(data)){
		cout << "Error nb returned false" << endl;
	    }
	    else
		cout << "Received    " << data << endl;
      if(data == 19)
	sc_stop();
  }
  
};

#endif
