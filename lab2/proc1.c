#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {


	set_prior(1);

	        printf(1, "\n THIS pid: %d start with prio 1\n", getpid());

	int i, k;
	for(i = 0; i < 43000; i++) {
		asm("nop");
		for(k = 0; k < 43000; k++) {
			asm("nop");
		}
	}
	



	
	exit();
}
