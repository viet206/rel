#include "vm.h"
#include <stdio.h>

int rel_main(word_t* restrict c) {
	int r[10] = {0};
	word_t word;
	int i;

	static const void* const table[] = {
		DEF_LABEL(OP_MOV,handler_mov),
		DEF_LABEL(OP_ADD,handler_add),
		DEF_LABEL(OP_SUB,handler_sub),
		DEF_LABEL(OP_EXIT,handler_exit)
	};

	word = *c;
	goto *table[READ_OPCODE(word)];

	DEF_OPCODE(handler_mov,
		r[READ_DSTR(word)] = READ_IMM16(word)
	)

	DEF_OPCODE(handler_add,__MATH__(+));
	DEF_OPCODE(handler_sub,__MATH__(-));

handler_exit:
	return r[0];
}
