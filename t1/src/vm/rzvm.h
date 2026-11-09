#ifndef RAZOR_VM
#define RAZOR_VM

/* Bytecode Layout
 * - Litte Endian
 * - 1 word = 4 byte
 * 
 * Layout :
 * [ 8 bit opcode ] [ 4 bit r[dst] ] [ 4 bit r[src] ] [ 16 bit imm ]
 *
 */

#define GET_OPCODE ( w & 0xFF )
#define GET_RDST ( w >> 8 ) & 0xF
#define GET_RSRC ( w >> 12 ) & 0xF
#define GET_IMM ( w >> 16 ) & 0xFFFF

#define NEXT \
		++c; \
		goto *table[GET_OPCODE]

#define DEF_LABEL(name_op,label) [name_op] = &&label,
#define DEF_OPCODE(name,handler) name: { handler; NEXT; }
#define __MATH__(operator) r[GET_RDST] operator##= r[GET_RSRC]

enum {
	OP_MOV = 0x00,
	OP_ADD = 0x01,
	OP_SUB = 0x02,
	OP_EXIT = 0x03
};

typedef unsigned int word;
typedef unsigned char byte;

void zexec(word* restrict c);

#endif
