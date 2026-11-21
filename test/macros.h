#ifndef MACROS_H
#define MACROS_H

#include "../src/rel.h"
#include "../src/reldk.h"

#define SETUP(size) \
  main() { \
    word_t word; \
    word_t pcode[size] = {0}; \
    int pc = 0;

#define UPDATE \
    pcode[pc++] = word

#define MOV(dst,imm) \
    __WGI16__(word,OP_MOV,dst,0,imm); \
    UPDATE

#define ADD(dst,src,opt) \
    __WGI12__(word,OP_ADD,dst,src,opt,0); \
    UPDATE

#define SUB(dst,src,opt) \
    __WGI12__(word,OP_SUB,dst,src,opt,0); \
    UPDATE

#define JNE(dst,src,imm) \
    __WGI16__(word,OP_JNE,dst,src,imm); \
    UPDATE

#define JEQ(dst,src,imm) \
    __WGI16__(word,OP_JEQ,dst,src,imm); \
    UPDATE

#define EXIT() \
    __WGI16__(word,OP_EXIT,0,0,0); \
    UPDATE

#endif
