#include "rel_vm.h"

void rel_main(word* restrict c) {
		int r[10] = {0};
		word w;

		static const void* restrict table[] = {
				DEF_LABEL(OP_MOV,op_mov)
				DEF_LABEL(OP_ADD,op_add)
				DEF_LABEL(OP_SUB,op_sub)
				
				[OP_EXIT] = &&op_exit
		};

		w = *c;
		goto *table[GET_OPCODE];

		DEF_OPCODE(op_mov,
				r[GET_RDST] = GET_IMM;
		)

		DEF_OPCODE(op_add,__MATH__(+));
		DEF_OPCODE(op_sub,__MATH__(-));

		op_exit:
}
