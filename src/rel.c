#include "rel.h"
#include <stdio.h>

int rel_main(word_t* restrict c) {
	int r[10] = {0};
	word_t word;
	int i;

	static const void* const table[] = {
		DEF_LABEL(OP_MOV,handler_mov),
		DEF_LABEL(OP_ADD,handler_add),
		DEF_LABEL(OP_SUB,handler_sub),
		DEF_LABEL(OP_EXIT,handler_exit),
    DEF_LABEL(OP_JEQ,handler_jeq),
    DEF_LABEL(OP_JNE,handler_jne),
    DEF_LABEL(OP_JLT,handler_jlt),
    DEF_LABEL(OP_JGT,handler_jgt)
	};

	word = *c;
	goto *table[READ_OPCODE(word)];

	DEF_OPCODE(handler_mov,
		r[READ_DST_REG(word)] = READ_IMM16(word)
	)

	DEF_OPCODE(handler_add,__MATH__(+));
	DEF_OPCODE(handler_sub,__MATH__(-));
  DEF_OPCODE(handler_mul,__MATH__(*));
  DEF_OPCODE(handler_div,__MATH__(/));
  DEF_OPCODE(handler_mod,__MATH__(%));
  DEF_OPCODE(handler_jeq,__JUMP__(==));
  DEF_OPCODE(handler_jne,__JUMP__(!=));
  DEF_OPCODE(handler_jlt,__JUMP__(<));
  DEF_OPCODE(handler_jgt,__JUMP__(>));

handler_exit:
	return r[0];
}
