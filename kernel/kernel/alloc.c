#include <kernel/alloc.h>
#include <stddef.h>
#define N_TASKS 512

struct slab_node {
	struct slab_node* next;
};

static struct slab_node* head;
static struct task slab[N_TASKS];

void init_alloc() {
	for (size_t i = 0; i < N_TASKS - 1; i++) {
		((struct slab_node*)&slab[i])->next =
			(struct slab_node*)&slab[i + 1];
	}
	((struct slab_node*)&slab[N_TASKS - 1])->next = NULL;
	

	head = (struct slab_node*)&slab[0];
}

struct task* t_alloc() {
	struct task* r = (struct task*)head;
	if(head) head = head->next;
	return r;
}

void t_free(struct task* t) {
	struct slab_node* p = (struct slab_node*) t;
	p->next = head;
	head = p;
}