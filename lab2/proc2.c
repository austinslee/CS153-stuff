#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {

        printf(1, "\n THIS pid: %d start with prio 50\n", getpid());

	set_prior(50);

        int i, k;
        for(i = 0; i < 43000; i++) {
                asm("nop");
                for(k = 0; k < 43000; k++) {
                        asm("nop");
                }
        }
		
	
	
	exit();
}

