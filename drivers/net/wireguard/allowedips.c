// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include "allowedips.h"
#include "peer.h"

<<<<<<< HEAD
static struct kmem_cache *node_cache;

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static void swap_endian(u8 *dst, const u8 *src, u8 bits)
{
	if (bits == 32) {
		*(u32 *)dst = be32_to_cpu(*(const __be32 *)src);
	} else if (bits == 128) {
		((u64 *)dst)[0] = be64_to_cpu(((const __be64 *)src)[0]);
		((u64 *)dst)[1] = be64_to_cpu(((const __be64 *)src)[1]);
	}
}

static void copy_and_assign_cidr(struct allowedips_node *node, const u8 *src,
				 u8 cidr, u8 bits)
{
	node->cidr = cidr;
	node->bit_at_a = cidr / 8U;
#ifdef __LITTLE_ENDIAN
	node->bit_at_a ^= (bits / 8U - 1U) % 8U;
#endif
	node->bit_at_b = 7U - (cidr % 8U);
	node->bitlen = bits;
	memcpy(node->bits, src, bits / 8U);
}
<<<<<<< HEAD

static inline u8 choose(struct allowedips_node *node, const u8 *key)
{
	return (key[node->bit_at_a] >> node->bit_at_b) & 1;
}
=======
#define CHOOSE_NODE(parent, key) \
	parent->bit[(key[parent->bit_at_a] >> parent->bit_at_b) & 1]
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

static void push_rcu(struct allowedips_node **stack,
		     struct allowedips_node __rcu *p, unsigned int *len)
{
	if (rcu_access_pointer(p)) {
		WARN_ON(IS_ENABLED(DEBUG) && *len >= 128);
		stack[(*len)++] = rcu_dereference_raw(p);
	}
}

<<<<<<< HEAD
static void node_free_rcu(struct rcu_head *rcu)
{
	kmem_cache_free(node_cache, container_of(rcu, struct allowedips_node, rcu));
}

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static void root_free_rcu(struct rcu_head *rcu)
{
	struct allowedips_node *node, *stack[128] = {
		container_of(rcu, struct allowedips_node, rcu) };
	unsigned int len = 1;

	while (len > 0 && (node = stack[--len])) {
		push_rcu(stack, node->bit[0], &len);
		push_rcu(stack, node->bit[1], &len);
<<<<<<< HEAD
		kmem_cache_free(node_cache, node);
=======
		kfree(node);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}
}

static void root_remove_peer_lists(struct allowedips_node *root)
{
	struct allowedips_node *node, *stack[128] = { root };
	unsigned int len = 1;

	while (len > 0 && (node = stack[--len])) {
		push_rcu(stack, node->bit[0], &len);
		push_rcu(stack, node->bit[1], &len);
		if (rcu_access_pointer(node->peer))
			list_del(&node->peer_list);
	}
}

<<<<<<< HEAD
=======
static void walk_remove_by_peer(struct allowedips_node __rcu **top,
				struct wg_peer *peer, struct mutex *lock)
{
#define REF(p) rcu_access_pointer(p)
#define DEREF(p) rcu_dereference_protected(*(p), lockdep_is_held(lock))
#define PUSH(p) ({                                                             \
		WARN_ON(IS_ENABLED(DEBUG) && len >= 128);                      \
		stack[len++] = p;                                              \
	})

	struct allowedips_node __rcu **stack[128], **nptr;
	struct allowedips_node *node, *prev;
	unsigned int len;

	if (unlikely(!peer || !REF(*top)))
		return;

	for (prev = NULL, len = 0, PUSH(top); len > 0; prev = node) {
		nptr = stack[len - 1];
		node = DEREF(nptr);
		if (!node) {
			--len;
			continue;
		}
		if (!prev || REF(prev->bit[0]) == node ||
		    REF(prev->bit[1]) == node) {
			if (REF(node->bit[0]))
				PUSH(&node->bit[0]);
			else if (REF(node->bit[1]))
				PUSH(&node->bit[1]);
		} else if (REF(node->bit[0]) == prev) {
			if (REF(node->bit[1]))
				PUSH(&node->bit[1]);
		} else {
			if (rcu_dereference_protected(node->peer,
				lockdep_is_held(lock)) == peer) {
				RCU_INIT_POINTER(node->peer, NULL);
				list_del_init(&node->peer_list);
				if (!node->bit[0] || !node->bit[1]) {
					rcu_assign_pointer(*nptr, DEREF(
					       &node->bit[!REF(node->bit[0])]));
					kfree_rcu(node, rcu);
					node = DEREF(nptr);
				}
			}
			--len;
		}
	}

