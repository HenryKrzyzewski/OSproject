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
extern void swap(mcontext_t*, mcontext_t*);

void makecontext(ucontext_t* thread, void* func, void* argv1, void* argv2, void* argv3
){
    thread->uc_mcontext.a0 = (uint64) argv1 | 0;
    thread->uc_mcontext.a1 = (uint64) argv2 | 0;
    thread->uc_mcontext.a2 = (uint64) argv3 | 0;
    
    //set fn_ptr to func
    thread->uc_mcontext.ra = (unsigned long int) func;
    thread->uc_mcontext.sp = (unsigned long int) thread->original;
    thread->fn_ptr = func;
}

void swapcontext(ucontext_t* oldThread, ucontext_t* newThread) {
    swap(&oldThread->uc_mcontext, &newThread->uc_mcontext);
 }
