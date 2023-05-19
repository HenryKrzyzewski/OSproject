void initialize_basic_threads();

void create_new_thread(void (*fun_ptr)());

void create_new_parameterized_thread(void (*fun_ptr)(void*), void* parameter);

void schedule_threads();

void yield();

void finish_thread();
