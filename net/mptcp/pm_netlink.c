// SPDX-License-Identifier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2020, Red Hat, Inc.
 */

#define pr_fmt(fmt) "MPTCP: " fmt

#include <linux/inet.h>
#include <linux/kernel.h>
#include <net/tcp.h>
#include <net/netns/generic.h>
#include <net/mptcp.h>
#include <net/genetlink.h>
#include <uapi/linux/mptcp.h>

#include "protocol.h"
#include "mib.h"

/* forward declaration */
static struct genl_family mptcp_genl_family;

static int pm_nl_pernet_id;

struct mptcp_pm_addr_entry {
	struct list_head	list;
	struct mptcp_addr_info	addr;
	struct rcu_head		rcu;
<<<<<<< HEAD
	struct socket		*lsk;
=======
<<<<<<< HEAD
	struct socket		*lsk;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

struct mptcp_pm_add_entry {
	struct list_head	list;
	struct mptcp_addr_info	addr;
	struct timer_list	add_timer;
	struct mptcp_sock	*sock;
	u8			retrans_times;
};

<<<<<<< HEAD
#define MAX_ADDR_ID		255
#define BITMAP_SZ DIV_ROUND_UP(MAX_ADDR_ID + 1, BITS_PER_LONG)

=======
<<<<<<< HEAD
#define MAX_ADDR_ID		255
#define BITMAP_SZ DIV_ROUND_UP(MAX_ADDR_ID + 1, BITS_PER_LONG)

=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
struct pm_nl_pernet {
	/* protects pernet updates */
	spinlock_t		lock;
	struct list_head	local_addr_list;
	unsigned int		addrs;
	unsigned int		add_addr_signal_max;
	unsigned int		add_addr_accept_max;
	unsigned int		local_addr_max;
	unsigned int		subflows_max;
	unsigned int		next_id;
<<<<<<< HEAD
	unsigned long		id_bitmap[BITMAP_SZ];
=======
<<<<<<< HEAD
	unsigned long		id_bitmap[BITMAP_SZ];
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

#define MPTCP_PM_ADDR_MAX	8
#define ADD_ADDR_RETRANS_MAX	3

<<<<<<< HEAD
static void mptcp_pm_nl_add_addr_send_ack(struct mptcp_sock *msk);

=======
<<<<<<< HEAD
static void mptcp_pm_nl_add_addr_send_ack(struct mptcp_sock *msk);

=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static bool addresses_equal(const struct mptcp_addr_info *a,
			    struct mptcp_addr_info *b, bool use_port)
{
	bool addr_equals = false;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (a->family == b->family) {
		if (a->family == AF_INET)
			addr_equals = a->addr.s_addr == b->addr.s_addr;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
		else
			addr_equals = !ipv6_addr_cmp(&a->addr6, &b->addr6);
	} else if (a->family == AF_INET) {
		if (ipv6_addr_v4mapped(&b->addr6))
			addr_equals = a->addr.s_addr == b->addr6.s6_addr32[3];
	} else if (b->family == AF_INET) {
		if (ipv6_addr_v4mapped(&a->addr6))
			addr_equals = a->addr6.s6_addr32[3] == b->addr.s_addr;
#endif
	}
<<<<<<< HEAD
=======
=======
	if (a->family != b->family)
		return false;

	if (a->family == AF_INET)
		addr_equals = a->addr.s_addr == b->addr.s_addr;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	else
		addr_equals = !ipv6_addr_cmp(&a->addr6, &b->addr6);
#endif
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (!addr_equals)
		return false;
	if (!use_port)
		return true;

