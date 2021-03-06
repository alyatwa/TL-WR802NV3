/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#ifndef TTM_MEMORY_H
#define TTM_MEMORY_H

#include <linux/workqueue.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/errno.h>

/**
 * struct ttm_mem_shrink - callback to shrink TTM memory usage.
 *
 * @do_shrink: The callback function.
 *
 * Arguments to the do_shrink functions are intended to be passed using
 * inheritance. That is, the argument class derives from struct ttm_mem_srink,
 * and can be accessed using container_of().
 */

struct ttm_mem_shrink {
	int (*do_shrink) (struct ttm_mem_shrink *);
};

/**
 * struct ttm_mem_global - Global memory accounting structure.
 *
 * @shrink: A single callback to shrink TTM memory usage. Extend this
 * to a linked list to be able to handle multiple callbacks when needed.
 * @swap_queue: A workqueue to handle shrinking in low memory situations. We
 * need a separate workqueue since it will spend a lot of time waiting
 * for the GPU, and this will otherwise block other workqueue tasks(?)
 * At this point we use only a single-threaded workqueue.
 * @work: The workqueue callback for the shrink queue.
 * @queue: Wait queue for processes suspended waiting for memory.
 * @lock: Lock to protect the @shrink - and the memory accounting members,
 * that is, essentially the whole structure with some exceptions.
 * @emer_memory: Lowmem memory limit available for root.
 * @max_memory: Lowmem memory limit available for non-root.
 * @swap_limit: Lowmem memory limit where the shrink workqueue kicks in.
 * @used_memory: Currently used lowmem memory.
 * @used_total_memory: Currently used total (lowmem + highmem) memory.
 * @total_memory_swap_limit: Total memory limit where the shrink workqueue
 * kicks in.
 * @max_total_memory: Total memory available to non-root processes.
 * @emer_total_memory: Total memory available to root processes.
 *
 * Note that this structure is not per device. It should be global for all
 * graphics devices.
 */

struct ttm_mem_global {
	struct ttm_mem_shrink *shrink;
	struct workqueue_struct *swap_queue;
	struct work_struct work;
	wait_queue_head_t queue;
	spinlock_t lock;
	uint64_t emer_memory;
	uint64_t max_memory;
	uint64_t swap_limit;
	uint64_t used_memory;
	uint64_t used_total_memory;
	uint64_t total_memory_swap_limit;
	uint64_t max_total_memory;
	uint64_t emer_total_memory;
};

/**
 * ttm_mem_init_shrink - initialize a struct ttm_mem_shrink object
 *
 * @shrink: The object to initialize.
 * @func: The callback function.
 */

static inline void ttm_mem_init_shrink(struct ttm_mem_shrink *shrink,
				       int (*func) (struct ttm_mem_shrink *))
{
	shrink->do_shrink = func;
}

/**
 * ttm_mem_register_shrink - register a struct ttm_mem_shrink object.
 *
 * @glob: The struct ttm_mem_global object to register with.
 * @shrink: An initialized struct ttm_mem_shrink object to register.
 *
 * Returns:
 * -EBUSY: There's already a callback registered. (May change).
 */

static inline int ttm_mem_register_shrink(struct ttm_mem_global *glob,
					  struct ttm_mem_shrink *shrink)
{
	spin_lock(&glob->lock);
	if (glob->shrink != NULL) {
		spin_unlock(&glob->lock);
		return -EBUSY;
	}
	glob->shrink = shrink;
	spin_unlock(&glob->lock);
	return 0;
}

/**
 * ttm_mem_unregister_shrink - unregister a struct ttm_mem_shrink object.
 *
 * @glob: The struct ttm_mem_global object to unregister from.
 * @shrink: A previously registert struct ttm_mem_shrink object.
 *
 */

static inline void ttm_mem_unregister_shrink(struct ttm_mem_global *glob,
					     struct ttm_mem_shrink *shrink)
{
	spin_lock(&glob->lock);
	BUG_ON(glob->shrink != shrink);
	glob->shrink = NULL;
	spin_unlock(&glob->lock);
}

extern int ttm_mem_global_init(struct ttm_mem_global *glob);
extern void ttm_mem_global_release(struct ttm_mem_global *glob);
extern int ttm_mem_global_alloc(struct ttm_mem_global *glob, uint64_t memory,
				bool no_wait, bool interruptible, bool himem);
extern void ttm_mem_global_free(struct ttm_mem_global *glob,
				uint64_t amount, bool himem);
extern size_t ttm_round_pot(size_t size);
#endif
