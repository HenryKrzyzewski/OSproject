#include <signal.h>
#include <stack.h>
#include <context.h>


typedef struct {
	stack_t uc_stack;
	mcontext_t uc_mcontext;
	int id;
	void* fn_ptr;
}ucontext_t;
