#ifndef RAW_EXECUTION_LAYER_H
#define RAW_EXECUTION_LAYER_H

#define __VERSION "0.1-preview"

#define READ_OPCODE(word) word & 0xFF
#define READ_DST_REG(word) ( word >> 8 ) & 0xF
#define READ_SRC_REG(word) ( word >> 12 ) & 0xF
#define READ_IMM16(word) ( word >> 16 ) & 0xFFFF
#define READ_OPT_REG(word) ( word >> 16 ) & 0xF
#define GET_IMM12(word) ( word >> 20 ) & 0xFFF

// Write General Instruction
#define __WGI16__(word,op,dst,src,imm16) \
  word = ( op & 0xFF ) | \
        ( dst << 8 ) | \
        ( src << 12 ) | \
        ( imm16 << 16 )

#define __WGI12__(word,op,dst,src,opt,imm12) \
  word = ( op & 0xFF ) | \
        ( dst << 8 ) | \
        ( src << 12 ) | \
        ( opt << 16 ) | \
        ( imm12 << 20 )

// Define Alias Register
#define SRC_REG r[READ_SRC_REG(word)]
#define DST_REG r[READ_DST_REG(word)]
#define OPT_REG r[READ_OPT_REG(word)]

// Define Next Handler
#define NEXT \
	word = *(++c); \
	goto *table[READ_OPCODE(word)]

#define DEF_LABEL(name,op) \
	[name] = &&op

#define DEF_OPCODE(name,handler) \
	name: { \
		handler; \
		NEXT; \
	}

#define __MATH__(operator) \
	DST_REG = SRC_REG operator OPT_REG

#define __JUMP__(op) \
	if ( DST_REG op SRC_REG ) { \
		c += READ_IMM16(word); \
	} \

enum {
	OP_MOV,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_JNE,
  OP_JEQ,
  OP_JLT,
  OP_JGT,
	OP_EXIT = 0xFF
};

typedef unsigned int word_t;
typedef unsigned char cell_t;

int rel_main(word_t* restrict c);

#endif
