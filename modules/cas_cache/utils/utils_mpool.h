/*
 * Copyright(c) 2012-2021 Intel Corporation
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef UTILS_MPOOL_H_
#define UTILS_MPOOL_H_

#include <linux/types.h>

#define MPOOL_ALLOCATOR_NAME_MAX 128

enum {
	env_mpool_1,
	env_mpool_2,
	env_mpool_4,
	env_mpool_8,
	env_mpool_16,
	env_mpool_32,
	env_mpool_64,
	env_mpool_128,

	env_mpool_max
};

struct env_mpool;

/**
 * @brief Create CAS memory pool
 *
 * @param hdr_size size of constant allocation part
 * @param elem_size size increment for each element
 * @param flags Allocation flags
 * @param mpool_max Maximal allocator size (power of two)
 * @param fallback Should allocations fall back to vmalloc if allocator fails
 * @param limits Array of rpool preallocation limits per each mpool allocation
 * 		order or NULL if defaults are to be used. Array should have
 * 		mpool_max elements
 * @param name_prefix Format name prefix
 * @param zero Unused parameter
 *
 * @return CAS memory pool
 */
struct env_mpool *env_mpool_create(uint32_t hdr_size, uint32_t elem_size,
		int flags, int mpool_max, bool fallback,
		const uint32_t limits[env_mpool_max],
		const char *name_prefix, bool zero);

/**
 * @brief Destroy existing memory pool
 *
 * @param mpool memory pool
 */
void env_mpool_destroy(struct env_mpool *mpool);

/**
 * @brief Allocate new items of memory pool
 *
 * @note Allocation based on ATOMIC memory pool and this function can be called
 * when IRQ disable
 *
 * @param mpool CAS memory pool reference
 * @param count Count of elements to be allocated
 *
 * @return Pointer to the new items
 */
void *env_mpool_new(struct env_mpool *mpool, uint32_t count);

/**
 * @brief Allocate new items of memory pool with specified allocation flag
 *
 * @param mpool CAS memory pool reference
 * @param count Count of elements to be allocated
 * @param flags Kernel allocation falgs
 *
 * @return Pointer to the new items
 */
void *env_mpool_new_f(struct env_mpool *mpool, uint32_t count, int flags);

/**
 * @brief Free existing items of memory pool
 *
 * @param mpool CAS memory pool reference
 * @param items Items to be freed
 * @param count - Count of elements to be free
 *
 * @return Allocation was freed
 */
bool env_mpool_del(struct env_mpool *mpool, void *items, uint32_t count);

#endif /* UTILS_MPOOL_H_ */
