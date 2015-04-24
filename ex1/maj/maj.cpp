#include "maj.h"

void Maj::action()
{
  f = (a && b) || (!a && b && c) || (a && !b && c);
}
