// 
// Header File for userspace threads implementation
//

#include <ucontext.h>
#include <signal.h>
 
void makecontext(ucontext_t thread, void* func, void* args);
void swapcontext(ucontext_t oldThread, ucontext_t newThread);

