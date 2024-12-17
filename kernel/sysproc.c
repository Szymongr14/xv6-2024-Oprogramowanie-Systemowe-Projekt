#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
uint64
sys_ps(void)
{
    struct proc *p;
    for(p = proc; p < &proc[NPROC]; p++) {
        if(p->state != UNUSED) {
            printf("PID: %d, State: %d, Name: %s \n", p->pid, p->state, p->name);
        }
    }
    return 0;

}

int
sys_is_alive(void)
{
  int pid;
  argint(0, &pid);
  if (pid < 0)
    return -1;
  return is_alive(pid);
}

uint64
sys_setfgpid(void)
{
  int pid;
  argint(0, &pid);
  fg_pid = pid;  // Update the global foreground process ID
  return 0;      // Return success
}

uint64
sys_waitpid(void) {
  int pid;
  uint64 status;

  argint(0, &pid);
  argaddr(1, &status);

  return waitpid(pid, (int *)status);
}