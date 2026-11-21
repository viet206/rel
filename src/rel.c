#include "rel.h"
#include <stdio.h>

int rel_main(word_t* restrict c) {
	int r[10] = {0};
	word_t word;
  cell_t __local_stack__[1024] = {0};

  ptr_t stack;
  stack.c = __local_stack__;

	static const void* const table[] = {
		DEF_LABEL(OP_MOV,mov),
		DEF_LABEL(OP_ADD,add),
		DEF_LABEL(OP_SUB,sub),
		DEF_LABEL(OP_EXIT,exit),
    DEF_LABEL(OP_JEQ,jeq),
    DEF_LABEL(OP_JNE,jne),
    DEF_LABEL(OP_JLT,jlt),
    DEF_LABEL(OP_JGT,jgt),
    DEF_LABEL(OP_CALL,call),
    DEF_LABEL(OP_RET,ret),
    DEF_LABEL(OP_LBU,lbu),
    DEF_LABEL(OP_SBU,sbu)
	};

	word = *c;
	goto *table[READ_OPCODE(word)];

	DEF_OPCODE(mov,
		r[READ_DST_REG(word)] = READ_IMM16(word)
	)

  DEF_OPCODE(call,
    (void)0
  )

  DEF_OPCODE(ret,
    (void)0
  )

  DEF_OPCODE(lbu,
    (void)0
  )

  DEF_OPCODE(sbu,
    (void)0
  )

	DEF_OPCODE(add,__MATH__(+));
	DEF_OPCODE(sub,__MATH__(-));
  DEF_OPCODE(mul,__MATH__(*));
  DEF_OPCODE(div,__MATH__(/));
  DEF_OPCODE(mod,__MATH__(%));
  DEF_OPCODE(jeq,__JUMP__(==));
  DEF_OPCODE(jne,__JUMP__(!=));
  DEF_OPCODE(jlt,__JUMP__(<));
  DEF_OPCODE(jgt,__JUMP__(>));

handler_exit:
	return r[0];
}
