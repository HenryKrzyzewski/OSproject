//
// Header file for thread context
// defines register storage, register list, and context struct
//

typedef unsigned long int greg_t;

typedef struct gregset
   {
     greg_t gregs[14];
   } gregset_t;

typedef struct {
	gregset_t regset;
} mcontext_t;
