// SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#include "rxe.h"
#include "rxe_loc.h"

/* info about object pools
<<<<<<< HEAD
=======
 * note that mr and mw share a single index space
 * so that one can map an lkey to the correct type of object
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 */
struct rxe_type_info rxe_type_info[RXE_NUM_TYPES] = {
	[RXE_TYPE_UC] = {
		.name		= "rxe-uc",
		.size		= sizeof(struct rxe_ucontext),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_ucontext, pelem),
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.flags          = RXE_POOL_NO_ALLOC,
	},
	[RXE_TYPE_PD] = {
		.name		= "rxe-pd",
		.size		= sizeof(struct rxe_pd),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_pd, pelem),
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.flags		= RXE_POOL_NO_ALLOC,
	},
	[RXE_TYPE_AH] = {
		.name		= "rxe-ah",
		.size		= sizeof(struct rxe_ah),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_ah, pelem),
		.flags		= RXE_POOL_NO_ALLOC,
=======
		.flags		= RXE_POOL_ATOMIC | RXE_POOL_NO_ALLOC,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	},
	[RXE_TYPE_SRQ] = {
		.name		= "rxe-srq",
		.size		= sizeof(struct rxe_srq),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_srq, pelem),
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.flags		= RXE_POOL_INDEX | RXE_POOL_NO_ALLOC,
		.min_index	= RXE_MIN_SRQ_INDEX,
		.max_index	= RXE_MAX_SRQ_INDEX,
	},
	[RXE_TYPE_QP] = {
		.name		= "rxe-qp",
		.size		= sizeof(struct rxe_qp),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_qp, pelem),
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.cleanup	= rxe_qp_cleanup,
		.flags		= RXE_POOL_INDEX,
		.min_index	= RXE_MIN_QP_INDEX,
		.max_index	= RXE_MAX_QP_INDEX,
	},
	[RXE_TYPE_CQ] = {
		.name		= "rxe-cq",
		.size		= sizeof(struct rxe_cq),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_cq, pelem),
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.flags          = RXE_POOL_NO_ALLOC,
		.cleanup	= rxe_cq_cleanup,
	},
	[RXE_TYPE_MR] = {
		.name		= "rxe-mr",
<<<<<<< HEAD
		.size		= sizeof(struct rxe_mr),
		.elem_offset	= offsetof(struct rxe_mr, pelem),
		.cleanup	= rxe_mr_cleanup,
=======
		.size		= sizeof(struct rxe_mem),
		.cleanup	= rxe_mem_cleanup,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.flags		= RXE_POOL_INDEX,
		.max_index	= RXE_MAX_MR_INDEX,
		.min_index	= RXE_MIN_MR_INDEX,
	},
	[RXE_TYPE_MW] = {
		.name		= "rxe-mw",
<<<<<<< HEAD
		.size		= sizeof(struct rxe_mw),
		.elem_offset	= offsetof(struct rxe_mw, pelem),
		.flags		= RXE_POOL_INDEX | RXE_POOL_NO_ALLOC,
=======
		.size		= sizeof(struct rxe_mem),
		.flags		= RXE_POOL_INDEX,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.max_index	= RXE_MAX_MW_INDEX,
		.min_index	= RXE_MIN_MW_INDEX,
	},
	[RXE_TYPE_MC_GRP] = {
		.name		= "rxe-mc_grp",
		.size		= sizeof(struct rxe_mc_grp),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_mc_grp, pelem),
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		.cleanup	= rxe_mc_cleanup,
		.flags		= RXE_POOL_KEY,
		.key_offset	= offsetof(struct rxe_mc_grp, mgid),
		.key_size	= sizeof(union ib_gid),
	},
	[RXE_TYPE_MC_ELEM] = {
		.name		= "rxe-mc_elem",
		.size		= sizeof(struct rxe_mc_elem),
<<<<<<< HEAD
		.elem_offset	= offsetof(struct rxe_mc_elem, pelem),
=======
		.flags		= RXE_POOL_ATOMIC,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	},
};

static inline const char *pool_name(struct rxe_pool *pool)
{
	return rxe_type_info[pool->type].name;
}

