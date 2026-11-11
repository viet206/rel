#ifndef REL
#define REL

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

int rel_main(word* restrict c);

#endif
