#pragma once

#include "sched.h"

void init_alloc();

struct task* t_alloc();
void t_free(struct task*);