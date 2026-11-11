#ifndef MACRO_CODE_GENERATOR
#define MACRO_CODE_GENERATOR

#include "vm/vm.h"

#define cg_init(size) \
	word_t arr[size] = {0}; \
	int bytectr = -1

#define mov(reg_dst,imm) \
    (arr[++bytectr] = (MOV << 24) | \
                      ((reg_dst & 0xF) << 20) | \
                      (imm & 0xFFFF))

#define __CG_MATH__(op,rdst, rsrc) \
    (arr[++bytectr] = (op << 24) | \
                      ((rdst & 0xF) << 20) | \
                      ((rsrc & 0xF) << 16))

#define add(rdst,rsrc) __CG_MATH__(ADD,rdst,rsrc)
#define sub(rdst,rsrc) __CG_MATH__(SUB,rdst,rsrc)

#define exit arr[++bytectr] = EXIT

#endif