#undef REF
#undef DEREF
#undef PUSH
}

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static unsigned int fls128(u64 a, u64 b)
{
	return a ? fls64(a) + 64U : fls64(b);
}

static u8 common_bits(const struct allowedips_node *node, const u8 *key,
		      u8 bits)
{
	if (bits == 32)
		return 32U - fls(*(const u32 *)node->bits ^ *(const u32 *)key);
	else if (bits == 128)
		return 128U - fls128(
			*(const u64 *)&node->bits[0] ^ *(const u64 *)&key[0],
			*(const u64 *)&node->bits[8] ^ *(const u64 *)&key[8]);
	return 0;
}

static bool prefix_matches(const struct allowedips_node *node, const u8 *key,
			   u8 bits)
{
	/* This could be much faster if it actually just compared the common
	 * bits properly, by precomputing a mask bswap(~0 << (32 - cidr)), and
	 * the rest, but it turns out that common_bits is already super fast on
	 * modern processors, even taking into account the unfortunate bswap.
	 * So, we just inline it like this instead.
	 */
	return common_bits(node, key, bits) >= node->cidr;
}

static struct allowedips_node *find_node(struct allowedips_node *trie, u8 bits,
					 const u8 *key)
{
	struct allowedips_node *node = trie, *found = NULL;

	while (node && prefix_matches(node, key, bits)) {
		if (rcu_access_pointer(node->peer))
			found = node;
		if (node->cidr == bits)
			break;
<<<<<<< HEAD
		node = rcu_dereference_bh(node->bit[choose(node, key)]);
=======
		node = rcu_dereference_bh(CHOOSE_NODE(node, key));
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}
	return found;
}

/* Returns a strong reference to a peer */
static struct wg_peer *lookup(struct allowedips_node __rcu *root, u8 bits,
			      const void *be_ip)
{
	/* Aligned so it can be passed to fls/fls64 */
	u8 ip[16] __aligned(__alignof(u64));
	struct allowedips_node *node;
	struct wg_peer *peer = NULL;

	swap_endian(ip, be_ip, bits);

	rcu_read_lock_bh();
retry:
	node = find_node(rcu_dereference_bh(root), bits, ip);
	if (node) {
		peer = wg_peer_get_maybe_zero(rcu_dereference_bh(node->peer));
		if (!peer)
			goto retry;
	}
	rcu_read_unlock_bh();
	return peer;
}

static bool node_placement(struct allowedips_node __rcu *trie, const u8 *key,
			   u8 cidr, u8 bits, struct allowedips_node **rnode,
			   struct mutex *lock)
{
<<<<<<< HEAD
	struct allowedips_node *node = rcu_dereference_protected(trie, lockdep_is_held(lock));
=======
	struct allowedips_node *node = rcu_dereference_protected(trie,
						lockdep_is_held(lock));
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct allowedips_node *parent = NULL;
	bool exact = false;

	while (node && node->cidr <= cidr && prefix_matches(node, key, bits)) {
		parent = node;
		if (parent->cidr == cidr) {
			exact = true;
			break;
		}
<<<<<<< HEAD
		node = rcu_dereference_protected(parent->bit[choose(parent, key)], lockdep_is_held(lock));
=======
		node = rcu_dereference_protected(CHOOSE_NODE(parent, key),
						 lockdep_is_held(lock));
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}
	*rnode = parent;
	return exact;
}

<<<<<<< HEAD
static inline void connect_node(struct allowedips_node **parent, u8 bit, struct allowedips_node *node)
{
	node->parent_bit_packed = (unsigned long)parent | bit;
	rcu_assign_pointer(*parent, node);
}