	return a->port == b->port;
}

static bool address_zero(const struct mptcp_addr_info *addr)
{
	struct mptcp_addr_info zero;

	memset(&zero, 0, sizeof(zero));
	zero.family = addr->family;

<<<<<<< HEAD
	return addresses_equal(addr, &zero, true);
=======
<<<<<<< HEAD
	return addresses_equal(addr, &zero, true);
=======
	return addresses_equal(addr, &zero, false);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static void local_address(const struct sock_common *skc,
			  struct mptcp_addr_info *addr)
{
<<<<<<< HEAD
	addr->family = skc->skc_family;
	addr->port = htons(skc->skc_num);
=======
<<<<<<< HEAD
	addr->family = skc->skc_family;
	addr->port = htons(skc->skc_num);
=======
	addr->port = 0;
	addr->family = skc->skc_family;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (addr->family == AF_INET)
		addr->addr.s_addr = skc->skc_rcv_saddr;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	else if (addr->family == AF_INET6)
		addr->addr6 = skc->skc_v6_rcv_saddr;
#endif
}

static void remote_address(const struct sock_common *skc,
			   struct mptcp_addr_info *addr)
{
	addr->family = skc->skc_family;
	addr->port = skc->skc_dport;
	if (addr->family == AF_INET)
		addr->addr.s_addr = skc->skc_daddr;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	else if (addr->family == AF_INET6)
		addr->addr6 = skc->skc_v6_daddr;
#endif
}

static bool lookup_subflow_by_saddr(const struct list_head *list,
				    struct mptcp_addr_info *saddr)
{
	struct mptcp_subflow_context *subflow;
	struct mptcp_addr_info cur;
	struct sock_common *skc;

	list_for_each_entry(subflow, list, node) {
		skc = (struct sock_common *)mptcp_subflow_tcp_sock(subflow);

		local_address(skc, &cur);
<<<<<<< HEAD
		if (addresses_equal(&cur, saddr, saddr->port))
=======
<<<<<<< HEAD
		if (addresses_equal(&cur, saddr, saddr->port))
=======
		if (addresses_equal(&cur, saddr, false))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			return true;
	}

	return false;
}

static struct mptcp_pm_addr_entry *
select_local_address(const struct pm_nl_pernet *pernet,
		     struct mptcp_sock *msk)
{
	struct mptcp_pm_addr_entry *entry, *ret = NULL;
<<<<<<< HEAD
	struct sock *sk = (struct sock *)msk;
=======
<<<<<<< HEAD
	struct sock *sk = (struct sock *)msk;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	msk_owned_by_me(msk);

	rcu_read_lock();
	__mptcp_flush_join_list(msk);
	list_for_each_entry_rcu(entry, &pernet->local_addr_list, list) {
		if (!(entry->addr.flags & MPTCP_PM_ADDR_FLAG_SUBFLOW))
			continue;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		if (entry->addr.family != sk->sk_family) {
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
			if ((entry->addr.family == AF_INET &&
			     !ipv6_addr_v4mapped(&sk->sk_v6_daddr)) ||
			    (sk->sk_family == AF_INET &&
			     !ipv6_addr_v4mapped(&entry->addr.addr6)))
#endif
				continue;
		}

		/* avoid any address already in use by subflows and
		 * pending join
		 */
		if (!lookup_subflow_by_saddr(&msk->conn_list, &entry->addr)) {
<<<<<<< HEAD
=======
=======
		/* avoid any address already in use by subflows and
		 * pending join
		 */
		if (entry->addr.family == ((struct sock *)msk)->sk_family &&
		    !lookup_subflow_by_saddr(&msk->conn_list, &entry->addr)) {
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			ret = entry;
			break;
		}
	}
	rcu_read_unlock();
	return ret;
}

static struct mptcp_pm_addr_entry *
select_signal_address(struct pm_nl_pernet *pernet, unsigned int pos)
{
	struct mptcp_pm_addr_entry *entry, *ret = NULL;
	int i = 0;

	rcu_read_lock();
	/* do not keep any additional per socket state, just signal
	 * the address list in order.
	 * Note: removal from the local address list during the msk life-cycle
	 * can lead to additional addresses not being announced.
	 */
	list_for_each_entry_rcu(entry, &pernet->local_addr_list, list) {
		if (!(entry->addr.flags & MPTCP_PM_ADDR_FLAG_SIGNAL))
			continue;
		if (i++ == pos) {
			ret = entry;
			break;
		}
	}
	rcu_read_unlock();
	return ret;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
unsigned int mptcp_pm_get_add_addr_signal_max(struct mptcp_sock *msk)
{
	struct pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((struct sock *)msk), pm_nl_pernet_id);
	return READ_ONCE(pernet->add_addr_signal_max);
}
EXPORT_SYMBOL_GPL(mptcp_pm_get_add_addr_signal_max);

unsigned int mptcp_pm_get_add_addr_accept_max(struct mptcp_sock *msk)
{
	struct pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((struct sock *)msk), pm_nl_pernet_id);
	return READ_ONCE(pernet->add_addr_accept_max);
}
EXPORT_SYMBOL_GPL(mptcp_pm_get_add_addr_accept_max);

unsigned int mptcp_pm_get_subflows_max(struct mptcp_sock *msk)
{
	struct pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((struct sock *)msk), pm_nl_pernet_id);
	return READ_ONCE(pernet->subflows_max);
}
EXPORT_SYMBOL_GPL(mptcp_pm_get_subflows_max);

unsigned int mptcp_pm_get_local_addr_max(struct mptcp_sock *msk)
{
	struct pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((struct sock *)msk), pm_nl_pernet_id);
	return READ_ONCE(pernet->local_addr_max);
}
EXPORT_SYMBOL_GPL(mptcp_pm_get_local_addr_max);

static void check_work_pending(struct mptcp_sock *msk)
{
	if (msk->pm.add_addr_signaled == mptcp_pm_get_add_addr_signal_max(msk) &&
	    (msk->pm.local_addr_used == mptcp_pm_get_local_addr_max(msk) ||
	     msk->pm.subflows == mptcp_pm_get_subflows_max(msk)))
<<<<<<< HEAD
=======
=======
static void check_work_pending(struct mptcp_sock *msk)
{
	if (msk->pm.add_addr_signaled == msk->pm.add_addr_signal_max &&
	    (msk->pm.local_addr_used == msk->pm.local_addr_max ||
	     msk->pm.subflows == msk->pm.subflows_max))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		WRITE_ONCE(msk->pm.work_pending, false);
}

static struct mptcp_pm_add_entry *
lookup_anno_list_by_saddr(struct mptcp_sock *msk,
			  struct mptcp_addr_info *addr)
{
	struct mptcp_pm_add_entry *entry;

	lockdep_assert_held(&msk->pm.lock);

	list_for_each_entry(entry, &msk->pm.anno_list, list) {
<<<<<<< HEAD
		if (addresses_equal(&entry->addr, addr, true))
=======
<<<<<<< HEAD
		if (addresses_equal(&entry->addr, addr, true))
=======
		if (addresses_equal(&entry->addr, addr, false))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			return entry;
	}

	return NULL;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
bool mptcp_pm_sport_in_anno_list(struct mptcp_sock *msk, const struct sock *sk)
{
	struct mptcp_pm_add_entry *entry;
	struct mptcp_addr_info saddr;
	bool ret = false;

	local_address((struct sock_common *)sk, &saddr);

	spin_lock_bh(&msk->pm.lock);
	list_for_each_entry(entry, &msk->pm.anno_list, list) {
		if (addresses_equal(&entry->addr, &saddr, true)) {
			ret = true;
			goto out;
		}
	}

out:
	spin_unlock_bh(&msk->pm.lock);
	return ret;
}

<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static void mptcp_pm_add_timer(struct timer_list *timer)
{
	struct mptcp_pm_add_entry *entry = from_timer(entry, timer, add_timer);
	struct mptcp_sock *msk = entry->sock;
	struct sock *sk = (struct sock *)msk;

	pr_debug("msk=%p", msk);

	if (!msk)
		return;

	if (inet_sk_state_load(sk) == TCP_CLOSE)
		return;

	if (!entry->addr.id)
		return;

	if (mptcp_pm_should_add_signal(msk)) {
		sk_reset_timer(sk, timer, jiffies + TCP_RTO_MAX / 8);
		goto out;
	}

	spin_lock_bh(&msk->pm.lock);

	if (!mptcp_pm_should_add_signal(msk)) {
		pr_debug("retransmit ADD_ADDR id=%d", entry->addr.id);
		mptcp_pm_announce_addr(msk, &entry->addr, false, entry->addr.port);
		mptcp_pm_add_addr_send_ack(msk);
		entry->retrans_times++;
	}

	if (entry->retrans_times < ADD_ADDR_RETRANS_MAX)
		sk_reset_timer(sk, timer,
			       jiffies + mptcp_get_add_addr_timeout(sock_net(sk)));

	spin_unlock_bh(&msk->pm.lock);

out:
	__sock_put(sk);
}

struct mptcp_pm_add_entry *
mptcp_pm_del_add_timer(struct mptcp_sock *msk,
		       struct mptcp_addr_info *addr)
{
	struct mptcp_pm_add_entry *entry;
	struct sock *sk = (struct sock *)msk;

	spin_lock_bh(&msk->pm.lock);
	entry = lookup_anno_list_by_saddr(msk, addr);
	if (entry)
		entry->retrans_times = ADD_ADDR_RETRANS_MAX;
	spin_unlock_bh(&msk->pm.lock);

	if (entry)
		sk_stop_timer_sync(sk, &entry->add_timer);

	return entry;
}

static bool mptcp_pm_alloc_anno_list(struct mptcp_sock *msk,
				     struct mptcp_pm_addr_entry *entry)
{
	struct mptcp_pm_add_entry *add_entry = NULL;
	struct sock *sk = (struct sock *)msk;
	struct net *net = sock_net(sk);

	lockdep_assert_held(&msk->pm.lock);

	if (lookup_anno_list_by_saddr(msk, &entry->addr))
		return false;

	add_entry = kmalloc(sizeof(*add_entry), GFP_ATOMIC);
	if (!add_entry)
		return false;

	list_add(&add_entry->list, &msk->pm.anno_list);

	add_entry->addr = entry->addr;
	add_entry->sock = msk;
	add_entry->retrans_times = 0;

	timer_setup(&add_entry->add_timer, mptcp_pm_add_timer, 0);
	sk_reset_timer(sk, &add_entry->add_timer,
		       jiffies + mptcp_get_add_addr_timeout(net));

	return true;
}

void mptcp_pm_free_anno_list(struct mptcp_sock *msk)
{
	struct mptcp_pm_add_entry *entry, *tmp;
	struct sock *sk = (struct sock *)msk;
	LIST_HEAD(free_list);

	pr_debug("msk=%p", msk);

	spin_lock_bh(&msk->pm.lock);
	list_splice_init(&msk->pm.anno_list, &free_list);
	spin_unlock_bh(&msk->pm.lock);

	list_for_each_entry_safe(entry, tmp, &free_list, list) {
		sk_stop_timer_sync(sk, &entry->add_timer);
		kfree(entry);
	}
}

static void mptcp_pm_create_subflow_or_signal_addr(struct mptcp_sock *msk)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct sock *sk = (struct sock *)msk;
	struct mptcp_pm_addr_entry *local;
	unsigned int add_addr_signal_max;
	unsigned int local_addr_max;
	struct pm_nl_pernet *pernet;
	unsigned int subflows_max;

	pernet = net_generic(sock_net(sk), pm_nl_pernet_id);

	add_addr_signal_max = mptcp_pm_get_add_addr_signal_max(msk);
	local_addr_max = mptcp_pm_get_local_addr_max(msk);
	subflows_max = mptcp_pm_get_subflows_max(msk);

	pr_debug("local %d:%d signal %d:%d subflows %d:%d\n",
		 msk->pm.local_addr_used, local_addr_max,
		 msk->pm.add_addr_signaled, add_addr_signal_max,
		 msk->pm.subflows, subflows_max);

	/* check first for announce */
	if (msk->pm.add_addr_signaled < add_addr_signal_max) {
<<<<<<< HEAD
=======
=======
	struct mptcp_addr_info remote = { 0 };
	struct sock *sk = (struct sock *)msk;
	struct mptcp_pm_addr_entry *local;
	struct pm_nl_pernet *pernet;

	pernet = net_generic(sock_net(sk), pm_nl_pernet_id);

	pr_debug("local %d:%d signal %d:%d subflows %d:%d\n",
		 msk->pm.local_addr_used, msk->pm.local_addr_max,
		 msk->pm.add_addr_signaled, msk->pm.add_addr_signal_max,
		 msk->pm.subflows, msk->pm.subflows_max);

	/* check first for announce */
	if (msk->pm.add_addr_signaled < msk->pm.add_addr_signal_max) {
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		local = select_signal_address(pernet,
					      msk->pm.add_addr_signaled);

		if (local) {
			if (mptcp_pm_alloc_anno_list(msk, local)) {
				msk->pm.add_addr_signaled++;
				mptcp_pm_announce_addr(msk, &local->addr, false, local->addr.port);
				mptcp_pm_nl_add_addr_send_ack(msk);
			}
		} else {
			/* pick failed, avoid fourther attempts later */
<<<<<<< HEAD
			msk->pm.local_addr_used = add_addr_signal_max;
=======
<<<<<<< HEAD
			msk->pm.local_addr_used = add_addr_signal_max;
=======
			msk->pm.local_addr_used = msk->pm.add_addr_signal_max;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		}

		check_work_pending(msk);
	}

	/* check if should create a new subflow */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (msk->pm.local_addr_used < local_addr_max &&
	    msk->pm.subflows < subflows_max) {
		local = select_local_address(pernet, msk);
		if (local) {
			struct mptcp_addr_info remote = { 0 };

			msk->pm.local_addr_used++;
			msk->pm.subflows++;
			check_work_pending(msk);
			remote_address((struct sock_common *)sk, &remote);
<<<<<<< HEAD
=======
=======
	if (msk->pm.local_addr_used < msk->pm.local_addr_max &&
	    msk->pm.subflows < msk->pm.subflows_max) {
		remote_address((struct sock_common *)sk, &remote);

		local = select_local_address(pernet, msk);
		if (local) {
			msk->pm.local_addr_used++;
			msk->pm.subflows++;
			check_work_pending(msk);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			spin_unlock_bh(&msk->pm.lock);
			__mptcp_subflow_connect(sk, &local->addr, &remote);
			spin_lock_bh(&msk->pm.lock);
			return;
		}

		/* lookup failed, avoid fourther attempts later */
<<<<<<< HEAD
		msk->pm.local_addr_used = local_addr_max;
=======
<<<<<<< HEAD
		msk->pm.local_addr_used = local_addr_max;
=======
		msk->pm.local_addr_used = msk->pm.local_addr_max;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		check_work_pending(msk);
	}
}

<<<<<<< HEAD
static void mptcp_pm_nl_fully_established(struct mptcp_sock *msk)
=======
<<<<<<< HEAD
static void mptcp_pm_nl_fully_established(struct mptcp_sock *msk)
=======
void mptcp_pm_nl_fully_established(struct mptcp_sock *msk)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	mptcp_pm_create_subflow_or_signal_addr(msk);
}

<<<<<<< HEAD
static void mptcp_pm_nl_subflow_established(struct mptcp_sock *msk)
=======
<<<<<<< HEAD
static void mptcp_pm_nl_subflow_established(struct mptcp_sock *msk)
=======
void mptcp_pm_nl_subflow_established(struct mptcp_sock *msk)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	mptcp_pm_create_subflow_or_signal_addr(msk);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static void mptcp_pm_nl_add_addr_received(struct mptcp_sock *msk)
{
	struct sock *sk = (struct sock *)msk;
	unsigned int add_addr_accept_max;
	struct mptcp_addr_info remote;
	struct mptcp_addr_info local;
	unsigned int subflows_max;
	bool use_port = false;

	add_addr_accept_max = mptcp_pm_get_add_addr_accept_max(msk);
	subflows_max = mptcp_pm_get_subflows_max(msk);

	pr_debug("accepted %d:%d remote family %d",
		 msk->pm.add_addr_accepted, add_addr_accept_max,
		 msk->pm.remote.family);
	msk->pm.add_addr_accepted++;
	msk->pm.subflows++;
	if (msk->pm.add_addr_accepted >= add_addr_accept_max ||
	    msk->pm.subflows >= subflows_max)
<<<<<<< HEAD
=======
=======
void mptcp_pm_nl_add_addr_received(struct mptcp_sock *msk)
{
	struct sock *sk = (struct sock *)msk;
	struct mptcp_addr_info remote;
	struct mptcp_addr_info local;
	bool use_port = false;

	pr_debug("accepted %d:%d remote family %d",
		 msk->pm.add_addr_accepted, msk->pm.add_addr_accept_max,
		 msk->pm.remote.family);
	msk->pm.add_addr_accepted++;
	msk->pm.subflows++;
	if (msk->pm.add_addr_accepted >= msk->pm.add_addr_accept_max ||
	    msk->pm.subflows >= msk->pm.subflows_max)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		WRITE_ONCE(msk->pm.accept_addr, false);

	/* connect to the specified remote address, using whatever
	 * local address the routing configuration will pick.
	 */
	remote = msk->pm.remote;
	if (!remote.port)
		remote.port = sk->sk_dport;
	else
		use_port = true;
	memset(&local, 0, sizeof(local));
	local.family = remote.family;

	spin_unlock_bh(&msk->pm.lock);
	__mptcp_subflow_connect(sk, &local, &remote);
	spin_lock_bh(&msk->pm.lock);

	mptcp_pm_announce_addr(msk, &remote, true, use_port);
	mptcp_pm_nl_add_addr_send_ack(msk);
}

<<<<<<< HEAD
static void mptcp_pm_nl_add_addr_send_ack(struct mptcp_sock *msk)
=======
<<<<<<< HEAD
static void mptcp_pm_nl_add_addr_send_ack(struct mptcp_sock *msk)
=======
void mptcp_pm_nl_add_addr_send_ack(struct mptcp_sock *msk)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	struct mptcp_subflow_context *subflow;

	msk_owned_by_me(msk);
	lockdep_assert_held(&msk->pm.lock);

	if (!mptcp_pm_should_add_signal(msk))
		return;

	__mptcp_flush_join_list(msk);
	subflow = list_first_entry_or_null(&msk->conn_list, typeof(*subflow), node);
	if (subflow) {
		struct sock *ssk = mptcp_subflow_tcp_sock(subflow);
		u8 add_addr;

		spin_unlock_bh(&msk->pm.lock);
		pr_debug("send ack for add_addr%s%s",
			 mptcp_pm_should_add_signal_ipv6(msk) ? " [ipv6]" : "",
			 mptcp_pm_should_add_signal_port(msk) ? " [port]" : "");

		lock_sock(ssk);
		tcp_send_ack(ssk);
		release_sock(ssk);
		spin_lock_bh(&msk->pm.lock);

		add_addr = READ_ONCE(msk->pm.addr_signal);
		if (mptcp_pm_should_add_signal_ipv6(msk))
			add_addr &= ~BIT(MPTCP_ADD_ADDR_IPV6);
		if (mptcp_pm_should_add_signal_port(msk))
			add_addr &= ~BIT(MPTCP_ADD_ADDR_PORT);
		WRITE_ONCE(msk->pm.addr_signal, add_addr);
	}
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
int mptcp_pm_nl_mp_prio_send_ack(struct mptcp_sock *msk,
				 struct mptcp_addr_info *addr,
				 u8 bkup)
{
	struct mptcp_subflow_context *subflow;

	pr_debug("bkup=%d", bkup);

	mptcp_for_each_subflow(msk, subflow) {
		struct sock *ssk = mptcp_subflow_tcp_sock(subflow);
		struct sock *sk = (struct sock *)msk;
		struct mptcp_addr_info local;

		local_address((struct sock_common *)ssk, &local);
		if (!addresses_equal(&local, addr, addr->port))
			continue;

		subflow->backup = bkup;
		subflow->send_mp_prio = 1;
		subflow->request_bkup = bkup;
		__MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPPRIOTX);

		spin_unlock_bh(&msk->pm.lock);
		pr_debug("send ack for mp_prio");
		lock_sock(ssk);
		tcp_send_ack(ssk);
		release_sock(ssk);
		spin_lock_bh(&msk->pm.lock);

		return 0;
	}

	return -EINVAL;
}

static void mptcp_pm_nl_rm_addr_received(struct mptcp_sock *msk)
<<<<<<< HEAD
=======
=======
void mptcp_pm_nl_rm_addr_received(struct mptcp_sock *msk)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	struct mptcp_subflow_context *subflow, *tmp;
	struct sock *sk = (struct sock *)msk;

	pr_debug("address rm_id %d", msk->pm.rm_id);

	msk_owned_by_me(msk);

	if (!msk->pm.rm_id)
		return;

	if (list_empty(&msk->conn_list))
		return;

	list_for_each_entry_safe(subflow, tmp, &msk->conn_list, node) {
		struct sock *ssk = mptcp_subflow_tcp_sock(subflow);
		int how = RCV_SHUTDOWN | SEND_SHUTDOWN;

		if (msk->pm.rm_id != subflow->remote_id)
			continue;

		spin_unlock_bh(&msk->pm.lock);
		mptcp_subflow_shutdown(sk, ssk, how);
<<<<<<< HEAD
		mptcp_close_ssk(sk, ssk, subflow);
=======
<<<<<<< HEAD
		mptcp_close_ssk(sk, ssk, subflow);
=======
		__mptcp_close_ssk(sk, ssk, subflow);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		spin_lock_bh(&msk->pm.lock);

		msk->pm.add_addr_accepted--;
		msk->pm.subflows--;
		WRITE_ONCE(msk->pm.accept_addr, true);

		__MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_RMADDR);

		break;
	}
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
void mptcp_pm_nl_work(struct mptcp_sock *msk)
{
	struct mptcp_pm_data *pm = &msk->pm;

	msk_owned_by_me(msk);

	spin_lock_bh(&msk->pm.lock);

	pr_debug("msk=%p status=%x", msk, pm->status);
	if (pm->status & BIT(MPTCP_PM_ADD_ADDR_RECEIVED)) {
		pm->status &= ~BIT(MPTCP_PM_ADD_ADDR_RECEIVED);
		mptcp_pm_nl_add_addr_received(msk);
	}
	if (pm->status & BIT(MPTCP_PM_ADD_ADDR_SEND_ACK)) {
		pm->status &= ~BIT(MPTCP_PM_ADD_ADDR_SEND_ACK);
		mptcp_pm_nl_add_addr_send_ack(msk);
	}
	if (pm->status & BIT(MPTCP_PM_RM_ADDR_RECEIVED)) {
		pm->status &= ~BIT(MPTCP_PM_RM_ADDR_RECEIVED);
		mptcp_pm_nl_rm_addr_received(msk);
	}
	if (pm->status & BIT(MPTCP_PM_ESTABLISHED)) {
		pm->status &= ~BIT(MPTCP_PM_ESTABLISHED);
		mptcp_pm_nl_fully_established(msk);
	}
	if (pm->status & BIT(MPTCP_PM_SUBFLOW_ESTABLISHED)) {
		pm->status &= ~BIT(MPTCP_PM_SUBFLOW_ESTABLISHED);
		mptcp_pm_nl_subflow_established(msk);
	}

	spin_unlock_bh(&msk->pm.lock);
}

<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
void mptcp_pm_nl_rm_subflow_received(struct mptcp_sock *msk, u8 rm_id)
{
	struct mptcp_subflow_context *subflow, *tmp;
	struct sock *sk = (struct sock *)msk;

	pr_debug("subflow rm_id %d", rm_id);

	msk_owned_by_me(msk);

	if (!rm_id)
		return;

	if (list_empty(&msk->conn_list))
		return;

	list_for_each_entry_safe(subflow, tmp, &msk->conn_list, node) {
		struct sock *ssk = mptcp_subflow_tcp_sock(subflow);
		int how = RCV_SHUTDOWN | SEND_SHUTDOWN;

		if (rm_id != subflow->local_id)
			continue;

		spin_unlock_bh(&msk->pm.lock);
		mptcp_subflow_shutdown(sk, ssk, how);
<<<<<<< HEAD
		mptcp_close_ssk(sk, ssk, subflow);
=======
<<<<<<< HEAD
		mptcp_close_ssk(sk, ssk, subflow);
=======
		__mptcp_close_ssk(sk, ssk, subflow);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		spin_lock_bh(&msk->pm.lock);

		msk->pm.local_addr_used--;
		msk->pm.subflows--;

		__MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_RMSUBFLOW);

		break;
	}
}

static bool address_use_port(struct mptcp_pm_addr_entry *entry)
{
	return (entry->addr.flags &
		(MPTCP_PM_ADDR_FLAG_SIGNAL | MPTCP_PM_ADDR_FLAG_SUBFLOW)) ==
		MPTCP_PM_ADDR_FLAG_SIGNAL;
}

static int mptcp_pm_nl_append_new_local_addr(struct pm_nl_pernet *pernet,
					     struct mptcp_pm_addr_entry *entry)
{
	struct mptcp_pm_addr_entry *cur;
<<<<<<< HEAD
	unsigned int addr_max;
=======
<<<<<<< HEAD
	unsigned int addr_max;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	int ret = -EINVAL;

	spin_lock_bh(&pernet->lock);
	/* to keep the code simple, don't do IDR-like allocation for address ID,
	 * just bail when we exceed limits
	 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (pernet->next_id == MAX_ADDR_ID)
		pernet->next_id = 1;
	if (pernet->addrs >= MPTCP_PM_ADDR_MAX)
		goto out;
	if (test_bit(entry->addr.id, pernet->id_bitmap))
<<<<<<< HEAD
=======
=======
	if (pernet->next_id > 255)
		goto out;
	if (pernet->addrs >= MPTCP_PM_ADDR_MAX)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		goto out;

	/* do not insert duplicate address, differentiate on port only
	 * singled addresses
	 */
	list_for_each_entry(cur, &pernet->local_addr_list, list) {
		if (addresses_equal(&cur->addr, &entry->addr,
				    address_use_port(entry) &&
				    address_use_port(cur)))
			goto out;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (!entry->addr.id) {
find_next:
		entry->addr.id = find_next_zero_bit(pernet->id_bitmap,
						    MAX_ADDR_ID + 1,
						    pernet->next_id);
		if ((!entry->addr.id || entry->addr.id > MAX_ADDR_ID) &&
		    pernet->next_id != 1) {
			pernet->next_id = 1;
			goto find_next;
		}
	}

	if (!entry->addr.id || entry->addr.id > MAX_ADDR_ID)
		goto out;

	__set_bit(entry->addr.id, pernet->id_bitmap);
	if (entry->addr.id > pernet->next_id)
		pernet->next_id = entry->addr.id;

	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SIGNAL) {
		addr_max = pernet->add_addr_signal_max;
		WRITE_ONCE(pernet->add_addr_signal_max, addr_max + 1);
	}
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SUBFLOW) {
		addr_max = pernet->local_addr_max;
		WRITE_ONCE(pernet->local_addr_max, addr_max + 1);
	}

<<<<<<< HEAD
=======
=======
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SIGNAL)
		pernet->add_addr_signal_max++;
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SUBFLOW)
		pernet->local_addr_max++;

	entry->addr.id = pernet->next_id++;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	pernet->addrs++;
	list_add_tail_rcu(&entry->list, &pernet->local_addr_list);
	ret = entry->addr.id;

