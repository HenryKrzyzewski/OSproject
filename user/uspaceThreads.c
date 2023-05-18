/*
 * Userspace Threads
 *
 *
 */
#include "ucontext.h"

//Pass in old and new contexts
extern void swap(greg_t*, greg_t*);

void makecontext(ucontext_t* thread, void* func, int argc, void* argv){
    // for(int i = 0; i < argc; i++) {
    //     //iterate over arguments and store them on the stack
    //     thread.stack_t.ss_sp + (4 * i) = argv[i];
    // }
    //worry about args later (different argument types)

    //set fn_ptr to fun
    thread->uc_mcontext.gregs[0] = (unsigned long int) &func;
    thread->uc_mcontext.gregs[1] = (unsigned long int) thread->uc_stack;
    thread->fn_ptr = func;
    // *thread.uc_mcontext = ;
}

void swapcontext(ucontext_t* oldThread, ucontext_t* newThread) {
    //load registers from stack into a buffer
    //store registers from old context onto 
    swap(oldThread->uc_mcontext.gregs, newThread->uc_mcontext.gregs);
}
