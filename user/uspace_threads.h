// 
// Header File for userspace threads implementation
//

typedef uint64 greg_t;

typedef struct gregset
   {
     greg_t gregs[14];
   } mcontext_t;

typedef struct {
	void* uc_stack;
    void* original;
	mcontext_t uc_mcontext;
	int id;
	void* fn_ptr;
  int state;
}ucontext_t;
 
void swapcontext(ucontext_t* oldThread, ucontext_t* newThread);
void makecontext(ucontext_t* thread, void* func , void* argv1 = 0, void* argv2 = 0, void* argv3 = 0, 
    void* argv4 = 0, void* argv5 = 0, void* argv6 = 0, void* argv7 = 0, void* argv8 = 0
);


