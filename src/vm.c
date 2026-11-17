#include "vm.h"
#include <stdio.h>

int rel_main(word_t* restrict c) {
	int r[10] = {0};
	word_t word;
	int i;

	static const void* restrict table[] = {
		DEF_LABEL(MOV,op_mov),
		DEF_LABEL(ADD,op_add),
		DEF_LABEL(SUB,op_sub),
		DEF_LABEL(EXIT,op_exit)
	};

	word = *c;
	goto *table[READ_OPCODE];

	DEF_OPCODE(op_mov,
		r[READ_DSTR] = READ_IMM16
	)

	DEF_OPCODE(op_add,__MATH__(+));
	DEF_OPCODE(op_sub,__MATH__(-));

op_exit:
	return r[0];
}
