#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Sets the ticket amount to the specified value
int sys_settickets(void) {
	#ifdef STRIDE
	int tickets_val;

	// Error condition
	if(argint(0, &tickets_val) == -1) {
		return -1;
	}

	// Error condition
	if(tickets_val < 1) {
		return settickets(8);
	}
	else if(tickets_val > (1<<5)) {
		return settickets(32);
	}
	return settickets(tickets_val);
	#else
	return 0;
	#endif
}

// Placeholder for getpinfo
int sys_getpinfo(void) {
	struct pstat* my_stats;
	if(argptr(0, (void*)&my_stats, sizeof(struct pstat*)) == -1) {
		return -1;
	}
	return getpinfo(my_stats);
}
