/*
 * Userspace Threads
 *
 *
 */
#include "ucontext.h"

//Pass in old and new contexts
extern void swap(greg_t*, greg_t*);

void getcontext(ucontext_t * thread) {
    
    mcontext_t mcontext = {};
    thread->uc_mcontext = mcontext;
}

void makecontext(ucontext_t* thread, void* func
//, void* argv1 = 0, void* argv2 = 0, void* argv3 = 0, void* argv4 = 0, void* argv5 = 0, void* argv6 = 0, void* argv7 = 0, void* argv8 = 0
){
    // for(int i = 0; i < argc; i++) {
    //     //iterate over arguments and store them on the stack
    //     thread.stack_t.ss_sp + (4 * i) = argv[i];
    // }
    //worry about args later (different argument types)

    //set fn_ptr to fun
    thread->uc_mcontext.gregs[0] = (unsigned long int) &func;
    thread->uc_mcontext.gregs[1] = (unsigned long int) thread->uc_stack;
    thread->fn_ptr = func;
}

void swapcontext(ucontext_t* oldThread, ucontext_t* newThread) {
    //load registers from stack into a buffer
    //store registers from old context onto 
    swap(oldThread->uc_mcontext.gregs, newThread->uc_mcontext.gregs);
}