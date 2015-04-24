#include "mon.h"

#include <iomanip>
using std::cout;
using std::endl;
using std::setw;

void Mon::action()
{
  

  // write header
  cout << setw(4)  << "a"
    << setw(4)  << "b"
    << setw(4)  << "c"
    << setw(10) << "biggest" << endl;

  int exp_big = 0;

  for (;;)
  {
    wait();                             // wait for 1 clock cycle
    exp_big = a; 
	
	
    if(a < b && a < c) {
	if(b < c)
		exp_big = c;
	else
		exp_big = b;
    }
    else if(a < b && a > c) {
	exp_big = b;
    }
    else if(a > b && a < c) {
	exp_big = c;
    }
    else if(a == b && a < c) {
	exp_big = c;
    }
    else if(a == c && a < b) {
 	exp_big = b;
    }
	
    cout << setw(4)  << a->read()
      << setw(4)  << b->read()
      << setw(4)  << c->read()
      << setw(10) << biggest->read() 
      << setw(10) << "Result: " 
      << setw(4)  << ((biggest->read() == exp_big) ? "CORRECT" : "FAIL") << endl;  
//    cout << setw(4)  << "Expected " << exp_big << "Got " << biggest->read() << endl;
  }
}
