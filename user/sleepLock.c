// Sleeping locks


#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "../kernel/param.h"
#include "../kernel/memlayout.h"
#include "../kernel/spinlock.h"
#include "../kernel/proc.h"
#include "sleeplock.h"
#include "ucontext.h"

void
initsleeplock(struct sleeplock *lk)
{
  initlock(&lk->lk, "sleep lock"); 
  lk->locked = 0;
  lk->pid = 0;
}

void
acquiresleep(struct sleeplock *lk, ucontext_t* thread)
{
  acquire(&lk->lk); 
  while (lk->locked) {
    sleep(lk, &lk->lk); 
  }
  lk->locked = 1;
  lk->pid =thread->id; 
  release(&lk->lk);
}

void
releasesleep(struct sleeplock *lk)
{
  acquire(&lk->lk);
  lk->locked = 0;
  lk->pid = 0;
  wakeup(lk); 
  release(&lk->lk); 
}

int
holdingsleep(struct sleeplock *lk, , ucontext_t* thread)
{
  int r;
  
  acquire(&lk->lk); 
  r = lk->locked && (lk->pid == thread->id`); 
  release(&lk->lk); 
  return r;
}



