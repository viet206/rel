#include "macros.h"
#include <stdio.h>

int SETUP(256)

  MOV(0,10);
  MOV(1,100);
  ADD(3,1,0);
  MOV(2,24);
  SUB(0,3,2);
  JNE(3,0,0);
  EXIT();

  relu_dasm(pcode);
  int r = rel_main(pcode);

  printf("output: %d\n",r);
}
