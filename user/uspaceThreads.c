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

void makecontext(ucontext_t* thread, void* func, void* argv1 = 0, void* argv2 = 0, void* argv3 = 0, 
                void* argv4 = 0, void* argv5 = 0, void* argv6 = 0, void* argv7 = 0, void* argv8 = 0
){
    thread->uc_mcontext.gregs[2] = argv1;
    thread->uc_mcontext.gregs[3] = argv2;
    thread->uc_mcontext.gregs[4] = argv3;
    thread->uc_mcontext.gregs[5] = argv4;
    thread->uc_mcontext.gregs[6] = argv5;
    thread->uc_mcontext.gregs[7] = argv6;
    thread->uc_mcontext.gregs[8] = argv7;
    thread->uc_mcontext.gregs[9] = argv8;
    
    //set fn_ptr to func
    thread->uc_mcontext.gregs[0] = (unsigned long int) &func;
    thread->uc_mcontext.gregs[1] = (unsigned long int) thread->uc_stack;
    thread->fn_ptr = func;
}

void swapcontext(ucontext_t* oldThread, ucontext_t* newThread) {
    swap(oldThread->uc_mcontext.gregs, newThread->uc_mcontext.gregs);
}
