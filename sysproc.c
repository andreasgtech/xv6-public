#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

//#include <stdio.h>

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

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int sys_printRunningProc(void)
{
  struct proc * p;
  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
  {
    if(p->state != UNUSED)
    {
      cprintf("PID: %d, ", p->pid);
      cprintf("Name: %s, ", p->name);
      cprintf("PPID: %d, ", p->parent->pid);
      switch(p->state)
      {
        case UNUSED : cprintf("State: %s, ", "UNUSED"); break;
        case EMBRYO : cprintf("State: %s, ", "EMBRYO"); break;
        case SLEEPING : cprintf("State: %s, ", "SLEEPING"); break;
        case RUNNABLE : cprintf("State: %s, ", "RUNNABLE"); break;
        case RUNNING : cprintf("State: %s, ", "RUNNING"); break;
        case ZOMBIE : cprintf("State: %s, ", "ZOMBIE"); break;
      }
      cprintf("Runnnig time: %d, ", p->runningTime);
      cprintf("Creation time: %d, ", p->birthTime);
      cprintf("Priority: %d, ", p->priority);     
      cprintf("Times scheduled: %d\n", p->times_sched);
    }
  }
  release(&ptable.lock);
  return 0;
}
