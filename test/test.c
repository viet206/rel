#include "vm.h"
#include "relu.h"
#include <stdio.h>

#define MOV(dst,imm) \
  __WGI__(word,OP_MOV,dst,0,imm); \
  buf[pc++] = word

#define EXIT __WGI__(word,OP_EXIT,0,0,0); buf[pc++] = word

int main() {

  word_t buf[32] = {0};
  int pc = 0;
  int word = 0;

  MOV(0,10);
  MOV(1,100);
  EXIT;

  relu_dasm(buf);
}
