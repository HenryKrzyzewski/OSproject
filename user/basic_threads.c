// #include <malloc.h>
// #include <ucontext.h>
// #include <stdio.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "basic_threads.h"
#include "uspace_threads.h"
#include "sleepLock.h"

// 64kB stack
#define THREAD_STACK_SIZE 1024 * 64

/*
   max number of threads
   */
#define MAX_THREADS 5
typedef int bool;
#define false 0
#define true 1

// storage for your thread data
ucontext_t threads[MAX_THREADS];
struct sleeplock lock;
// add additional constants and globals here as you need
int active_threads[MAX_THREADS];
bool finished = false;
ucontext_t scheduler;
int to_free = -1;
bool free_thread = false;
int currThreadIndex = 0;

int count;

void display_context (ucontext_t* cont) {
   void* stack = cont->uc_stack;
   void* original = cont->original;
   mcontext_t regset = cont->uc_mcontext;

   uint64 ra = regset.ra;
   uint64 sp = regset.sp;
   uint64 a0 = regset.a0;
   uint64 a1 = regset.a1;
   uint64 a2 = regset.a2;

   void* func = cont->fn_ptr;

   printf("\n-- CONTEXT INFORMATION --\nStack: %p\nOriginal: %p\nRegisters...\n   ra: %p\n   sp: %p\n   a0: %d\n   a1: %d\n   a2: %d\nFunction: %p\n-- END --\n\n", stack, original, ra, sp, a0, a1, a2, func);

}

void add_10_to_count()
{
   printf("Starting thread function\n");
   for (int i = 0; i < 10; i++)
   {
      yield();
      count = count + 1;
   }
   finish_thread();
}

void add_3_to_count()
{
   for (int i = 0; i < 3; i++)
   {
      yield();
      count = count + 1;
   }
   finish_thread();
}

void test_1()
{
   initialize_basic_threads();
   create_new_thread(&add_10_to_count);
   schedule_threads();
   printf("Expected: 10, Actual: %d\n", count);
}

void test_2a()
{
   count = 0;
   initialize_basic_threads();
   create_new_thread(add_10_to_count);
   create_new_thread(add_10_to_count);
   schedule_threads();
   printf("Expected: 20, Actual: %d\n", count);
}

void test_2b()
{
   count = 0;
   initialize_basic_threads();
   create_new_thread(add_3_to_count);
   create_new_thread(add_10_to_count);
   create_new_thread(add_3_to_count);
   schedule_threads();
   printf("Expected: 16, Actual: %d\n", count);
}

void initialize_basic_threads()
{
   finished = false;
   currThreadIndex = 0;
   for (int i = 0; i < MAX_THREADS; i++)
   {
      active_threads[i] = 0;
   }
   initsleeplock(&lock);
   
   //    scheduler.original = malloc(THREAD_STACK_SIZE);
   //    scheduler.uc_stack = scheduler.original + THREAD_STACK_SIZE;
   //   if (scheduler.original == 0)
   //   {
   //    //  perror("malloc: Could not allocate stack");
   //     exit(1);
   //   }

      //makecontext(&scheduler, schedule_threads, 0, 0, 0);
}

void intermediate(void (*fun_ptr)(void *), void *parameter)
{
   fun_ptr(parameter);
   finish_thread();
}

void create_new_thread(void (*fun_ptr)())
{
   int i = 0;
   while (active_threads[i] != 0)
   {
      i++;
   }
   if (i >= MAX_THREADS)
   {
      exit(1);
   }

   ucontext_t nThread;
   nThread.original = malloc(THREAD_STACK_SIZE);
   nThread.uc_stack = nThread.original + THREAD_STACK_SIZE;
   if (nThread.original == 0)
   {
      printf("Malloc error\n");
      exit(1);
   }
   makecontext(&nThread, fun_ptr, 0, 0, 0);

   threads[i] = nThread;
   active_threads[i] = 1;
   printf("Thread created\n");
}

void create_new_parameterized_thread(void (*fun_ptr)(void *), void *parameter)
{
   int i = 0;
   while (active_threads[i] != 0)
   {
      i++;
   }
   if (i >= MAX_THREADS)
   {
      exit(1);
   }
   ucontext_t nThread;

   // Modify the context to a new stack
   nThread.original = malloc(THREAD_STACK_SIZE); // need to properly
   nThread.uc_stack = nThread.original + THREAD_STACK_SIZE;
   if (nThread.original == 0)
   {
      exit(1);
   }

   // Create the new context
   makecontext(&nThread, fun_ptr, parameter, 0, 0);

   threads[i] = nThread;
   active_threads[i] = 1;
}

void schedule_threads()
{
   printf("Scheduler Beginning\n");
   while (!finished)
   {
      if (active_threads[currThreadIndex] == 0)
      {
         currThreadIndex = 0;
      }

      if (active_threads[currThreadIndex] == 1)
      {
         printf("Swapping to thread %d\n", currThreadIndex);
         printf("BEFORE\n");
         display_context(&scheduler);
         display_context(&threads[currThreadIndex]);
         swapcontext(&scheduler, &threads[currThreadIndex]);
         printf("Index: %d\n", currThreadIndex);
      }

      printf("HERE %d\n", free_thread);

      if (free_thread && to_free >= 0)
      {
         free(threads[to_free].original);
         free_thread = false;
         to_free = -1;
      }

      currThreadIndex++;

      for (int i = 0; i < MAX_THREADS; i++)
      {
         if (active_threads[i])
         {
            finished = 0;
            break;
         }
         else
         {
            finished = 1;
         }
      }
   }
}

void yield()
{
   printf("Yielding\n");
            printf("AFTER\n");
         display_context(&scheduler);
         display_context(&threads[currThreadIndex]);
         printf("returned from process\n");
   swapcontext(&threads[currThreadIndex], &scheduler); //problems here 
}

void finish_thread()
{
   printf("Thread finished\n");
   active_threads[currThreadIndex] = 0;
   free_thread = true;
   to_free = currThreadIndex;
   yield();
}

void main()
{
   test_2a();
}