#include <kernel/sched.h>
#include <stddef.h>

int syscall_handler(size_t syscallno, size_t arg0, size_t arg1) {
	switch(syscallno) {
		case 0:
			scheduler_exit_current_task();
		case 1:
			scheduler_create_task((void (*)(void)) arg0, (void *) arg1);
		case 2:
			scheduler_relinquish();
		default:
			return -1;
	};
	return 0;
}