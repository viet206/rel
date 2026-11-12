#ifndef MACRO_CODE_GENERATOR
#define MACRO_CODE_GENERATOR

#include "vm.h"

/* Instruction encoding */
#define WRITE_OP(op)   ((word_t)(op))
#define WRITE_DR(reg)  ((word_t)(reg) << 8)
#define WRITE_SR(reg)  ((word_t)(reg) << 12)
#define WRITE_IMM(imm) ((word_t)(imm) << 16)

/* Initialize code buffer */
#define gen_init(size) \
    word_t arr[size] = {0}; \
    int i = -1

/* Execute generated code */
#define gen_exec(rtcode) \
    int rtcode = rel_main(arr)

/* Generate math instruction */
#define __WRITE_MATH__(op, rdst, rsrc) do { \
    arr[++i] = WRITE_OP(op)       | \
               WRITE_DR(rdst)     | \
               WRITE_SR(rsrc)     | \
               WRITE_IMM(0);      \
} while (0)

/* Move immediate value to register */
#define MOV(rdst, imm) do { \
    arr[++i] = WRITE_OP(MOV)   | \
               WRITE_DR(rdst)    | \
               WRITE_SR(0)       | \
               WRITE_IMM(imm);   \
} while (0)

/* Arithmetic instructions */
#define ADD(dst, src) __WRITE_MATH__(ADD, dst, src)
#define SUB(dst, src) __WRITE_MATH__(SUB, dst, src)

/* Exit instruction */
#define EXIT do { \
    arr[++i] = WRITE_OP(EXIT); \
} while (0)

#endif