out:
	spin_unlock_bh(&pernet->lock);
	return ret;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int mptcp_pm_nl_create_listen_socket(struct sock *sk,
					    struct mptcp_pm_addr_entry *entry)
{
	struct sockaddr_storage addr;
	struct mptcp_sock *msk;
	struct socket *ssock;
	int backlog = 1024;
	int err;

	err = sock_create_kern(sock_net(sk), entry->addr.family,
			       SOCK_STREAM, IPPROTO_MPTCP, &entry->lsk);
	if (err)
		return err;

	msk = mptcp_sk(entry->lsk->sk);
	if (!msk) {
		err = -EINVAL;
		goto out;
	}

	ssock = __mptcp_nmpc_socket(msk);
	if (!ssock) {
		err = -EINVAL;
		goto out;
	}

	mptcp_info2sockaddr(&entry->addr, &addr, entry->addr.family);
	err = kernel_bind(ssock, (struct sockaddr *)&addr,
			  sizeof(struct sockaddr_in));
	if (err) {
		pr_warn("kernel_bind error, err=%d", err);
		goto out;
	}

	err = kernel_listen(ssock, backlog);
	if (err) {
		pr_warn("kernel_listen error, err=%d", err);
		goto out;
	}

	return 0;

out:
	sock_release(entry->lsk);
	return err;
}

