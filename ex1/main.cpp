#include "top.h"

int sc_main(int argc, char *argv[])
{
  // Instantiate the top-level module
  Top top("top");

  sc_core::sc_start();

  return 0;
}