static inline void choose_and_connect_node(struct allowedips_node *parent, struct allowedips_node *node)
{
	u8 bit = choose(parent, node->bits);
	connect_node(&parent->bit[bit], bit, node);
}

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int add(struct allowedips_node __rcu **trie, u8 bits, const u8 *key,
	       u8 cidr, struct wg_peer *peer, struct mutex *lock)
{
	struct allowedips_node *node, *parent, *down, *newnode;

	if (unlikely(cidr > bits || !peer))
		return -EINVAL;

	if (!rcu_access_pointer(*trie)) {
<<<<<<< HEAD
		node = kmem_cache_zalloc(node_cache, GFP_KERNEL);
=======
		node = kzalloc(sizeof(*node), GFP_KERNEL);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		if (unlikely(!node))
			return -ENOMEM;
		RCU_INIT_POINTER(node->peer, peer);
		list_add_tail(&node->peer_list, &peer->allowedips_list);
		copy_and_assign_cidr(node, key, cidr, bits);
<<<<<<< HEAD
		connect_node(trie, 2, node);
=======
		rcu_assign_pointer(*trie, node);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		return 0;
	}
	if (node_placement(*trie, key, cidr, bits, &node, lock)) {
		rcu_assign_pointer(node->peer, peer);
		list_move_tail(&node->peer_list, &peer->allowedips_list);
		return 0;
	}

<<<<<<< HEAD
	newnode = kmem_cache_zalloc(node_cache, GFP_KERNEL);
=======
	newnode = kzalloc(sizeof(*newnode), GFP_KERNEL);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (unlikely(!newnode))
		return -ENOMEM;
	RCU_INIT_POINTER(newnode->peer, peer);
	list_add_tail(&newnode->peer_list, &peer->allowedips_list);
	copy_and_assign_cidr(newnode, key, cidr, bits);

	if (!node) {
		down = rcu_dereference_protected(*trie, lockdep_is_held(lock));
	} else {
<<<<<<< HEAD
		const u8 bit = choose(node, key);
		down = rcu_dereference_protected(node->bit[bit], lockdep_is_held(lock));
		if (!down) {
			connect_node(&node->bit[bit], bit, newnode);
=======
		down = rcu_dereference_protected(CHOOSE_NODE(node, key),
						 lockdep_is_held(lock));
		if (!down) {
			rcu_assign_pointer(CHOOSE_NODE(node, key), newnode);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			return 0;
		}
	}
	cidr = min(cidr, common_bits(down, key, bits));
	parent = node;

	if (newnode->cidr == cidr) {
<<<<<<< HEAD
		choose_and_connect_node(newnode, down);
		if (!parent)
			connect_node(trie, 2, newnode);
		else
			choose_and_connect_node(parent, newnode);
		return 0;
	}

	node = kmem_cache_zalloc(node_cache, GFP_KERNEL);
	if (unlikely(!node)) {
		list_del(&newnode->peer_list);
		kmem_cache_free(node_cache, newnode);
		return -ENOMEM;
	}
	INIT_LIST_HEAD(&node->peer_list);
	copy_and_assign_cidr(node, newnode->bits, cidr, bits);

	choose_and_connect_node(node, down);
	choose_and_connect_node(node, newnode);
	if (!parent)
		connect_node(trie, 2, node);
	else
		choose_and_connect_node(parent, node);
=======
		rcu_assign_pointer(CHOOSE_NODE(newnode, down->bits), down);
		if (!parent)
			rcu_assign_pointer(*trie, newnode);
		else
			rcu_assign_pointer(CHOOSE_NODE(parent, newnode->bits),
					   newnode);
	} else {
		node = kzalloc(sizeof(*node), GFP_KERNEL);
		if (unlikely(!node)) {
			list_del(&newnode->peer_list);
			kfree(newnode);
			return -ENOMEM;
		}
		INIT_LIST_HEAD(&node->peer_list);
		copy_and_assign_cidr(node, newnode->bits, cidr, bits);

		rcu_assign_pointer(CHOOSE_NODE(node, down->bits), down);
		rcu_assign_pointer(CHOOSE_NODE(node, newnode->bits), newnode);
		if (!parent)
			rcu_assign_pointer(*trie, node);
		else
			rcu_assign_pointer(CHOOSE_NODE(parent, node->bits),
					   node);
	}
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	return 0;
}

void wg_allowedips_init(struct allowedips *table)
{
	table->root4 = table->root6 = NULL;
	table->seq = 1;
}

void wg_allowedips_free(struct allowedips *table, struct mutex *lock)
{
	struct allowedips_node __rcu *old4 = table->root4, *old6 = table->root6;

	++table->seq;
	RCU_INIT_POINTER(table->root4, NULL);
	RCU_INIT_POINTER(table->root6, NULL);
	if (rcu_access_pointer(old4)) {
		struct allowedips_node *node = rcu_dereference_protected(old4,
							lockdep_is_held(lock));

		root_remove_peer_lists(node);
		call_rcu(&node->rcu, root_free_rcu);
	}
	if (rcu_access_pointer(old6)) {
		struct allowedips_node *node = rcu_dereference_protected(old6,
							lockdep_is_held(lock));

		root_remove_peer_lists(node);
		call_rcu(&node->rcu, root_free_rcu);
	}
}

