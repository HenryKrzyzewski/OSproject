struct spinlock {
  uint locked;       

  // struct cpu *cpu; ?   
};

struct sleeplock {
  int locked;       
  struct spinlock lk; 
  
  int tid;           
};

void initsleeplock(struct sleeplock* lk);

void acquiresleep(struct sleeplock *lk, int id);

void releasesleep(struct sleeplock *lk);

int holdingsleep(struct sleeplock *lk, int id);