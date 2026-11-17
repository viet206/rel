#include "relu.h"

#define NEXT_PATTERN \
  word = *(pcode++); \
  op = READ_OPCODE(word); \
  pattern = type_pattern[op]; \
  goto *dp[pattern]

#define REG_RANGE(reg) \
  ( ! ( reg >= 0 && reg <= 7 ) )

int relu_dasm(word_t* pcode) {

  const int type_pattern[] = {
    [OP_MOV] = RI_PATTERN,
    [OP_ADD] = RR_PATTERN,
    [OP_SUB] = RR_PATTERN,
    [OP_EXIT] = EXIT_PATTERN
  };

	const char* const op_name[] = {
		[OP_MOV] = "mov",
		[OP_ADD] = "add",
		[OP_SUB] = "sub",
		[OP_EXIT] = "exit"
	};

	const char* const reg_name[] = {
		[0] = "r0",
		[1] = "r1",
		[2] = "r2",
		[3] = "r3",
		[4] = "r4",
		[5] = "r5",
		[6] = "r6",
		[7] = "r7"
	};

  const void* const dp[] = {
    [RI_PATTERN] = &&ri,
    [RR_PATTERN] = &&rr,
    [FULL_PATTERN] = &&full,
    [EXIT_PATTERN] = &&exit
  };

  int word , op , imm , dst , pattern , src = 0;

  NEXT_PATTERN;

ri:

  imm = READ_IMM16(word);
  dst = READ_DSTR(word);

  if (REG_RANGE(dst)) {
    printf("register: r%d not valid\n",dst);
    goto exit;
  }

  printf("%s %s , %d\n",
    op_name[op],
    reg_name[dst],
    imm
  );

  NEXT_PATTERN;

rr:

  dst = READ_DSTR(word);
  src = READ_SRCR(word);

  if ((REG_RANGE(dst)) || (REG_RANGE(src))) {
    printf("Dump RR_PATTERN\n");
    printf("dst : r%d\n",dst);
    printf("src : r%d\n",src);
    goto exit;
  }

  printf("%s %s , %s\n",
    op_name[op],
    reg_name[dst],
    reg_name[src]
  );

  NEXT_PATTERN;

full:

  dst = READ_DSTR(word);
  src = READ_SRCR(word);
  imm = READ_IMM16(word);

  if ((REG_RANGE(dst)) || (REG_RANGE(src))) {
    printf("Dump FULL_PATTERN\n");
    printf("dst: r%d\n",dst);
    printf("src: r%d\n",src);
    goto exit;
  }

  printf("%s %s , %s , %d\n",
    op_name[op],
    reg_name[dst],
    reg_name[src],
    imm
  );

  NEXT_PATTERN;

exit:

  return 0;
}
