#include "relu.h"

int relu_dasm(word_t* pcode) {

	const char* const op_name[] = {
		[OP_MOV] = "mov",
		[OP_ADD] = "add",
		[OP_SUB] = "sub",
    [OP_MUL] = "mul",
    [OP_DIV] = "div",
    [OP_JNE] = "jne",
    [OP_JEQ] = "jeq",
    [OP_JLT] = "jlt",
    [OP_JGT] = "jgt",
		[OP_EXIT] = "exit"
	};

  const void* const dp[] = {
    [OP_MOV] = &&RI_PATTERN,
    [OP_ADD] = &&MATH_PATTERN,
    [OP_SUB] = &&MATH_PATTERN,
    [OP_MUL] = &&MATH_PATTERN,
    [OP_DIV] = &&MATH_PATTERN,
    [OP_JNE] = &&JUMP_PATTERN,
    [OP_JEQ] = &&JUMP_PATTERN,
    [OP_JGT] = &&JUMP_PATTERN,
    [OP_JLT] = &&JUMP_PATTERN,
    [OP_EXIT] = &&EXIT_POINT
  };

  int word;
  int pattern;
  int pc = 0;

  word_t* point = pcode;

  puts("Bytecode reverse translation");
  puts("Little-Endian 32 bit\n");
  puts ("address  |  word  |  asm");

  DASM_NEXT_PATTERN;

RI_PATTERN:

  printf("%08x: %08x  %s r%d , %d\n",
    pc,
    word,
    op_name[READ_OPCODE(word)],
    READ_DST_REG(word),
    READ_IMM16(word)
  );

  DASM_NEXT_PATTERN;

MATH_PATTERN:

  printf("%08x: %08x  %s r%d , r%d , r%d\n",
    pc,
    word,
    op_name[READ_OPCODE(word)],
    READ_DST_REG(word),
    READ_SRC_REG(word),
    READ_OPT_REG(word)
  );

  DASM_NEXT_PATTERN;

BASE_PATTERN:

  printf("%s r%d , r%d , %d\n",
    op_name[READ_OPCODE(word)],
    READ_DST_REG(word),
    READ_SRC_REG(word),
    READ_IMM16(word)
  );

  DASM_NEXT_PATTERN;

JUMP_PATTERN:

  printf("%08x: %08x  %s r%d , r%d , ",
      pc,
      word,
      op_name[READ_OPCODE(word)],
      READ_DST_REG(word),
      READ_SRC_REG(word)
  );

  if ( READ_IMM16(word) > 0 ) {
    printf("+%d\n",READ_IMM16(word));
  }else{
    printf("%d\n",READ_IMM16(word));
  }

  DASM_NEXT_PATTERN;

EXIT_POINT:

  printf("%08x: %08x  %s\n",
      pc,
      word,
      op_name[READ_OPCODE(word)]
  );

  return 0;
}
