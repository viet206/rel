#include "relu.h"

int relu_dasm(word_t* pcode) {
	const int pattern[] = {
		[OP_MOV] = RI_PATTERN,
		[OP_ADD] = RR_PATTERN,
		[OP_EXIT] = SINGLE_PATTERN
	};

	const char* const op_name[] = {
		[OP_MOV] = "mov",
		[OP_ADD] = "add",
		[OP_SUB] = "sub",
		[OP_EXIT] = "exit"
	};

	const char* const reg_name[] = {
		"r0",
		"r1",
		"r2",
		"r3",
		"r4",
		"r5",
		"r6",
		"r7"
	};

	int word = *pcode++;
	int dst , src , imm = 0;
	int op = READ_OPCODE;

	while ( op != OP_EXIT ) {		
		switch (pattern[op]) {
			case RR_PATTERN:
				dst = READ_DSTR;
				src = READ_SRCR;

				printf("%s %s %s\n",
					op_name[op],
					reg_name[dst],
					reg_name[src]
				);

				word = *pcode++;
				op = READ_OPCODE;
				
				break;
			case RI_PATTERN:
				dst = READ_DSTR;
                imm = READ_IMM16;

                printf("%s %s %d\n",
					op_name[op],
					reg_name[dst],
					imm
                );

                word = *pcode++;
                op = READ_OPCODE;

                break;

			case FULL_PATTERN:
				dst = READ_DSTR;
                src = READ_SRCR;
				imm = READ_IMM16;

                printf("%s %s %s %d\n",
                    op_name[op],
                    reg_name[dst],
                    reg_name[src],
					imm
				);

                 word = *pcode++;
                 op = READ_OPCODE;

                 break;

			case SINGLE_PATTERN:
				goto exit_point;
		}
	}
	
exit_point:
	return 0;
}
