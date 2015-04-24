#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "systemc"
using namespace sc_core;

class Comparator: public sc_module {

public:
        sc_in<int> a;
        sc_in<int> b;
        sc_out<bool> f;

        Comparator(sc_module_name _mn);
        SC_HAS_PROCESS(Comparator);
        void compare();
};

#endif