int wg_allowedips_insert_v4(struct allowedips *table, const struct in_addr *ip,
			    u8 cidr, struct wg_peer *peer, struct mutex *lock)
{
	/* Aligned so it can be passed to fls */
	u8 key[4] __aligned(__alignof(u32));

	++table->seq;
	swap_endian(key, (const u8 *)ip, 32);
	return add(&table->root4, 32, key, cidr, peer, lock);
}

int wg_allowedips_insert_v6(struct allowedips *table, const struct in6_addr *ip,
			    u8 cidr, struct wg_peer *peer, struct mutex *lock)
{
	/* Aligned so it can be passed to fls64 */
	u8 key[16] __aligned(__alignof(u64));

	++table->seq;
	swap_endian(key, (const u8 *)ip, 128);
	return add(&table->root6, 128, key, cidr, peer, lock);
}

void wg_allowedips_remove_by_peer(struct allowedips *table,
				  struct wg_peer *peer, struct mutex *lock)
{
<<<<<<< HEAD
	struct allowedips_node *node, *child, **parent_bit, *parent, *tmp;
	bool free_parent;

	if (list_empty(&peer->allowedips_list))
		return;
	++table->seq;
	list_for_each_entry_safe(node, tmp, &peer->allowedips_list, peer_list) {
		list_del_init(&node->peer_list);
		RCU_INIT_POINTER(node->peer, NULL);
		if (node->bit[0] && node->bit[1])
			continue;
		child = rcu_dereference_protected(node->bit[!rcu_access_pointer(node->bit[0])],
						  lockdep_is_held(lock));
		if (child)
			child->parent_bit_packed = node->parent_bit_packed;
		parent_bit = (struct allowedips_node **)(node->parent_bit_packed & ~3UL);
		*parent_bit = child;
		parent = (void *)parent_bit -
			 offsetof(struct allowedips_node, bit[node->parent_bit_packed & 1]);
		free_parent = !rcu_access_pointer(node->bit[0]) &&
			      !rcu_access_pointer(node->bit[1]) &&
			      (node->parent_bit_packed & 3) <= 1 &&
			      !rcu_access_pointer(parent->peer);
		if (free_parent)
			child = rcu_dereference_protected(
					parent->bit[!(node->parent_bit_packed & 1)],
					lockdep_is_held(lock));
		call_rcu(&node->rcu, node_free_rcu);
		if (!free_parent)
			continue;
		if (child)
			child->parent_bit_packed = parent->parent_bit_packed;
		*(struct allowedips_node **)(parent->parent_bit_packed & ~3UL) = child;
		call_rcu(&parent->rcu, node_free_rcu);
	}
=======
	++table->seq;
	walk_remove_by_peer(&table->root4, peer, lock);
	walk_remove_by_peer(&table->root6, peer, lock);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

int wg_allowedips_read_node(struct allowedips_node *node, u8 ip[16], u8 *cidr)
{
	const unsigned int cidr_bytes = DIV_ROUND_UP(node->cidr, 8U);
	swap_endian(ip, node->bits, node->bitlen);
	memset(ip + cidr_bytes, 0, node->bitlen / 8U - cidr_bytes);
	if (node->cidr)
		ip[cidr_bytes - 1U] &= ~0U << (-node->cidr % 8U);

	*cidr = node->cidr;
	return node->bitlen == 32 ? AF_INET : AF_INET6;
}

/* Returns a strong reference to a peer */
struct wg_peer *wg_allowedips_lookup_dst(struct allowedips *table,
					 struct sk_buff *skb)
{
	if (skb->protocol == htons(ETH_P_IP))
		return lookup(table->root4, 32, &ip_hdr(skb)->daddr);
	else if (skb->protocol == htons(ETH_P_IPV6))
		return lookup(table->root6, 128, &ipv6_hdr(skb)->daddr);
	return NULL;
}

/* Returns a strong reference to a peer */
struct wg_peer *wg_allowedips_lookup_src(struct allowedips *table,
					 struct sk_buff *skb)
{
	if (skb->protocol == htons(ETH_P_IP))
		return lookup(table->root4, 32, &ip_hdr(skb)->saddr);
	else if (skb->protocol == htons(ETH_P_IPV6))
		return lookup(table->root6, 128, &ipv6_hdr(skb)->saddr);
	return NULL;
}

<<<<<<< HEAD
int __init wg_allowedips_slab_init(void)
{
	node_cache = KMEM_CACHE(allowedips_node, 0);
	return node_cache ? 0 : -ENOMEM;
}

void wg_allowedips_slab_uninit(void)
{
	rcu_barrier();
	kmem_cache_destroy(node_cache);
}

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include "selftest/allowedips.c"