static int rxe_pool_init_index(struct rxe_pool *pool, u32 max, u32 min)
{
	int err = 0;
	size_t size;

	if ((max - min + 1) < pool->max_elem) {
		pr_warn("not enough indices for max_elem\n");
		err = -EINVAL;
		goto out;
	}

<<<<<<< HEAD
	pool->index.max_index = max;
	pool->index.min_index = min;

	size = BITS_TO_LONGS(max - min + 1) * sizeof(long);
	pool->index.table = kmalloc(size, GFP_KERNEL);
	if (!pool->index.table) {
=======
	pool->max_index = max;
	pool->min_index = min;

	size = BITS_TO_LONGS(max - min + 1) * sizeof(long);
	pool->table = kmalloc(size, GFP_KERNEL);
	if (!pool->table) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		err = -ENOMEM;
		goto out;
	}

<<<<<<< HEAD
	pool->index.table_size = size;
	bitmap_zero(pool->index.table, max - min + 1);
=======
	pool->table_size = size;
	bitmap_zero(pool->table, max - min + 1);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

out:
	return err;
}

int rxe_pool_init(
	struct rxe_dev		*rxe,
	struct rxe_pool		*pool,
	enum rxe_elem_type	type,
	unsigned int		max_elem)
{
	int			err = 0;
	size_t			size = rxe_type_info[type].size;

	memset(pool, 0, sizeof(*pool));

	pool->rxe		= rxe;
	pool->type		= type;
	pool->max_elem		= max_elem;
	pool->elem_size		= ALIGN(size, RXE_POOL_ALIGN);
	pool->flags		= rxe_type_info[type].flags;
<<<<<<< HEAD
	pool->index.tree	= RB_ROOT;
	pool->key.tree		= RB_ROOT;
=======
	pool->tree		= RB_ROOT;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	pool->cleanup		= rxe_type_info[type].cleanup;

	atomic_set(&pool->num_elem, 0);

<<<<<<< HEAD
=======
	kref_init(&pool->ref_cnt);

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	rwlock_init(&pool->pool_lock);

	if (rxe_type_info[type].flags & RXE_POOL_INDEX) {
		err = rxe_pool_init_index(pool,
					  rxe_type_info[type].max_index,
					  rxe_type_info[type].min_index);
		if (err)
			goto out;
	}

	if (rxe_type_info[type].flags & RXE_POOL_KEY) {
<<<<<<< HEAD
		pool->key.key_offset = rxe_type_info[type].key_offset;
		pool->key.key_size = rxe_type_info[type].key_size;
	}

=======
		pool->key_offset = rxe_type_info[type].key_offset;
		pool->key_size = rxe_type_info[type].key_size;
	}

	pool->state = RXE_POOL_STATE_VALID;

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
out:
	return err;
}

