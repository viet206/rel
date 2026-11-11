#include "vm.h"

int rel_main(word_t* restrict c) {
	int r[10] = {0};
	word_t word;

	static const void* restrict table[] = {
		DEF_LABEL(MOV,op_mov)
		DEF_LABEL(ADD,op_add)
		DEF_LABEL(SUB,op_sub)
		
		[EXIT] = &&op_exit
	};

	word = *c;
	goto *table[GET_OPCODE];

	DEF_OPCODE(op_mov,
		r[GET_DR] = GET_IMM
	)

	DEF_OPCODE(op_add,__MATH__(+));
	DEF_OPCODE(op_sub,__MATH__(-));

op_exit:
	return r[0];
}