<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
int mptcp_pm_nl_get_local_id(struct mptcp_sock *msk, struct sock_common *skc)
{
	struct mptcp_pm_addr_entry *entry;
	struct mptcp_addr_info skc_local;
	struct mptcp_addr_info msk_local;
	struct pm_nl_pernet *pernet;
	int ret = -1;

	if (WARN_ON_ONCE(!msk))
		return -1;

	/* The 0 ID mapping is defined by the first subflow, copied into the msk
	 * addr
	 */
	local_address((struct sock_common *)msk, &msk_local);
	local_address((struct sock_common *)skc, &skc_local);
	if (addresses_equal(&msk_local, &skc_local, false))
		return 0;

	if (address_zero(&skc_local))
		return 0;

	pernet = net_generic(sock_net((struct sock *)msk), pm_nl_pernet_id);

	rcu_read_lock();
	list_for_each_entry_rcu(entry, &pernet->local_addr_list, list) {
<<<<<<< HEAD
		if (addresses_equal(&entry->addr, &skc_local, entry->addr.port)) {
=======
<<<<<<< HEAD
		if (addresses_equal(&entry->addr, &skc_local, entry->addr.port)) {
=======
		if (addresses_equal(&entry->addr, &skc_local, false)) {
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			ret = entry->addr.id;
			break;
		}
	}
	rcu_read_unlock();
	if (ret >= 0)
		return ret;

	/* address not found, add to local list */
	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		return -ENOMEM;

	entry->addr = skc_local;
	entry->addr.ifindex = 0;
	entry->addr.flags = 0;
<<<<<<< HEAD
	entry->addr.id = 0;
	entry->addr.port = 0;
	entry->lsk = NULL;
=======
<<<<<<< HEAD
	entry->addr.id = 0;
	entry->addr.port = 0;
	entry->lsk = NULL;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	ret = mptcp_pm_nl_append_new_local_addr(pernet, entry);
	if (ret < 0)
		kfree(entry);

	return ret;
}

void mptcp_pm_nl_data_init(struct mptcp_sock *msk)
{
	struct mptcp_pm_data *pm = &msk->pm;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	bool subflows;

	subflows = !!mptcp_pm_get_subflows_max(msk);
	WRITE_ONCE(pm->work_pending, (!!mptcp_pm_get_local_addr_max(msk) && subflows) ||
		   !!mptcp_pm_get_add_addr_signal_max(msk));
	WRITE_ONCE(pm->accept_addr, !!mptcp_pm_get_add_addr_accept_max(msk) && subflows);
	WRITE_ONCE(pm->accept_subflow, subflows);
}

#define MPTCP_PM_CMD_GRP_OFFSET       0
#define MPTCP_PM_EV_GRP_OFFSET        1

static const struct genl_multicast_group mptcp_pm_mcgrps[] = {
	[MPTCP_PM_CMD_GRP_OFFSET]	= { .name = MPTCP_PM_CMD_GRP_NAME, },
	[MPTCP_PM_EV_GRP_OFFSET]        = { .name = MPTCP_PM_EV_GRP_NAME,
					    .flags = GENL_UNS_ADMIN_PERM,
					  },
<<<<<<< HEAD
=======
=======
	struct pm_nl_pernet *pernet;
	bool subflows;

	pernet = net_generic(sock_net((struct sock *)msk), pm_nl_pernet_id);

	pm->add_addr_signal_max = READ_ONCE(pernet->add_addr_signal_max);
	pm->add_addr_accept_max = READ_ONCE(pernet->add_addr_accept_max);
	pm->local_addr_max = READ_ONCE(pernet->local_addr_max);
	pm->subflows_max = READ_ONCE(pernet->subflows_max);
	subflows = !!pm->subflows_max;
	WRITE_ONCE(pm->work_pending, (!!pm->local_addr_max && subflows) ||
		   !!pm->add_addr_signal_max);
	WRITE_ONCE(pm->accept_addr, !!pm->add_addr_accept_max && subflows);
	WRITE_ONCE(pm->accept_subflow, subflows);
}

#define MPTCP_PM_CMD_GRP_OFFSET	0

static const struct genl_multicast_group mptcp_pm_mcgrps[] = {
	[MPTCP_PM_CMD_GRP_OFFSET]	= { .name = MPTCP_PM_CMD_GRP_NAME, },
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

static const struct nla_policy
mptcp_pm_addr_policy[MPTCP_PM_ADDR_ATTR_MAX + 1] = {
	[MPTCP_PM_ADDR_ATTR_FAMILY]	= { .type	= NLA_U16,	},
	[MPTCP_PM_ADDR_ATTR_ID]		= { .type	= NLA_U8,	},
	[MPTCP_PM_ADDR_ATTR_ADDR4]	= { .type	= NLA_U32,	},
	[MPTCP_PM_ADDR_ATTR_ADDR6]	=
		NLA_POLICY_EXACT_LEN(sizeof(struct in6_addr)),
	[MPTCP_PM_ADDR_ATTR_PORT]	= { .type	= NLA_U16	},
	[MPTCP_PM_ADDR_ATTR_FLAGS]	= { .type	= NLA_U32	},
	[MPTCP_PM_ADDR_ATTR_IF_IDX]     = { .type	= NLA_S32	},
};

static const struct nla_policy mptcp_pm_policy[MPTCP_PM_ATTR_MAX + 1] = {
	[MPTCP_PM_ATTR_ADDR]		=
					NLA_POLICY_NESTED(mptcp_pm_addr_policy),
	[MPTCP_PM_ATTR_RCV_ADD_ADDRS]	= { .type	= NLA_U32,	},
	[MPTCP_PM_ATTR_SUBFLOWS]	= { .type	= NLA_U32,	},
};

static int mptcp_pm_family_to_addr(int family)
{
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	if (family == AF_INET6)
		return MPTCP_PM_ADDR_ATTR_ADDR6;
#endif
	return MPTCP_PM_ADDR_ATTR_ADDR4;
}

static int mptcp_pm_parse_addr(struct nlattr *attr, struct genl_info *info,
			       bool require_family,
			       struct mptcp_pm_addr_entry *entry)
{
	struct nlattr *tb[MPTCP_PM_ADDR_ATTR_MAX + 1];
	int err, addr_addr;

	if (!attr) {
		GENL_SET_ERR_MSG(info, "missing address info");
		return -EINVAL;
	}

	/* no validation needed - was already done via nested policy */
	err = nla_parse_nested_deprecated(tb, MPTCP_PM_ADDR_ATTR_MAX, attr,
					  mptcp_pm_addr_policy, info->extack);
	if (err)
		return err;

	memset(entry, 0, sizeof(*entry));
	if (!tb[MPTCP_PM_ADDR_ATTR_FAMILY]) {
		if (!require_family)
			goto skip_family;

		NL_SET_ERR_MSG_ATTR(info->extack, attr,
				    "missing family");
		return -EINVAL;
	}

	entry->addr.family = nla_get_u16(tb[MPTCP_PM_ADDR_ATTR_FAMILY]);
	if (entry->addr.family != AF_INET
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	    && entry->addr.family != AF_INET6
#endif
	    ) {
		NL_SET_ERR_MSG_ATTR(info->extack, attr,
				    "unknown address family");
		return -EINVAL;
	}
	addr_addr = mptcp_pm_family_to_addr(entry->addr.family);
	if (!tb[addr_addr]) {
		NL_SET_ERR_MSG_ATTR(info->extack, attr,
				    "missing address data");
		return -EINVAL;
	}

#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	if (entry->addr.family == AF_INET6)
		entry->addr.addr6 = nla_get_in6_addr(tb[addr_addr]);
	else
#endif
		entry->addr.addr.s_addr = nla_get_in_addr(tb[addr_addr]);

skip_family:
	if (tb[MPTCP_PM_ADDR_ATTR_IF_IDX]) {
		u32 val = nla_get_s32(tb[MPTCP_PM_ADDR_ATTR_IF_IDX]);

		entry->addr.ifindex = val;
	}

	if (tb[MPTCP_PM_ADDR_ATTR_ID])
		entry->addr.id = nla_get_u8(tb[MPTCP_PM_ADDR_ATTR_ID]);

	if (tb[MPTCP_PM_ADDR_ATTR_FLAGS])
		entry->addr.flags = nla_get_u32(tb[MPTCP_PM_ADDR_ATTR_FLAGS]);

<<<<<<< HEAD
	if (tb[MPTCP_PM_ADDR_ATTR_PORT])
		entry->addr.port = htons(nla_get_u16(tb[MPTCP_PM_ADDR_ATTR_PORT]));

=======
<<<<<<< HEAD
	if (tb[MPTCP_PM_ADDR_ATTR_PORT])
		entry->addr.port = htons(nla_get_u16(tb[MPTCP_PM_ADDR_ATTR_PORT]));

=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	return 0;
}

static struct pm_nl_pernet *genl_info_pm_nl(struct genl_info *info)
{
	return net_generic(genl_info_net(info), pm_nl_pernet_id);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int mptcp_nl_add_subflow_or_signal_addr(struct net *net)
{
	struct mptcp_sock *msk;
	long s_slot = 0, s_num = 0;

	while ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != NULL) {
		struct sock *sk = (struct sock *)msk;

		if (!READ_ONCE(msk->fully_established))
			goto next;

		lock_sock(sk);
		spin_lock_bh(&msk->pm.lock);
		mptcp_pm_create_subflow_or_signal_addr(msk);
		spin_unlock_bh(&msk->pm.lock);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	}

	return 0;
}

<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int mptcp_nl_cmd_add_addr(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	struct mptcp_pm_addr_entry addr, *entry;
	int ret;

	ret = mptcp_pm_parse_addr(attr, info, true, &addr);
	if (ret < 0)
		return ret;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		GENL_SET_ERR_MSG(info, "can't allocate addr");
		return -ENOMEM;
	}

	*entry = addr;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (entry->addr.port) {
		ret = mptcp_pm_nl_create_listen_socket(skb->sk, entry);
		if (ret) {
			GENL_SET_ERR_MSG(info, "create listen socket error");
			kfree(entry);
			return ret;
		}
	}
	ret = mptcp_pm_nl_append_new_local_addr(pernet, entry);
	if (ret < 0) {
		GENL_SET_ERR_MSG(info, "too many addresses or duplicate one");
		if (entry->lsk)
			sock_release(entry->lsk);
<<<<<<< HEAD
=======
=======
	ret = mptcp_pm_nl_append_new_local_addr(pernet, entry);
	if (ret < 0) {
		GENL_SET_ERR_MSG(info, "too many addresses or duplicate one");
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		kfree(entry);
		return ret;
	}

<<<<<<< HEAD
	mptcp_nl_add_subflow_or_signal_addr(sock_net(skb->sk));

=======
<<<<<<< HEAD
	mptcp_nl_add_subflow_or_signal_addr(sock_net(skb->sk));

=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	return 0;
}

static struct mptcp_pm_addr_entry *
__lookup_addr_by_id(struct pm_nl_pernet *pernet, unsigned int id)
{
	struct mptcp_pm_addr_entry *entry;

	list_for_each_entry(entry, &pernet->local_addr_list, list) {
		if (entry->addr.id == id)
			return entry;
	}
	return NULL;
}

static bool remove_anno_list_by_saddr(struct mptcp_sock *msk,
				      struct mptcp_addr_info *addr)
{
	struct mptcp_pm_add_entry *entry;

	entry = mptcp_pm_del_add_timer(msk, addr);
	if (entry) {
		list_del(&entry->list);
		kfree(entry);
		return true;
	}

	return false;
}

static bool mptcp_pm_remove_anno_addr(struct mptcp_sock *msk,
				      struct mptcp_addr_info *addr,
				      bool force)
{
	bool ret;

	ret = remove_anno_list_by_saddr(msk, addr);
	if (ret || force) {
		spin_lock_bh(&msk->pm.lock);
		mptcp_pm_remove_addr(msk, addr->id);
		spin_unlock_bh(&msk->pm.lock);
	}
	return ret;
}

static int mptcp_nl_remove_subflow_and_signal_addr(struct net *net,
						   struct mptcp_addr_info *addr)
{
	struct mptcp_sock *msk;
	long s_slot = 0, s_num = 0;

	pr_debug("remove_id=%d", addr->id);

	while ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != NULL) {
		struct sock *sk = (struct sock *)msk;
		bool remove_subflow;

		if (list_empty(&msk->conn_list)) {
			mptcp_pm_remove_anno_addr(msk, addr, false);
			goto next;
		}

		lock_sock(sk);
		remove_subflow = lookup_subflow_by_saddr(&msk->conn_list, addr);
		mptcp_pm_remove_anno_addr(msk, addr, remove_subflow);
		if (remove_subflow)
			mptcp_pm_remove_subflow(msk, addr->id);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	}

	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
struct addr_entry_release_work {
	struct rcu_work	rwork;
	struct mptcp_pm_addr_entry *entry;
};

static void mptcp_pm_release_addr_entry(struct work_struct *work)
{
	struct addr_entry_release_work *w;
	struct mptcp_pm_addr_entry *entry;

	w = container_of(to_rcu_work(work), struct addr_entry_release_work, rwork);
	entry = w->entry;
	if (entry) {
		if (entry->lsk)
			sock_release(entry->lsk);
		kfree(entry);
	}
	kfree(w);
}

static void mptcp_pm_free_addr_entry(struct mptcp_pm_addr_entry *entry)
{
	struct addr_entry_release_work *w;

	w = kmalloc(sizeof(*w), GFP_ATOMIC);
	if (w) {
		INIT_RCU_WORK(&w->rwork, mptcp_pm_release_addr_entry);
		w->entry = entry;
		queue_rcu_work(system_wq, &w->rwork);
	}
}

<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int mptcp_nl_cmd_del_addr(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	struct mptcp_pm_addr_entry addr, *entry;
<<<<<<< HEAD
	unsigned int addr_max;
=======
<<<<<<< HEAD
	unsigned int addr_max;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	int ret;

	ret = mptcp_pm_parse_addr(attr, info, false, &addr);
	if (ret < 0)
		return ret;

	spin_lock_bh(&pernet->lock);
	entry = __lookup_addr_by_id(pernet, addr.addr.id);
	if (!entry) {
		GENL_SET_ERR_MSG(info, "address not found");
		spin_unlock_bh(&pernet->lock);
		return -EINVAL;
	}
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SIGNAL) {
		addr_max = pernet->add_addr_signal_max;
		WRITE_ONCE(pernet->add_addr_signal_max, addr_max - 1);
	}
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SUBFLOW) {
		addr_max = pernet->local_addr_max;
		WRITE_ONCE(pernet->local_addr_max, addr_max - 1);
	}

	pernet->addrs--;
	list_del_rcu(&entry->list);
	__clear_bit(entry->addr.id, pernet->id_bitmap);
	spin_unlock_bh(&pernet->lock);

	mptcp_nl_remove_subflow_and_signal_addr(sock_net(skb->sk), &entry->addr);
	mptcp_pm_free_addr_entry(entry);
<<<<<<< HEAD
=======
=======
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SIGNAL)
		pernet->add_addr_signal_max--;
	if (entry->addr.flags & MPTCP_PM_ADDR_FLAG_SUBFLOW)
		pernet->local_addr_max--;

	pernet->addrs--;
	list_del_rcu(&entry->list);
	spin_unlock_bh(&pernet->lock);

	mptcp_nl_remove_subflow_and_signal_addr(sock_net(skb->sk), &entry->addr);
	kfree_rcu(entry, rcu);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return ret;
}

