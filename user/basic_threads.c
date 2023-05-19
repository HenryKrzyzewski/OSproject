// #include <malloc.h>
// #include <ucontext.h>
// #include <stdio.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "basic_threads.h"
#include "uspace_threads.h"

// 64kB stack
#define THREAD_STACK_SIZE 1024*64

/*
   max number of threads
   */
#define MAX_THREADS 5
typedef int bool;
#define false 0
#define true 1

// storage for your thread data
ucontext_t threads[MAX_THREADS];


// add additional constants and globals here as you need
int active_threads[MAX_THREADS];
bool finished = false;
ucontext_t scheduler;
int to_free = -1;
bool free_thread = false;
int currThreadIndex = 0;

int count;

void add_10_to_count()
{
   printf("Starting thread function\n");
  for(int i = 0; i < 10; i++) {
    yield();
    count = count + 1;
  }
  printf("Yielding\n");
  finish_thread();
}

void add_3_to_count()
{
  for(int i = 0; i < 3; i++) {
    yield();
    count = count + 1;
  }
  finish_thread();
}

void test_1() {
  initialize_basic_threads();
  create_new_thread(&add_10_to_count);
  schedule_threads();
  printf("Expected: 10, Actual: %d\n", count);
}

void test_2a() {
  count = 0;
  initialize_basic_threads();
  create_new_thread(add_10_to_count);
  create_new_thread(add_10_to_count);
  schedule_threads();
  printf("Expected: 20, Actual: %d\n", count);
}

void test_2b() {
  count = 0;
  initialize_basic_threads();
  create_new_thread(add_3_to_count);
  create_new_thread(add_10_to_count);
  create_new_thread(add_3_to_count);
  schedule_threads();
  printf("Expected: 16, Actual: %d\n", count);
}


void initialize_basic_threads() {
   finished = false;
   currThreadIndex = 0;
   for(int i = 0; i < MAX_THREADS; i++) {
      active_threads[i] = 0;
   }
//    scheduler.original = malloc(THREAD_STACK_SIZE); //need to properly 
//    scheduler.uc_stack = scheduler.original + THREAD_STACK_SIZE;
//   if (scheduler.original == 0)
//   {
//    //  perror("malloc: Could not allocate stack");
//     exit(1);
//   }
  
//    makecontext(&scheduler, schedule_threads);
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
   exit(1);
  }

ucontext_t nThread;
  nThread.original = malloc(THREAD_STACK_SIZE); 
  nThread.uc_stack = nThread.original + THREAD_STACK_SIZE;
  if (nThread.original == 0)
  {
    exit(1);
  }
  makecontext(&nThread, fun_ptr, 0, 0, 0, 0, 0, 0, 0, 0);


  threads[i] = nThread;
  active_threads[i] = 1;
  printf("Thread created\n");
}




void create_new_parameterized_thread(void (*fun_ptr)(void*), void* parameter) {
   int i = 0;
   while(active_threads[i] != 0) {
      i++;
   }
  if(i >= MAX_THREADS) {
   exit(1);
  }
   ucontext_t nThread;

  // Modify the context to a new stack
  nThread.original = malloc(THREAD_STACK_SIZE); //need to properly 
  nThread.uc_stack = nThread.original + THREAD_STACK_SIZE;
  if (nThread.original == 0)
  {
    exit(1);
  }

  // Create the new context
  makecontext(&nThread, fun_ptr, parameter, 0, 0, 0, 0, 0, 0, 0);
  
  threads[i] = nThread;
  active_threads[i] = 1;
}


void schedule_threads() {
   printf("Scheduler Beginning\n");
   while(!finished) {
      if(active_threads[currThreadIndex] == 0) {
         currThreadIndex = 0;
      }

      if(active_threads[currThreadIndex] == 1) {
         printf("Swapping to thread %d\n", currThreadIndex);
         swapcontext(&scheduler, &threads[currThreadIndex]);
      }

      if(free_thread && to_free >= 0) {
         free(threads[to_free].original);
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
   printf("Yielding\n");
   swapcontext(&threads[currThreadIndex], &scheduler);
}

void finish_thread() {
   printf("Thread finished\n");
    active_threads[currThreadIndex] = 0;
    free_thread = true;
    to_free = currThreadIndex;
    yield();
}



void main () {
   test_1();
}