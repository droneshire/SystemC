#include "mon.h"

using std::cout;
using std::endl;

void Mon::monitor()
{
  cout.setf(std::ios::showpos);
  cout.width(12);
  cout << "a";
  cout.width(12);
  cout << "b";
  cout.width(12);
  cout << "f" << endl;

  while (true) {
    wait();                             // wait for 1 clock cycle
    cout.width(12);
    cout << a->read();
    cout.width(12);
    cout << b->read();
    cout.width(12);
    cout << f->read() << endl;
  }
}
