#ifndef REL_UTILS
#define REL_UTILS

#include "rel.h"
#include <stdio.h>

#define DASM_NEXT_PATTERN \
  word = *(pcode++); \
  pc = (int)(pcode - point); \
  goto *dp[READ_OPCODE(word)]

int relu_dasm(word_t* pcode);

#endif
