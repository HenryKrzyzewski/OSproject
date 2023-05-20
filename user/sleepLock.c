// Sleeping locks

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "sleepLock.h"

// Add functions as system calls

void initsleeplock(struct sleeplock *lk)
{
  lk->lk.locked = 0;
  lk->locked = 0;
  lk->tid = 0;
}

void acquiresleep(struct sleeplock *lk, int id)
{
  // acquire(&lk->lk);
  while (lk->locked)
  {
    // sleep(lk, &lk->lk);
  }
  lk->locked = 1;
  lk->tid = id;
  // release(&lk->lk);
}

void releasesleep(struct sleeplock *lk)
{
  // acquire(&lk->lk);
  lk->locked = 0;
  lk->tid = 0;
  // wakeup(lk);
  // release(&lk->lk);
}

int holdingsleep(struct sleeplock *lk, int id)
{
  int r;

  // acquire(&lk->lk);
  r = lk->locked && (lk->tid == id);
  // release(&lk->lk);
  return r;
}
