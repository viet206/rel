#ifndef RAW_EXECUTION_LAYER_H
#define RAW_EXECUTION_LAYER_H

#define __VERSION "0.1-preview"

#define ENABLE_DEBUG 0

/* Define Main Logic VM */

// [ imm ] [ sr ] [ dr ] [ opcode ]
#define READ_OPCODE(word) word & 0xFF
#define READ_DSTR(word) ( word >> 8 ) & 0xF
#define READ_SRCR(word) ( word >> 12 ) & 0xF
#define READ_IMM16(word) ( word >> 16 ) & 0xFFFF

// Write General Instruction
#define __WGI__(word,op,dst,src,imm16) \
  word |= op; \
  word |= ( dst << 8 ); \
  word |= ( src << 12 ); \
  word |= ( imm16 << 16 )

// Define Alias Register
#define SR r[READ_SRCR(word)]
#define DR r[READ_DSTR(word)]

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
	DR operator##= SR

#define __JMP__(op) \
	if ( DR op SR ) { \
		pc += GET_IMM16(word); \
	} \
	NEXT

enum {
	OP_MOV = 0x00,
	OP_ADD = 0x01,
	OP_SUB = 0x02,
	OP_EXIT = 0x03
};

typedef unsigned int word_t;
typedef unsigned char cell_t;

int rel_main(word_t* restrict c);

#endif
