#include "rel.h"
#include "relu.h"
#include <stdio.h>

#define MOV(dst,imm) \
  __WGI16__(word,OP_MOV,dst,0,imm); \
  buf[pc++] = word

#define EXIT __WGI16__(word,OP_EXIT,0,0,0); buf[pc++] = word

#define ADD(dst,src,opt) __WGI12__(word,OP_ADD,dst,src,opt,0); buf[pc++] = word
#define SUB(dst,src,opt) __WGI12__(word,OP_SUB,dst,src,opt,0); buf[pc++] = word

#define JEQ(dst,src,addr) __WGI16__(word,OP_JEQ,dst,src,addr); buf[pc++] = word
#define JNE(dst,src,addr) __WGI16__(word,OP_JNE,dst,src,addr); buf[pc++] = word

int main() {

  word_t buf[32] = {0};
  int pc = 0;
  int word = 0;

  MOV(0,10);
  MOV(1,100);
  ADD(3,1,0);
  MOV(2,24);
  SUB(0,3,2);
  JNE(3,0,0);
  EXIT;

  relu_dasm(buf);
  int r = rel_main(buf);

  printf("output: %d\n",r);
}
