#include <kernel/sched.h>
#include <kernel/alloc.h>
#include <stddef.h>

struct scheduler_private {
	jmp_buf buf;
	struct task* current;
	struct task* head;
} priv;

static struct task task_sentinel;

void scheduler_init(void) {
	priv.current = NULL;
	priv.head = &task_sentinel;
	task_sentinel.next = NULL;
}

void add_to_end(struct task* list, struct task* task) {
	struct task* prev = list;
	while((list = list->next)) {
		prev = list;
	}
	prev->next = task;
	task->next = NULL;
}

void remove(struct task* list, struct task* task) {
	struct task* prev = list;
	while((list = list->next) != task) {
		prev = list;
	}
	prev->next = task->next;
	task->next = NULL;
}

void scheduler_create_task(void (*func)(void), void* stack_bottom) {
	static int id = 1;
	struct task *task = t_alloc();
	task->status = ST_CREATED;
	task->func = func;
	task->id = id++;
	task->stack_bottom = stack_bottom;
	add_to_end(priv.head, task);
}

enum {
	INIT=0,
	SCHEDULE,
	EXIT_TASK,
};

static struct task *scheduler_choose_task(void) {
	struct task *task = priv.head;

	while((task = task->next)) {
		if (task->status == ST_RUNNING || task->status == ST_CREATED) {
			remove(priv.head, task);
			add_to_end(priv.head, task);
			return task;
		}
	}
	return NULL;
}

static void scheduler_free_current_task(void) {
	struct task *task = priv.current;
	priv.current = NULL;
	t_free(task);
}

static void schedule(void) {
	struct task *next = scheduler_choose_task();

	if (!next) {
		return;
	}

	priv.current = next;
	if (next->status == ST_CREATED) {
		/*
		 * This task has not been started yet. Assign a new stack
		 * pointer, run the task, and exit it at the end.
		 */
		register void *top = next->stack_bottom;
		__asm __volatile(
			"movl %[rs], %%esp \n"
			: [ rs ] "+r" (top) ::
		);

		/*
		 * Run the task function
		 */
		next->status = ST_RUNNING;
		next->func();

		/*
		 * The stack pointer should be back where we set it. Returning would be
		 * a very, very bad idea. Let's instead exit
		 */
		scheduler_exit_current_task();
	} else {
		longjmp(next->buf, 1);
	}
	/* NO RETURN */
}

void scheduler_run(void) {
	/* This is the exit path for the scheduler! */
	switch (setjmp(priv.buf)) {
	case EXIT_TASK:
		scheduler_free_current_task();
	case INIT:
	case SCHEDULE:
		schedule();
		/* if return, there's nothing else to do and we exit */
		return;
	default:
		__asm __volatile("cli; hlt");
		return;
	}
}

void scheduler_relinquish(void) {
	if (setjmp(priv.current->buf)) {
		return;
	} else {
		longjmp(priv.buf, SCHEDULE);
	}
}

void scheduler_exit_current_task(void) {
	struct task *task = priv.current;
	remove(priv.head, task);
	longjmp(priv.buf, EXIT_TASK);
	/* NO RETURN */
}

