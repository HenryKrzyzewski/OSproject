#include <malloc.h>
#include <ucontext.h>
#include <stdio.h>

#include "basic_threads.h"

// 64kB stack
#define THREAD_STACK_SIZE 1024*64

/*
   max number of threads
   */
#define MAX_THREADS 5

// storage for your thread data
ucontext_t threads[MAX_THREADS];


// add additional constants and globals here as you need
int active_threads[MAX_THREADS];
bool finished = false;
ucontext_t scheduler;
int to_free = -1;
bool free_thread = false;
int currThreadIndex = 0;


void initialize_basic_threads() {
   finished = false;
   currThreadIndex = 0;
   for(int i = 0; i < MAX_THREADS; i++) {
      active_threads[i] = 0;
   }
}

void intermediate(void (*fun_ptr)(void*), void* parameter) {
   fun_ptr(parameter);
   finish_thread();
}

void create_new_thread(void (*fun_ptr)()) {
   int i = 0;
   while(active_threads[i] != 0) {
      i++;
   }
  if(i >= MAX_THREADS) {
   perror("max: Ran out of threads");
   exit(1);
  }
   ucontext_t nThread;
  // Get the current execution context
  nThread = {}

  // Modify the context to a new stack
  nThread.uc_link = 0;
  nThread.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  nThread.uc_stack.ss_size = THREAD_STACK_SIZE;
  nThread.uc_stack.ss_flags = 0;
  if (nThread.uc_stack.ss_sp == 0)
  {
    perror("malloc: Could not allocate stack");
    exit(1);
  }

  // Create the new context
//   void (*intermediatePtr)() = (void(*)()) &intermediate;
   void (* intermediatePtr)() = (void(*)()) &intermediate;
  makecontext(&nThread, intermediatePtr, 2, fun_ptr, NULL);
  threads[i] = nThread;
  active_threads[i] = 1;
}




void create_new_parameterized_thread(void (*fun_ptr)(void*), void* parameter) {
   int i = 0;
   while(active_threads[i] != 0) {
      i++;
   }
  if(i >= MAX_THREADS) {
   perror("max: Ran out of threads");
   exit(1);
  }
   ucontext_t nThread;
  
  getcontext(&nThread);

  // Modify the context to a new stack
  nThread.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  nThread.uc_stack.ss_size = THREAD_STACK_SIZE;
  nThread.uc_stack.ss_flags = 0;
  if (nThread.uc_stack.ss_sp == 0)
  {
    perror("malloc: Could not allocate stack");
    exit(1);
  }

  // Create the new context
//   void (*intermediatePtr)() = (void(*)()) &intermediate;
//   makecontext(&nThread, intermediatePtr, 2, fun_ptr, parameter);
  makecontext(&nThread, void(*) fun_ptr, 0);
  threads[i] = nThread;
  active_threads[i] = 1;
}


void schedule_threads() {
   while(!finished) {
      if(active_threads[currThreadIndex] == 0) {
         currThreadIndex = 0;
      }

      if(active_threads[currThreadIndex] == 1) {
         swapcontext(&scheduler, &threads[currThreadIndex]);
      }

      if(free_thread && to_free >= 0) {
         free(threads[to_free].uc_stack.ss_sp);
         free_thread = false;
         to_free = -1;
      }

      currThreadIndex++;

      for(int i = 0; i < MAX_THREADS; i++) {
         if(active_threads[i]) {
            finished = 0;
            break;
         } else {
            finished = 1;
         }
      }
   }
}

void yield() {
   swapcontext(&threads[currThreadIndex], &scheduler);
}

void finish_thread() {
    active_threads[currThreadIndex] = 0;
    free_thread = true;
    to_free = currThreadIndex;
    yield();
}


void main () {
   test_1();
}

int count;

void add_10_to_count()
{
  for(int i = 0; i < 10; i++) {
    yield();
    count = count + 1;
  }
  finish_thread();
}


void test_1(CuTest *tc) {
  count = 0;
  initialize_basic_threads();
  create_new_thread(add_10_to_count);
  schedule_threads();
  printf("Count: %d\n", count);
}