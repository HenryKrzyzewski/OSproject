/*
 * Userspace Threads
 *
 *
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "uspace_threads.h"

//Pass in old and new contexts
extern void swap(greg_t*, greg_t*);

void makecontext(ucontext_t* thread, void* func, void* argv1 = 0, void* argv2, void* argv3,void* argv4, void* argv5, void* argv6, void* argv7, void* argv8
){
    thread->uc_mcontext.gregs[2] = (uint64) argv1 | 0;
    thread->uc_mcontext.gregs[3] = (uint64) argv2 | 0;
    thread->uc_mcontext.gregs[4] = (uint64) argv3 | 0;
    thread->uc_mcontext.gregs[5] = (uint64) argv4 | 0;
    thread->uc_mcontext.gregs[6] = (uint64) argv5 | 0;
    thread->uc_mcontext.gregs[7] = (uint64) argv6 | 0;
    thread->uc_mcontext.gregs[8] = (uint64) argv7 | 0;
    thread->uc_mcontext.gregs[9] = (uint64) argv8 | 0;
    
    //set fn_ptr to func
    thread->uc_mcontext.gregs[0] = (unsigned long int) &func;
    thread->uc_mcontext.gregs[1] = (unsigned long int) thread->uc_stack;
    thread->fn_ptr = func;
}

void swapcontext(ucontext_t* oldThread, ucontext_t* newThread) {
    swap(oldThread->uc_mcontext.gregs, newThread->uc_mcontext.gregs);
}
