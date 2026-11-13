#ifndef RAW_EXECUTION_LAYER_H
#define RAW_EXECUTION_LAYER_H

#define __VERSION "0.1-preview"

#define ENABLE_DEBUG 0

/* Define Rel Tracer */
#if ENABLE_DEBUG == 1

#include <stdio.h>
#include <stdlib.h>

#define REL_DUMP_ONLY \
	printf("pc: %d\n",(int)(c - &c[0])); \
	printf("op: %02x\n",GET_OPCODE); \
	printf("dst: %02x\n",GET_DR); \
	printf("src: %02x\n",GET_SR); \
	printf("imm: %d\n",GET_IMM); \
	++c; \
	goto *table[GET_OPCODE]

#define REL_DUMP_BOOT \
	printf("opcode: %02x",GET_OPCODE); \
	goto op_exit

#else

#define REL_DUMP_ONLY (void)0
#define REL_DUMP_BOOT (void)0

#endif

/* Define Main Logic VM */

// [ imm ] [ sr ] [ dr ] [ opcode ]
#define GET_OPCODE word & 0xFF
#define GET_DR ( word >> 8 ) & 0xF
#define GET_SR ( word >> 12 ) & 0xF
#define GET_IMM ( word >> 16 ) & 0xFFFF

// Define Alias Register
#define SR r[GET_SR]
#define DR r[GET_DR]

// Define Next Handler
#define NEXT \
	word = *(++c); \
	goto *table[GET_OPCODE]

#define DEF_LABEL(name,op) \
	[name] = &&op

#define DEF_OPCODE(name,handler) \
	name: { \
		REL_DUMP_ONLY; \
		handler; \
		NEXT; \
	}

#define __MATH__(operator) \
	DR operator##= SR

#define __JMP__(op) \
	if ( DR op SR ) { \
		pc += GET_IMM; \
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
