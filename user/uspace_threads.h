//
// Header File for userspace threads implementation
//

typedef struct
{
  uint64 ra;
  uint64 sp;
  uint64 a0;
  uint64 a1;
  uint64 a2;
  uint64 s0;
  uint64 s1;
  uint64 s2;
  uint64 s3;
  uint64 s4;
  uint64 s5;
  uint64 s6;
  uint64 s7;
  uint64 s8;
  uint64 s9;
  uint64 s10;
  uint64 s11;
} mcontext_t;

typedef struct
{
  void *uc_stack;
  void *original;
  mcontext_t uc_mcontext;
  int id;
  void *fn_ptr;
  int state;
} ucontext_t;

void swapcontext(ucontext_t *oldThread, ucontext_t *newThread);
void makecontext(ucontext_t *thread, void *func, void *argv1, void *argv2, void *argv3);