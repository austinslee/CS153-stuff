#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {
	acquire(&(shm_table.lock));
	int i;
	uint pa;
	uint va = PGROUNDUP(myproc()->sz);
	//Case 1
	for (i = 0; i< 64; i++) {
		if(shm_table.shm_pages[i].id == id) {
			pa = V2P(shm_table.shm_pages[i].frame);
			mappages(myproc()->pgdir, (void*) va, PGSIZE, pa, PTE_W|PTE_U);
			shm_table.shm_pages[i].refcnt++;
			*pointer = (char *)va;
			myproc()->sz += PGSIZE;
			release(&(shm_table.lock));
			return 0;
		}
	}

	for (i = 0; i < 64; i++) {
		//Case 2
		if(shm_table.shm_pages[i].id == 0) {
			shm_table.shm_pages[i].id = id;
			shm_table.shm_pages[i].refcnt = 1;
			shm_table.shm_pages[i].frame = kalloc();
			memset(shm_table.shm_pages[i].frame, 0, PGSIZE);
			pa = V2P(shm_table.shm_pages[i].frame);
			mappages(myproc()->pgdir, (void*) va, PGSIZE, pa, PTE_W|PTE_U);
			*pointer=(char *) va;
			myproc()->sz += PGSIZE;
			release(&(shm_table.lock));
			return 0;
		}
	}
	

	release(&(shm_table.lock));
	return 0;
}


int shm_close(int id) {
	acquire(&(shm_table.lock));
	int i;
	for (i = 0; i< 64; i++) {
		if(shm_table.shm_pages[i].id == id) {
			if(shm_table.shm_pages[i].refcnt >= 1) {
				shm_table.shm_pages[i].refcnt--;
			}
			if(shm_table.shm_pages[i].refcnt <= 0) {	 
				shm_table.shm_pages[i].id = 0;
				shm_table.shm_pages[i].frame = 0;
				shm_table.shm_pages[i].refcnt = 0;
				release(&(shm_table.lock));
				return 0;
			}
		}
	}
	release(&(shm_table.lock));
	return 0;
}
