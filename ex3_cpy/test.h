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
	int clkcnt;
        int data_sent;
  public:

  sc_fifo<int> fifo;  
  sc_in<bool> clk;

  SC_CTOR(Test) : fifo("fifo",4), clk("clk"){
    data_sent = 0;
    clkcnt = 0;
    SC_METHOD(producer);
	sensitive << clk.pos();
    SC_METHOD(consumer);
	sensitive << clk.pos();
  }

  void producer() {
    if(data_sent < 20){
      if(!fifo.nb_write(data_sent)){
	cout << "FIFO FULL" << endl;
      }
      else {
	      cout << "Produced " << data_sent++ << endl;
      }
    }
    
  }

  void consumer() {
      int data = 0;	
      if(++clkcnt == 2){
	    if(!fifo.nb_read(data)){
		cout << "FIFO EMPTY" << endl;
	    }
	    else
		cout << "Received    " << data << endl;
	    clkcnt = 0;
      }
      if(data == 19)
	sc_stop();
  }
  
};

#endif
