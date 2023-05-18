// Sleeping locks

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "../kernel/param.h"
#include "../kernel/memlayout.h"
#include "../kernel/spinlock.h"
#include "../kernel/proc.h"
#include "sleeplock.h"

void
initsleeplock(struct sleeplock *lk, char *name)
{
  initlock(&lk->lk, "sleep lock"); //need to implement?
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
}

void
acquiresleep(struct sleeplock *lk)
{
  acquire(&lk->lk); //need to implement?
  while (lk->locked) {
    sleep(lk, &lk->lk); //need to implement?
  }
  lk->locked = 1;
  lk->pid = myproc()->pid; //should we just pass in the pid?
  release(&lk->lk);
}

void
releasesleep(struct sleeplock *lk)
{
  acquire(&lk->lk); //need to implement?
  lk->locked = 0;
  lk->pid = 0;
  wakeup(lk); //need to implement?
  release(&lk->lk); //need to implement?
}

int
holdingsleep(struct sleeplock *lk)
{
  int r;
  
  acquire(&lk->lk); //need to implement?
  r = lk->locked && (lk->pid == myproc()->pid); //should we just pass in the pid?
  release(&lk->lk); //need to implement?
  return r;
}