static void __flush_addrs(struct net *net, struct list_head *list)
{
	while (!list_empty(list)) {
		struct mptcp_pm_addr_entry *cur;

		cur = list_entry(list->next,
				 struct mptcp_pm_addr_entry, list);
		mptcp_nl_remove_subflow_and_signal_addr(net, &cur->addr);
		list_del_rcu(&cur->list);
<<<<<<< HEAD
		mptcp_pm_free_addr_entry(cur);
=======
<<<<<<< HEAD
		mptcp_pm_free_addr_entry(cur);
=======
		kfree_rcu(cur, rcu);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}
}

static void __reset_counters(struct pm_nl_pernet *pernet)
{
<<<<<<< HEAD
	WRITE_ONCE(pernet->add_addr_signal_max, 0);
	WRITE_ONCE(pernet->add_addr_accept_max, 0);
	WRITE_ONCE(pernet->local_addr_max, 0);
=======
<<<<<<< HEAD
	WRITE_ONCE(pernet->add_addr_signal_max, 0);
	WRITE_ONCE(pernet->add_addr_accept_max, 0);
	WRITE_ONCE(pernet->local_addr_max, 0);
=======
	pernet->add_addr_signal_max = 0;
	pernet->add_addr_accept_max = 0;
	pernet->local_addr_max = 0;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	pernet->addrs = 0;
}

