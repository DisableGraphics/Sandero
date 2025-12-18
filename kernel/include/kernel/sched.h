#pragma once
// based on brennan.io/2020/05/24/userspace-cooperative-multitasking/
#include <setjmp.h>

struct task {
    enum {
        ST_CREATED,
        ST_RUNNING,
        ST_WAITING,
    } status;

    int id;

    jmp_buf buf;

    void (*func)(void);

    struct task* next;

    void *stack_bottom;
};


void scheduler_init(void);
void scheduler_create_task(void (*func)(void), void* stack_bottom);
void scheduler_run(void);

void scheduler_exit_current_task(void);
void scheduler_relinquish(void);