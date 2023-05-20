
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "basic_threads.h"
#include "uspace_threads.h"
#include "sleepLock.h"

// 64kB stack
#define THREAD_STACK_SIZE 1024 * 64

#define MAX_THREADS 5
typedef int bool;
#define false 0
#define true 1

// storage for threads
ucontext_t threads[MAX_THREADS];

//concurrency lock
struct sleeplock lock;

//  additional constants and globals
int active_threads[MAX_THREADS];
bool finished = false;
ucontext_t scheduler;
int to_free = -1;
bool free_thread = false;
int currThreadIndex = 0;

int count;

void display_context(ucontext_t *cont)
{
   void *stack = cont->uc_stack;
   void *original = cont->original;
   mcontext_t regset = cont->uc_mcontext;

   uint64 ra = regset.ra;
   uint64 sp = regset.sp;
   uint64 a0 = regset.a0;
   uint64 a1 = regset.a1;
   uint64 a2 = regset.a2;

   void *func = cont->fn_ptr;

   printf("\n-- CONTEXT INFORMATION --\nStack: %p\nOriginal: %p\nRegisters...\n   ra: %p\n   sp: %p\n   a0: %d\n   a1: %d\n   a2: %d\nFunction: %p\n-- END --\n\n", stack, original, ra, sp, a0, a1, a2, func);
}

void add_10_to_count()
{
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

   
   nThread.original = malloc(THREAD_STACK_SIZE);
   nThread.uc_stack = nThread.original + THREAD_STACK_SIZE;
   if (nThread.original == 0)
   {
      printf("Malloc error\n");
      exit(1);
   }

   makecontext(&nThread, fun_ptr, parameter, 0, 0);

   threads[i] = nThread;
   active_threads[i] = 1;
}

void schedule_threads()
{
   while (!finished)
   {
      if (active_threads[currThreadIndex] == 0)
      {
         currThreadIndex = 0;
      }

      if (active_threads[currThreadIndex] == 1)
      {
         printf("BEFORE SWAP\n");
         display_context(&scheduler);
         display_context(&threads[currThreadIndex]);

         swapcontext(&scheduler, &threads[currThreadIndex]);
      }

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
   printf("AFTER SWAP\n");
   display_context(&scheduler);
   display_context(&threads[currThreadIndex]);

   swapcontext(&threads[currThreadIndex], &scheduler); 
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