static int mptcp_nl_cmd_flush_addrs(struct sk_buff *skb, struct genl_info *info)
{
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	LIST_HEAD(free_list);

	spin_lock_bh(&pernet->lock);
	list_splice_init(&pernet->local_addr_list, &free_list);
	__reset_counters(pernet);
<<<<<<< HEAD
	pernet->next_id = 1;
	bitmap_zero(pernet->id_bitmap, MAX_ADDR_ID + 1);
=======
<<<<<<< HEAD
	pernet->next_id = 1;
	bitmap_zero(pernet->id_bitmap, MAX_ADDR_ID + 1);
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	spin_unlock_bh(&pernet->lock);
	__flush_addrs(sock_net(skb->sk), &free_list);
	return 0;
}

static int mptcp_nl_fill_addr(struct sk_buff *skb,
			      struct mptcp_pm_addr_entry *entry)
{
	struct mptcp_addr_info *addr = &entry->addr;
	struct nlattr *attr;

	attr = nla_nest_start(skb, MPTCP_PM_ATTR_ADDR);
	if (!attr)
		return -EMSGSIZE;

	if (nla_put_u16(skb, MPTCP_PM_ADDR_ATTR_FAMILY, addr->family))
		goto nla_put_failure;
<<<<<<< HEAD
	if (nla_put_u16(skb, MPTCP_PM_ADDR_ATTR_PORT, ntohs(addr->port)))
		goto nla_put_failure;
=======
<<<<<<< HEAD
	if (nla_put_u16(skb, MPTCP_PM_ADDR_ATTR_PORT, ntohs(addr->port)))
		goto nla_put_failure;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (nla_put_u8(skb, MPTCP_PM_ADDR_ATTR_ID, addr->id))
		goto nla_put_failure;
	if (nla_put_u32(skb, MPTCP_PM_ADDR_ATTR_FLAGS, entry->addr.flags))
		goto nla_put_failure;
	if (entry->addr.ifindex &&
	    nla_put_s32(skb, MPTCP_PM_ADDR_ATTR_IF_IDX, entry->addr.ifindex))
		goto nla_put_failure;

	if (addr->family == AF_INET &&
	    nla_put_in_addr(skb, MPTCP_PM_ADDR_ATTR_ADDR4,
			    addr->addr.s_addr))
		goto nla_put_failure;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	else if (addr->family == AF_INET6 &&
		 nla_put_in6_addr(skb, MPTCP_PM_ADDR_ATTR_ADDR6, &addr->addr6))
		goto nla_put_failure;
#endif
	nla_nest_end(skb, attr);
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, attr);
	return -EMSGSIZE;
}

static int mptcp_nl_cmd_get_addr(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	struct mptcp_pm_addr_entry addr, *entry;
	struct sk_buff *msg;
	void *reply;
	int ret;

	ret = mptcp_pm_parse_addr(attr, info, false, &addr);
	if (ret < 0)
		return ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	reply = genlmsg_put_reply(msg, info, &mptcp_genl_family, 0,
				  info->genlhdr->cmd);
	if (!reply) {
		GENL_SET_ERR_MSG(info, "not enough space in Netlink message");
		ret = -EMSGSIZE;
		goto fail;
	}

	spin_lock_bh(&pernet->lock);
	entry = __lookup_addr_by_id(pernet, addr.addr.id);
	if (!entry) {
		GENL_SET_ERR_MSG(info, "address not found");
		ret = -EINVAL;
		goto unlock_fail;
	}

	ret = mptcp_nl_fill_addr(msg, entry);
	if (ret)
		goto unlock_fail;

	genlmsg_end(msg, reply);
	ret = genlmsg_reply(msg, info);
	spin_unlock_bh(&pernet->lock);
	return ret;

unlock_fail:
	spin_unlock_bh(&pernet->lock);

fail:
	nlmsg_free(msg);
	return ret;
}

