#ifndef RAW_EXECUTION_LAYER_H
#define RAW_EXECUTION_LAYER_H

#define REL_TRACE 0

/* Define Rel Tracer */
#if REL_TRACE == 1

#include <stdio.h>
#include <stdlib.h>

#define REL_TRACE_BEFORE \
	printf("pc: %d\n",(int)(c - &c[0])); \
	printf("word: %08x\n",*c);

#define REL_TRACE_AFTER (void)0

#else

#define REL_TRACE_BEFORE (void)0
#define REL_TRACE_AFTER (void)0

#endif

/* Define Main Logic VM */

#define GET_OPCODE word & 0xFF

// SR = Source Register
#define GET_SR ( word >> 8 ) & 0xF

// DR = Source Register
#define GET_DR ( word >> 12 ) & 0xF

#define GET_IMM16 ( word >> 16 ) & 0xFFFF
#define GET_IMM20 ( word >> 12 ) & 0xFFFFF

// Define Alias Register
#define SR r[GET_SR]
#define DR r[GET_DR]

// Define Next Handler
#define NEXT \
	word = *(++c); \
	goto *table[GET_OPCODE]

#define DEF_LABEL(name,op) \
	[name] = &&op,

#define DEF_OPCODE(name,handler) \
	name: { REL_TRACE_BEFORE; \
		handler; \
		REL_TRACE_AFTER; \
		NEXT; \
	}

#define __MATH__(operator) \
	DR operator##= SR

#define __NATIVE_JMP__(op) \
	if ( DR op SR ) { \
		pc += GET_IMM16; \
	} \
	NEXT

enum {
	MOV = 0x00,
	ADD = 0x01,
	SUB = 0x02,
	EXIT = 0x03
};

typedef unsigned int word_t;
typedef unsigned char cell_t;

int rel_main(word_t* restrict c);

#endif
