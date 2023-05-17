//
// Header file for thread context
// defines register storage, register list, and context struct
//
#include <stdint.h>

typedef uint64_t greg_t;

//rewrite gregs into 14 different pointers for each register

typedef struct gregset
   {
     greg_t gregs[14];
   } mcontext_t;

// typedef struct {
// 	gregset_t regset;
// } mcontext_t;
