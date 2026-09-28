#include <kernel/sched.h>
#include <stddef.h>

#define SYSC_EXIT 0
#define SYSC_NEW_TASK 1
#define SYSC_YIELD 2

int syscall_handler(size_t syscallno, size_t arg0, size_t arg1) {
	switch(syscallno) {
		case SYSC_EXIT:
			scheduler_exit_current_task();
			break;
		case SYSC_NEW_TASK:
			return scheduler_create_task((void (*)(void)) arg0, (void *) arg1);
		case SYSC_YIELD:
			scheduler_relinquish();
			return 0;
		default:
			return -1;
	};
}