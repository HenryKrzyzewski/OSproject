/*
 * Userspace Threads
 *
 *
 */
#include <uspace_threads.h>

//Pass in old and new contexts
extern void swap();

void makecontext(ucontext_t thread, void* func, void* args){


}

void swapcontext(ucontext_t oldThread, ucontext_t newThread) {


}