static int mptcp_nl_cmd_dump_addrs(struct sk_buff *msg,
				   struct netlink_callback *cb)
{
	struct net *net = sock_net(msg->sk);
	struct mptcp_pm_addr_entry *entry;
	struct pm_nl_pernet *pernet;
	int id = cb->args[0];
	void *hdr;
<<<<<<< HEAD
	int i;
=======
<<<<<<< HEAD
	int i;
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	pernet = net_generic(net, pm_nl_pernet_id);

	spin_lock_bh(&pernet->lock);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	for (i = id; i < MAX_ADDR_ID + 1; i++) {
		if (test_bit(i, pernet->id_bitmap)) {
			entry = __lookup_addr_by_id(pernet, i);
			if (!entry)
				break;

			if (entry->addr.id <= id)
				continue;

			hdr = genlmsg_put(msg, NETLINK_CB(cb->skb).portid,
					  cb->nlh->nlmsg_seq, &mptcp_genl_family,
					  NLM_F_MULTI, MPTCP_PM_CMD_GET_ADDR);
			if (!hdr)
				break;

			if (mptcp_nl_fill_addr(msg, entry) < 0) {
				genlmsg_cancel(msg, hdr);
				break;
			}

			id = entry->addr.id;
			genlmsg_end(msg, hdr);
		}
<<<<<<< HEAD
=======
=======
	list_for_each_entry(entry, &pernet->local_addr_list, list) {
		if (entry->addr.id <= id)
			continue;

		hdr = genlmsg_put(msg, NETLINK_CB(cb->skb).portid,
				  cb->nlh->nlmsg_seq, &mptcp_genl_family,
				  NLM_F_MULTI, MPTCP_PM_CMD_GET_ADDR);
		if (!hdr)
			break;

		if (mptcp_nl_fill_addr(msg, entry) < 0) {
			genlmsg_cancel(msg, hdr);
			break;
		}

		id = entry->addr.id;
		genlmsg_end(msg, hdr);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}
	spin_unlock_bh(&pernet->lock);

	cb->args[0] = id;
	return msg->len;
}

static int parse_limit(struct genl_info *info, int id, unsigned int *limit)
{
	struct nlattr *attr = info->attrs[id];

	if (!attr)
		return 0;

	*limit = nla_get_u32(attr);
	if (*limit > MPTCP_PM_ADDR_MAX) {
		GENL_SET_ERR_MSG(info, "limit greater than maximum");
		return -EINVAL;
	}
	return 0;
}

static int
mptcp_nl_cmd_set_limits(struct sk_buff *skb, struct genl_info *info)
{
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	unsigned int rcv_addrs, subflows;
	int ret;

	spin_lock_bh(&pernet->lock);
	rcv_addrs = pernet->add_addr_accept_max;
	ret = parse_limit(info, MPTCP_PM_ATTR_RCV_ADD_ADDRS, &rcv_addrs);
	if (ret)
		goto unlock;

	subflows = pernet->subflows_max;
	ret = parse_limit(info, MPTCP_PM_ATTR_SUBFLOWS, &subflows);
	if (ret)
		goto unlock;

	WRITE_ONCE(pernet->add_addr_accept_max, rcv_addrs);
	WRITE_ONCE(pernet->subflows_max, subflows);

unlock:
	spin_unlock_bh(&pernet->lock);
	return ret;
}

static int
mptcp_nl_cmd_get_limits(struct sk_buff *skb, struct genl_info *info)
{
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	struct sk_buff *msg;
	void *reply;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	reply = genlmsg_put_reply(msg, info, &mptcp_genl_family, 0,
				  MPTCP_PM_CMD_GET_LIMITS);
	if (!reply)
		goto fail;

	if (nla_put_u32(msg, MPTCP_PM_ATTR_RCV_ADD_ADDRS,
			READ_ONCE(pernet->add_addr_accept_max)))
		goto fail;

	if (nla_put_u32(msg, MPTCP_PM_ATTR_SUBFLOWS,
			READ_ONCE(pernet->subflows_max)))
		goto fail;

	genlmsg_end(msg, reply);
	return genlmsg_reply(msg, info);

fail:
	GENL_SET_ERR_MSG(info, "not enough space in Netlink message");
	nlmsg_free(msg);
	return -EMSGSIZE;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int mptcp_nl_addr_backup(struct net *net,
				struct mptcp_addr_info *addr,
				u8 bkup)
{
	long s_slot = 0, s_num = 0;
	struct mptcp_sock *msk;
	int ret = -EINVAL;

	while ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != NULL) {
		struct sock *sk = (struct sock *)msk;

		if (list_empty(&msk->conn_list))
			goto next;

		lock_sock(sk);
		spin_lock_bh(&msk->pm.lock);
		ret = mptcp_pm_nl_mp_prio_send_ack(msk, addr, bkup);
		spin_unlock_bh(&msk->pm.lock);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	}

	return ret;
}

static int mptcp_nl_cmd_set_flags(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	struct pm_nl_pernet *pernet = genl_info_pm_nl(info);
	struct mptcp_pm_addr_entry addr, *entry;
	struct net *net = sock_net(skb->sk);
	u8 bkup = 0;
	int ret;

	ret = mptcp_pm_parse_addr(attr, info, true, &addr);
	if (ret < 0)
		return ret;

	if (addr.addr.flags & MPTCP_PM_ADDR_FLAG_BACKUP)
		bkup = 1;

	list_for_each_entry(entry, &pernet->local_addr_list, list) {
		if (addresses_equal(&entry->addr, &addr.addr, true)) {
			ret = mptcp_nl_addr_backup(net, &entry->addr, bkup);
			if (ret)
				return ret;

			if (bkup)
				entry->addr.flags |= MPTCP_PM_ADDR_FLAG_BACKUP;
			else
				entry->addr.flags &= ~MPTCP_PM_ADDR_FLAG_BACKUP;
		}
	}

	return 0;
}

static void mptcp_nl_mcast_send(struct net *net, struct sk_buff *nlskb, gfp_t gfp)
{
	genlmsg_multicast_netns(&mptcp_genl_family, net,
				nlskb, 0, MPTCP_PM_EV_GRP_OFFSET, gfp);
}

static int mptcp_event_add_subflow(struct sk_buff *skb, const struct sock *ssk)
{
	const struct inet_sock *issk = inet_sk(ssk);
	const struct mptcp_subflow_context *sf;

	if (nla_put_u16(skb, MPTCP_ATTR_FAMILY, ssk->sk_family))
		return -EMSGSIZE;

	switch (ssk->sk_family) {
	case AF_INET:
		if (nla_put_in_addr(skb, MPTCP_ATTR_SADDR4, issk->inet_saddr))
			return -EMSGSIZE;
		if (nla_put_in_addr(skb, MPTCP_ATTR_DADDR4, issk->inet_daddr))
			return -EMSGSIZE;
		break;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	case AF_INET6: {
		const struct ipv6_pinfo *np = inet6_sk(ssk);

		if (nla_put_in6_addr(skb, MPTCP_ATTR_SADDR6, &np->saddr))
			return -EMSGSIZE;
		if (nla_put_in6_addr(skb, MPTCP_ATTR_DADDR6, &ssk->sk_v6_daddr))
			return -EMSGSIZE;
		break;
	}
#endif
	default:
		WARN_ON_ONCE(1);
		return -EMSGSIZE;
	}

	if (nla_put_be16(skb, MPTCP_ATTR_SPORT, issk->inet_sport))
		return -EMSGSIZE;
	if (nla_put_be16(skb, MPTCP_ATTR_DPORT, issk->inet_dport))
		return -EMSGSIZE;

	sf = mptcp_subflow_ctx(ssk);
	if (WARN_ON_ONCE(!sf))
		return -EINVAL;

	if (nla_put_u8(skb, MPTCP_ATTR_LOC_ID, sf->local_id))
		return -EMSGSIZE;

	if (nla_put_u8(skb, MPTCP_ATTR_REM_ID, sf->remote_id))
		return -EMSGSIZE;

	return 0;
}

static int mptcp_event_put_token_and_ssk(struct sk_buff *skb,
					 const struct mptcp_sock *msk,
					 const struct sock *ssk)
{
	const struct sock *sk = (const struct sock *)msk;
	const struct mptcp_subflow_context *sf;
	u8 sk_err;

	if (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token))
		return -EMSGSIZE;

	if (mptcp_event_add_subflow(skb, ssk))
		return -EMSGSIZE;

	sf = mptcp_subflow_ctx(ssk);
	if (WARN_ON_ONCE(!sf))
		return -EINVAL;

	if (nla_put_u8(skb, MPTCP_ATTR_BACKUP, sf->backup))
		return -EMSGSIZE;

	if (ssk->sk_bound_dev_if &&
	    nla_put_s32(skb, MPTCP_ATTR_IF_IDX, ssk->sk_bound_dev_if))
		return -EMSGSIZE;

