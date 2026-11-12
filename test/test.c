#include "cgen.h"
#include "vm.h"
#include <stdio.h>

#define DEBUG 1

int main() {
	gen_init(256);

	MOV(0,123);
	MOV(1,256);
	ADD(0,1);
	EXIT;


#if DEBUG == 1

	cell_t* a = (cell_t*) arr;

	for ( int i = 0 ; i < 32 ; i++ ) {
		if ( ( i % 8 ) == 0 ) {
			puts("");
		}

		if ( ( i % 4 ) == 0 ) printf(" ");

		printf("%02x",a[i]);
	}
	puts("");

#else

	gen_exec(r);
	printf("result: %d\n",r);
	
#endif
}
