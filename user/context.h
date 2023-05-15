//
// Header file for thread context
// defines register storage, register list, and context struct
//

typedef unsigned long int greg_t;


typedef struct {
	greg_t gregs[14];
} mcontext_t;
