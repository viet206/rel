#ifndef REL_UTILS
#define REL_UTILS

#include "vm.h"
#include <stdio.h>

#define FULL_PATTERN 0x67
// [ op ] [ dst ] [ src ] [ imm ]
#define RI_PATTERN 0x66
// op dst imm
#define RR_PATTERN 0x36
// op dst src
#define EXIT_PATTERN 0x99

int relu_dasm(word_t* pcode);

#endif