	sk_err = ssk->sk_err;
	if (sk_err && sk->sk_state == TCP_ESTABLISHED &&
	    nla_put_u8(skb, MPTCP_ATTR_ERROR, sk_err))
		return -EMSGSIZE;

	return 0;
}

static int mptcp_event_sub_established(struct sk_buff *skb,
				       const struct mptcp_sock *msk,
				       const struct sock *ssk)
{
	return mptcp_event_put_token_and_ssk(skb, msk, ssk);
}

static int mptcp_event_sub_closed(struct sk_buff *skb,
				  const struct mptcp_sock *msk,
				  const struct sock *ssk)
{
	if (mptcp_event_put_token_and_ssk(skb, msk, ssk))
		return -EMSGSIZE;

	return 0;
}

static int mptcp_event_created(struct sk_buff *skb,
			       const struct mptcp_sock *msk,
			       const struct sock *ssk)
{
	int err = nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token);

	if (err)
		return err;

	return mptcp_event_add_subflow(skb, ssk);
}

void mptcp_event_addr_removed(const struct mptcp_sock *msk, uint8_t id)
{
	struct net *net = sock_net((const struct sock *)msk);
	struct nlmsghdr *nlh;
	struct sk_buff *skb;

	if (!genl_has_listeners(&mptcp_genl_family, net, MPTCP_PM_EV_GRP_OFFSET))
		return;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!skb)
		return;

	nlh = genlmsg_put(skb, 0, 0, &mptcp_genl_family, 0, MPTCP_EVENT_REMOVED);
	if (!nlh)
		goto nla_put_failure;

	if (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token))
		goto nla_put_failure;

	if (nla_put_u8(skb, MPTCP_ATTR_REM_ID, id))
		goto nla_put_failure;

	genlmsg_end(skb, nlh);
	mptcp_nl_mcast_send(net, skb, GFP_ATOMIC);
	return;

nla_put_failure:
	kfree_skb(skb);
}

void mptcp_event_addr_announced(const struct mptcp_sock *msk,
				const struct mptcp_addr_info *info)
{
	struct net *net = sock_net((const struct sock *)msk);
	struct nlmsghdr *nlh;
	struct sk_buff *skb;

	if (!genl_has_listeners(&mptcp_genl_family, net, MPTCP_PM_EV_GRP_OFFSET))
		return;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!skb)
		return;

	nlh = genlmsg_put(skb, 0, 0, &mptcp_genl_family, 0,
			  MPTCP_EVENT_ANNOUNCED);
	if (!nlh)
		goto nla_put_failure;

	if (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token))
		goto nla_put_failure;

	if (nla_put_u8(skb, MPTCP_ATTR_REM_ID, info->id))
		goto nla_put_failure;

	if (nla_put_be16(skb, MPTCP_ATTR_DPORT, info->port))
		goto nla_put_failure;

	switch (info->family) {
	case AF_INET:
		if (nla_put_in_addr(skb, MPTCP_ATTR_DADDR4, info->addr.s_addr))
			goto nla_put_failure;
		break;
#if IS_ENABLED(CONFIG_MPTCP_IPV6)
	case AF_INET6:
		if (nla_put_in6_addr(skb, MPTCP_ATTR_DADDR6, &info->addr6))
			goto nla_put_failure;
		break;
#endif
	default:
		WARN_ON_ONCE(1);
		goto nla_put_failure;
	}

	genlmsg_end(skb, nlh);
	mptcp_nl_mcast_send(net, skb, GFP_ATOMIC);
	return;

nla_put_failure:
	kfree_skb(skb);
}

void mptcp_event(enum mptcp_event_type type, const struct mptcp_sock *msk,
		 const struct sock *ssk, gfp_t gfp)
{
	struct net *net = sock_net((const struct sock *)msk);
	struct nlmsghdr *nlh;
	struct sk_buff *skb;

	if (!genl_has_listeners(&mptcp_genl_family, net, MPTCP_PM_EV_GRP_OFFSET))
		return;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!skb)
		return;

	nlh = genlmsg_put(skb, 0, 0, &mptcp_genl_family, 0, type);
	if (!nlh)
		goto nla_put_failure;

	switch (type) {
	case MPTCP_EVENT_UNSPEC:
		WARN_ON_ONCE(1);
		break;
	case MPTCP_EVENT_CREATED:
	case MPTCP_EVENT_ESTABLISHED:
		if (mptcp_event_created(skb, msk, ssk) < 0)
			goto nla_put_failure;
		break;
	case MPTCP_EVENT_CLOSED:
		if (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token) < 0)
			goto nla_put_failure;
		break;
	case MPTCP_EVENT_ANNOUNCED:
	case MPTCP_EVENT_REMOVED:
		/* call mptcp_event_addr_announced()/removed instead */
		WARN_ON_ONCE(1);
		break;
	case MPTCP_EVENT_SUB_ESTABLISHED:
	case MPTCP_EVENT_SUB_PRIORITY:
		if (mptcp_event_sub_established(skb, msk, ssk) < 0)
			goto nla_put_failure;
		break;
	case MPTCP_EVENT_SUB_CLOSED:
		if (mptcp_event_sub_closed(skb, msk, ssk) < 0)
			goto nla_put_failure;
		break;
	}

	genlmsg_end(skb, nlh);
	mptcp_nl_mcast_send(net, skb, gfp);
	return;

nla_put_failure:
	kfree_skb(skb);
}

<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static const struct genl_small_ops mptcp_pm_ops[] = {
	{
		.cmd    = MPTCP_PM_CMD_ADD_ADDR,
		.doit   = mptcp_nl_cmd_add_addr,
		.flags  = GENL_ADMIN_PERM,
	},
	{
		.cmd    = MPTCP_PM_CMD_DEL_ADDR,
		.doit   = mptcp_nl_cmd_del_addr,
		.flags  = GENL_ADMIN_PERM,
	},
	{
		.cmd    = MPTCP_PM_CMD_FLUSH_ADDRS,
		.doit   = mptcp_nl_cmd_flush_addrs,
		.flags  = GENL_ADMIN_PERM,
	},
	{
		.cmd    = MPTCP_PM_CMD_GET_ADDR,
		.doit   = mptcp_nl_cmd_get_addr,
		.dumpit   = mptcp_nl_cmd_dump_addrs,
	},
	{
		.cmd    = MPTCP_PM_CMD_SET_LIMITS,
		.doit   = mptcp_nl_cmd_set_limits,
		.flags  = GENL_ADMIN_PERM,
	},
	{
		.cmd    = MPTCP_PM_CMD_GET_LIMITS,
		.doit   = mptcp_nl_cmd_get_limits,
	},
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	{
		.cmd    = MPTCP_PM_CMD_SET_FLAGS,
		.doit   = mptcp_nl_cmd_set_flags,
		.flags  = GENL_ADMIN_PERM,
	},
<<<<<<< HEAD
=======
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

static struct genl_family mptcp_genl_family __ro_after_init = {
	.name		= MPTCP_PM_NAME,
	.version	= MPTCP_PM_VER,
	.maxattr	= MPTCP_PM_ATTR_MAX,
	.policy		= mptcp_pm_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= mptcp_pm_ops,
	.n_small_ops	= ARRAY_SIZE(mptcp_pm_ops),
	.mcgrps		= mptcp_pm_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(mptcp_pm_mcgrps),
};

static int __net_init pm_nl_init_net(struct net *net)
{
	struct pm_nl_pernet *pernet = net_generic(net, pm_nl_pernet_id);

	INIT_LIST_HEAD_RCU(&pernet->local_addr_list);
	__reset_counters(pernet);
	pernet->next_id = 1;
<<<<<<< HEAD
	bitmap_zero(pernet->id_bitmap, MAX_ADDR_ID + 1);
=======
<<<<<<< HEAD
	bitmap_zero(pernet->id_bitmap, MAX_ADDR_ID + 1);
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	spin_lock_init(&pernet->lock);
	return 0;
}

static void __net_exit pm_nl_exit_net(struct list_head *net_list)
{
	struct net *net;

	list_for_each_entry(net, net_list, exit_list) {
		struct pm_nl_pernet *pernet = net_generic(net, pm_nl_pernet_id);

		/* net is removed from namespace list, can't race with
		 * other modifiers
		 */
		__flush_addrs(net, &pernet->local_addr_list);
	}
}

static struct pernet_operations mptcp_pm_pernet_ops = {
	.init = pm_nl_init_net,
	.exit_batch = pm_nl_exit_net,
	.id = &pm_nl_pernet_id,
	.size = sizeof(struct pm_nl_pernet),
};

void __init mptcp_pm_nl_init(void)
{
	if (register_pernet_subsys(&mptcp_pm_pernet_ops) < 0)
		panic("Failed to register MPTCP PM pernet subsystem.\n");

	if (genl_register_family(&mptcp_genl_family))
		panic("Failed to register MPTCP PM netlink family\n");
}