<<<<<<< HEAD
void rxe_pool_cleanup(struct rxe_pool *pool)
{
	if (atomic_read(&pool->num_elem) > 0)
		pr_warn("%s pool destroyed with unfree'd elem\n",
			pool_name(pool));

	kfree(pool->index.table);
=======
static void rxe_pool_release(struct kref *kref)
{
	struct rxe_pool *pool = container_of(kref, struct rxe_pool, ref_cnt);

	pool->state = RXE_POOL_STATE_INVALID;
	kfree(pool->table);
}

static void rxe_pool_put(struct rxe_pool *pool)
{
	kref_put(&pool->ref_cnt, rxe_pool_release);
}

void rxe_pool_cleanup(struct rxe_pool *pool)
{
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
	pool->state = RXE_POOL_STATE_INVALID;
	if (atomic_read(&pool->num_elem) > 0)
		pr_warn("%s pool destroyed with unfree'd elem\n",
			pool_name(pool));
	write_unlock_irqrestore(&pool->pool_lock, flags);

	rxe_pool_put(pool);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static u32 alloc_index(struct rxe_pool *pool)
{
	u32 index;
<<<<<<< HEAD
	u32 range = pool->index.max_index - pool->index.min_index + 1;

	index = find_next_zero_bit(pool->index.table, range, pool->index.last);
	if (index >= range)
		index = find_first_zero_bit(pool->index.table, range);

	WARN_ON_ONCE(index >= range);
	set_bit(index, pool->index.table);
	pool->index.last = index;
	return index + pool->index.min_index;
=======
	u32 range = pool->max_index - pool->min_index + 1;

	index = find_next_zero_bit(pool->table, range, pool->last);
	if (index >= range)
		index = find_first_zero_bit(pool->table, range);

	WARN_ON_ONCE(index >= range);
	set_bit(index, pool->table);
	pool->last = index;
	return index + pool->min_index;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static void insert_index(struct rxe_pool *pool, struct rxe_pool_entry *new)
{
<<<<<<< HEAD
	struct rb_node **link = &pool->index.tree.rb_node;
=======
	struct rb_node **link = &pool->tree.rb_node;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct rb_node *parent = NULL;
	struct rxe_pool_entry *elem;

	while (*link) {
		parent = *link;
<<<<<<< HEAD
		elem = rb_entry(parent, struct rxe_pool_entry, index_node);
=======
		elem = rb_entry(parent, struct rxe_pool_entry, node);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		if (elem->index == new->index) {
			pr_warn("element already exists!\n");
			goto out;
		}

		if (elem->index > new->index)
			link = &(*link)->rb_left;
		else
			link = &(*link)->rb_right;
	}

<<<<<<< HEAD
	rb_link_node(&new->index_node, parent, link);
	rb_insert_color(&new->index_node, &pool->index.tree);
=======
	rb_link_node(&new->node, parent, link);
	rb_insert_color(&new->node, &pool->tree);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
out:
	return;
}

static void insert_key(struct rxe_pool *pool, struct rxe_pool_entry *new)
{
<<<<<<< HEAD
	struct rb_node **link = &pool->key.tree.rb_node;
=======
	struct rb_node **link = &pool->tree.rb_node;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct rb_node *parent = NULL;
	struct rxe_pool_entry *elem;
	int cmp;

	while (*link) {
		parent = *link;
<<<<<<< HEAD
		elem = rb_entry(parent, struct rxe_pool_entry, key_node);

		cmp = memcmp((u8 *)elem + pool->key.key_offset,
			     (u8 *)new + pool->key.key_offset, pool->key.key_size);
=======
		elem = rb_entry(parent, struct rxe_pool_entry, node);

		cmp = memcmp((u8 *)elem + pool->key_offset,
			     (u8 *)new + pool->key_offset, pool->key_size);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		if (cmp == 0) {
			pr_warn("key already exists!\n");
			goto out;
		}

		if (cmp > 0)
			link = &(*link)->rb_left;
		else
			link = &(*link)->rb_right;
	}

<<<<<<< HEAD
	rb_link_node(&new->key_node, parent, link);
	rb_insert_color(&new->key_node, &pool->key.tree);
=======
	rb_link_node(&new->node, parent, link);
	rb_insert_color(&new->node, &pool->tree);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
out:
	return;
}

<<<<<<< HEAD
void __rxe_add_key_locked(struct rxe_pool_entry *elem, void *key)
{
	struct rxe_pool *pool = elem->pool;

	memcpy((u8 *)elem + pool->key.key_offset, key, pool->key.key_size);
	insert_key(pool, elem);
}

void __rxe_add_key(struct rxe_pool_entry *elem, void *key)
{
=======
void rxe_add_key(void *arg, void *key)
{
	struct rxe_pool_entry *elem = arg;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
<<<<<<< HEAD
	__rxe_add_key_locked(elem, key);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void __rxe_drop_key_locked(struct rxe_pool_entry *elem)
{
	struct rxe_pool *pool = elem->pool;

	rb_erase(&elem->key_node, &pool->key.tree);
}

void __rxe_drop_key(struct rxe_pool_entry *elem)
{
=======
	memcpy((u8 *)elem + pool->key_offset, key, pool->key_size);
	insert_key(pool, elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void rxe_drop_key(void *arg)
{
	struct rxe_pool_entry *elem = arg;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
<<<<<<< HEAD
	__rxe_drop_key_locked(elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void __rxe_add_index_locked(struct rxe_pool_entry *elem)
{
	struct rxe_pool *pool = elem->pool;

	elem->index = alloc_index(pool);
	insert_index(pool, elem);
}

void __rxe_add_index(struct rxe_pool_entry *elem)
{
=======
	rb_erase(&elem->node, &pool->tree);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void rxe_add_index(void *arg)
{
	struct rxe_pool_entry *elem = arg;
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
	elem->index = alloc_index(pool);
	insert_index(pool, elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void rxe_drop_index(void *arg)
{
	struct rxe_pool_entry *elem = arg;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
<<<<<<< HEAD
	__rxe_add_index_locked(elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void __rxe_drop_index_locked(struct rxe_pool_entry *elem)
{
	struct rxe_pool *pool = elem->pool;

	clear_bit(elem->index - pool->index.min_index, pool->index.table);
	rb_erase(&elem->index_node, &pool->index.tree);
}

void __rxe_drop_index(struct rxe_pool_entry *elem)
{
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
	__rxe_drop_index_locked(elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void *rxe_alloc_locked(struct rxe_pool *pool)
{
	struct rxe_type_info *info = &rxe_type_info[pool->type];
	struct rxe_pool_entry *elem;
	u8 *obj;
=======
	clear_bit(elem->index - pool->min_index, pool->table);
	rb_erase(&elem->node, &pool->tree);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}

void *rxe_alloc(struct rxe_pool *pool)
{
	struct rxe_pool_entry *elem;
	unsigned long flags;

	might_sleep_if(!(pool->flags & RXE_POOL_ATOMIC));

	read_lock_irqsave(&pool->pool_lock, flags);
	if (pool->state != RXE_POOL_STATE_VALID) {
		read_unlock_irqrestore(&pool->pool_lock, flags);
		return NULL;
	}
	kref_get(&pool->ref_cnt);
	read_unlock_irqrestore(&pool->pool_lock, flags);

	if (!ib_device_try_get(&pool->rxe->ib_dev))
		goto out_put_pool;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (atomic_inc_return(&pool->num_elem) > pool->max_elem)
		goto out_cnt;

<<<<<<< HEAD
	obj = kzalloc(info->size, GFP_ATOMIC);
	if (!obj)
		goto out_cnt;

	elem = (struct rxe_pool_entry *)(obj + info->elem_offset);

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	return obj;

out_cnt:
	atomic_dec(&pool->num_elem);
	return NULL;
}

void *rxe_alloc(struct rxe_pool *pool)
{
	struct rxe_type_info *info = &rxe_type_info[pool->type];
	struct rxe_pool_entry *elem;
	u8 *obj;

	if (atomic_inc_return(&pool->num_elem) > pool->max_elem)
		goto out_cnt;

	obj = kzalloc(info->size, GFP_KERNEL);
	if (!obj)
		goto out_cnt;

	elem = (struct rxe_pool_entry *)(obj + info->elem_offset);

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	return obj;

out_cnt:
	atomic_dec(&pool->num_elem);
	return NULL;
}

int __rxe_add_to_pool(struct rxe_pool *pool, struct rxe_pool_entry *elem)
{
=======
	elem = kzalloc(rxe_type_info[pool->type].size,
				 (pool->flags & RXE_POOL_ATOMIC) ?
				 GFP_ATOMIC : GFP_KERNEL);
	if (!elem)
		goto out_cnt;

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	return elem;

out_cnt:
	atomic_dec(&pool->num_elem);
	ib_device_put(&pool->rxe->ib_dev);
out_put_pool:
	rxe_pool_put(pool);
	return NULL;
}

int rxe_add_to_pool(struct rxe_pool *pool, struct rxe_pool_entry *elem)
{
	unsigned long flags;

	might_sleep_if(!(pool->flags & RXE_POOL_ATOMIC));

	read_lock_irqsave(&pool->pool_lock, flags);
	if (pool->state != RXE_POOL_STATE_VALID) {
		read_unlock_irqrestore(&pool->pool_lock, flags);
		return -EINVAL;
	}
	kref_get(&pool->ref_cnt);
	read_unlock_irqrestore(&pool->pool_lock, flags);

	if (!ib_device_try_get(&pool->rxe->ib_dev))
		goto out_put_pool;

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (atomic_inc_return(&pool->num_elem) > pool->max_elem)
		goto out_cnt;

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	return 0;

out_cnt:
	atomic_dec(&pool->num_elem);
<<<<<<< HEAD
=======
	ib_device_put(&pool->rxe->ib_dev);
out_put_pool:
	rxe_pool_put(pool);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	return -EINVAL;
}

void rxe_elem_release(struct kref *kref)
{
	struct rxe_pool_entry *elem =
		container_of(kref, struct rxe_pool_entry, ref_cnt);
	struct rxe_pool *pool = elem->pool;
<<<<<<< HEAD
	struct rxe_type_info *info = &rxe_type_info[pool->type];
	u8 *obj;
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (pool->cleanup)
		pool->cleanup(elem);

<<<<<<< HEAD
	if (!(pool->flags & RXE_POOL_NO_ALLOC)) {
		obj = (u8 *)elem - info->elem_offset;
		kfree(obj);
	}

	atomic_dec(&pool->num_elem);
}

void *rxe_pool_get_index_locked(struct rxe_pool *pool, u32 index)
{
	struct rxe_type_info *info = &rxe_type_info[pool->type];
	struct rb_node *node;
	struct rxe_pool_entry *elem;
	u8 *obj;

	node = pool->index.tree.rb_node;

	while (node) {
		elem = rb_entry(node, struct rxe_pool_entry, index_node);
=======
	if (!(pool->flags & RXE_POOL_NO_ALLOC))
		kfree(elem);
	atomic_dec(&pool->num_elem);
	ib_device_put(&pool->rxe->ib_dev);
	rxe_pool_put(pool);
}

void *rxe_pool_get_index(struct rxe_pool *pool, u32 index)
{
	struct rb_node *node = NULL;
	struct rxe_pool_entry *elem = NULL;
	unsigned long flags;

	read_lock_irqsave(&pool->pool_lock, flags);

	if (pool->state != RXE_POOL_STATE_VALID)
		goto out;

	node = pool->tree.rb_node;

	while (node) {
		elem = rb_entry(node, struct rxe_pool_entry, node);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		if (elem->index > index)
			node = node->rb_left;
		else if (elem->index < index)
			node = node->rb_right;
<<<<<<< HEAD
		else
			break;
	}

	if (node) {
		kref_get(&elem->ref_cnt);
		obj = (u8 *)elem - info->elem_offset;
	} else {
		obj = NULL;
	}

	return obj;
}

void *rxe_pool_get_index(struct rxe_pool *pool, u32 index)
{
	u8 *obj;
	unsigned long flags;

	read_lock_irqsave(&pool->pool_lock, flags);
	obj = rxe_pool_get_index_locked(pool, index);
	read_unlock_irqrestore(&pool->pool_lock, flags);

	return obj;
}

void *rxe_pool_get_key_locked(struct rxe_pool *pool, void *key)
{
	struct rxe_type_info *info = &rxe_type_info[pool->type];
	struct rb_node *node;
	struct rxe_pool_entry *elem;
	u8 *obj;
	int cmp;

	node = pool->key.tree.rb_node;

	while (node) {
		elem = rb_entry(node, struct rxe_pool_entry, key_node);

		cmp = memcmp((u8 *)elem + pool->key.key_offset,
			     key, pool->key.key_size);
=======
		else {
			kref_get(&elem->ref_cnt);
			break;
		}
	}

out:
	read_unlock_irqrestore(&pool->pool_lock, flags);
	return node ? elem : NULL;
}

void *rxe_pool_get_key(struct rxe_pool *pool, void *key)
{
	struct rb_node *node = NULL;
	struct rxe_pool_entry *elem = NULL;
	int cmp;
	unsigned long flags;

	read_lock_irqsave(&pool->pool_lock, flags);

	if (pool->state != RXE_POOL_STATE_VALID)
		goto out;

	node = pool->tree.rb_node;

	while (node) {
		elem = rb_entry(node, struct rxe_pool_entry, node);

		cmp = memcmp((u8 *)elem + pool->key_offset,
			     key, pool->key_size);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		if (cmp > 0)
			node = node->rb_left;
		else if (cmp < 0)
			node = node->rb_right;
		else
			break;
	}

<<<<<<< HEAD
	if (node) {
		kref_get(&elem->ref_cnt);
		obj = (u8 *)elem - info->elem_offset;
	} else {
		obj = NULL;
	}

	return obj;
}

void *rxe_pool_get_key(struct rxe_pool *pool, void *key)
{
	u8 *obj;
	unsigned long flags;

	read_lock_irqsave(&pool->pool_lock, flags);
	obj = rxe_pool_get_key_locked(pool, key);
	read_unlock_irqrestore(&pool->pool_lock, flags);

	return obj;
=======
	if (node)
		kref_get(&elem->ref_cnt);

out:
	read_unlock_irqrestore(&pool->pool_lock, flags);
	return node ? elem : NULL;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}
