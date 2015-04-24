#include "sorter.h"

Sorter::Sorter(sc_module_name _nm) : sc_module(_nm), c1("c1"), c2("c2"), c3("c3"), mux("mux"), decode("decode") 
{
	c1.a.bind(a);
	c1.b.bind(b);
	c1.f.bind(a_gt_b);

	c2.a.bind(b);
	c2.b.bind(c);
	c2.f.bind(b_gt_c);
	
	c3.a.bind(c);
	c3.b.bind(a);
	c3.f.bind(c_gt_a);

	decode.in0.bind(a_gt_b);
	decode.in1.bind(b_gt_c);
	decode.in2.bind(c_gt_a);
	decode.out1.bind(select);

	mux.in0.bind(a);
	mux.in1.bind(b);
	mux.in2.bind(c);
	mux.sel.bind(select);
	mux.out1.bind(biggest);
}
