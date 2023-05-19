//
// header file for thread structure
//


#include "stack.h"
#include "context.h"


typedef struct {
	void* uc_stack;
	mcontext_t uc_mcontext;
	int id;
	void* fn_ptr;
}ucontext_t;
