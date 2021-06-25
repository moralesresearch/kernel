// SPDX-License-Identifier: GPL-2.0
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <linux/dma-mapping.h>
#include <linux/pagemap.h>
#include <linux/sched.h>
#include <linux/dmapool.h>
#include <linux/mempool.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <net/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>
#include <linux/if_vlan.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include "qlge.h"

<<<<<<< HEAD
struct qlge_stats {
=======
struct ql_stats {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	char stat_string[ETH_GSTRING_LEN];
	int sizeof_stat;
	int stat_offset;
};

<<<<<<< HEAD
#define QL_SIZEOF(m) sizeof_field(struct qlge_adapter, m)
#define QL_OFF(m) offsetof(struct qlge_adapter, m)

static const struct qlge_stats qlge_gstrings_stats[] = {
=======
#define QL_SIZEOF(m) sizeof_field(struct ql_adapter, m)
#define QL_OFF(m) offsetof(struct ql_adapter, m)

static const struct ql_stats ql_gstrings_stats[] = {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	{"tx_pkts", QL_SIZEOF(nic_stats.tx_pkts), QL_OFF(nic_stats.tx_pkts)},
	{"tx_bytes", QL_SIZEOF(nic_stats.tx_bytes), QL_OFF(nic_stats.tx_bytes)},
	{"tx_mcast_pkts", QL_SIZEOF(nic_stats.tx_mcast_pkts),
					QL_OFF(nic_stats.tx_mcast_pkts)},
	{"tx_bcast_pkts", QL_SIZEOF(nic_stats.tx_bcast_pkts),
					QL_OFF(nic_stats.tx_bcast_pkts)},
	{"tx_ucast_pkts", QL_SIZEOF(nic_stats.tx_ucast_pkts),
					QL_OFF(nic_stats.tx_ucast_pkts)},
	{"tx_ctl_pkts", QL_SIZEOF(nic_stats.tx_ctl_pkts),
					QL_OFF(nic_stats.tx_ctl_pkts)},
	{"tx_pause_pkts", QL_SIZEOF(nic_stats.tx_pause_pkts),
					QL_OFF(nic_stats.tx_pause_pkts)},
	{"tx_64_pkts", QL_SIZEOF(nic_stats.tx_64_pkt),
					QL_OFF(nic_stats.tx_64_pkt)},
	{"tx_65_to_127_pkts", QL_SIZEOF(nic_stats.tx_65_to_127_pkt),
					QL_OFF(nic_stats.tx_65_to_127_pkt)},
	{"tx_128_to_255_pkts", QL_SIZEOF(nic_stats.tx_128_to_255_pkt),
					QL_OFF(nic_stats.tx_128_to_255_pkt)},
	{"tx_256_511_pkts", QL_SIZEOF(nic_stats.tx_256_511_pkt),
					QL_OFF(nic_stats.tx_256_511_pkt)},
	{"tx_512_to_1023_pkts",	QL_SIZEOF(nic_stats.tx_512_to_1023_pkt),
					QL_OFF(nic_stats.tx_512_to_1023_pkt)},
	{"tx_1024_to_1518_pkts", QL_SIZEOF(nic_stats.tx_1024_to_1518_pkt),
					QL_OFF(nic_stats.tx_1024_to_1518_pkt)},
	{"tx_1519_to_max_pkts",	QL_SIZEOF(nic_stats.tx_1519_to_max_pkt),
					QL_OFF(nic_stats.tx_1519_to_max_pkt)},
	{"tx_undersize_pkts", QL_SIZEOF(nic_stats.tx_undersize_pkt),
					QL_OFF(nic_stats.tx_undersize_pkt)},
	{"tx_oversize_pkts", QL_SIZEOF(nic_stats.tx_oversize_pkt),
					QL_OFF(nic_stats.tx_oversize_pkt)},
	{"rx_bytes", QL_SIZEOF(nic_stats.rx_bytes), QL_OFF(nic_stats.rx_bytes)},
	{"rx_bytes_ok",	QL_SIZEOF(nic_stats.rx_bytes_ok),
					QL_OFF(nic_stats.rx_bytes_ok)},
	{"rx_pkts", QL_SIZEOF(nic_stats.rx_pkts), QL_OFF(nic_stats.rx_pkts)},
	{"rx_pkts_ok", QL_SIZEOF(nic_stats.rx_pkts_ok),
					QL_OFF(nic_stats.rx_pkts_ok)},
	{"rx_bcast_pkts", QL_SIZEOF(nic_stats.rx_bcast_pkts),
					QL_OFF(nic_stats.rx_bcast_pkts)},
	{"rx_mcast_pkts", QL_SIZEOF(nic_stats.rx_mcast_pkts),
					QL_OFF(nic_stats.rx_mcast_pkts)},
	{"rx_ucast_pkts", QL_SIZEOF(nic_stats.rx_ucast_pkts),
					QL_OFF(nic_stats.rx_ucast_pkts)},
	{"rx_undersize_pkts", QL_SIZEOF(nic_stats.rx_undersize_pkts),
					QL_OFF(nic_stats.rx_undersize_pkts)},
	{"rx_oversize_pkts", QL_SIZEOF(nic_stats.rx_oversize_pkts),
					QL_OFF(nic_stats.rx_oversize_pkts)},
	{"rx_jabber_pkts", QL_SIZEOF(nic_stats.rx_jabber_pkts),
					QL_OFF(nic_stats.rx_jabber_pkts)},
	{"rx_undersize_fcerr_pkts",
		QL_SIZEOF(nic_stats.rx_undersize_fcerr_pkts),
				QL_OFF(nic_stats.rx_undersize_fcerr_pkts)},
	{"rx_drop_events", QL_SIZEOF(nic_stats.rx_drop_events),
					QL_OFF(nic_stats.rx_drop_events)},
	{"rx_fcerr_pkts", QL_SIZEOF(nic_stats.rx_fcerr_pkts),
					QL_OFF(nic_stats.rx_fcerr_pkts)},
	{"rx_align_err", QL_SIZEOF(nic_stats.rx_align_err),
					QL_OFF(nic_stats.rx_align_err)},
	{"rx_symbol_err", QL_SIZEOF(nic_stats.rx_symbol_err),
					QL_OFF(nic_stats.rx_symbol_err)},
	{"rx_mac_err", QL_SIZEOF(nic_stats.rx_mac_err),
					QL_OFF(nic_stats.rx_mac_err)},
	{"rx_ctl_pkts",	QL_SIZEOF(nic_stats.rx_ctl_pkts),
					QL_OFF(nic_stats.rx_ctl_pkts)},
	{"rx_pause_pkts", QL_SIZEOF(nic_stats.rx_pause_pkts),
					QL_OFF(nic_stats.rx_pause_pkts)},
	{"rx_64_pkts", QL_SIZEOF(nic_stats.rx_64_pkts),
					QL_OFF(nic_stats.rx_64_pkts)},
	{"rx_65_to_127_pkts", QL_SIZEOF(nic_stats.rx_65_to_127_pkts),
					QL_OFF(nic_stats.rx_65_to_127_pkts)},
	{"rx_128_255_pkts", QL_SIZEOF(nic_stats.rx_128_255_pkts),
					QL_OFF(nic_stats.rx_128_255_pkts)},
	{"rx_256_511_pkts", QL_SIZEOF(nic_stats.rx_256_511_pkts),
					QL_OFF(nic_stats.rx_256_511_pkts)},
	{"rx_512_to_1023_pkts",	QL_SIZEOF(nic_stats.rx_512_to_1023_pkts),
					QL_OFF(nic_stats.rx_512_to_1023_pkts)},
	{"rx_1024_to_1518_pkts", QL_SIZEOF(nic_stats.rx_1024_to_1518_pkts),
					QL_OFF(nic_stats.rx_1024_to_1518_pkts)},
	{"rx_1519_to_max_pkts",	QL_SIZEOF(nic_stats.rx_1519_to_max_pkts),
					QL_OFF(nic_stats.rx_1519_to_max_pkts)},
	{"rx_len_err_pkts", QL_SIZEOF(nic_stats.rx_len_err_pkts),
					QL_OFF(nic_stats.rx_len_err_pkts)},
	{"rx_code_err",	QL_SIZEOF(nic_stats.rx_code_err),
					QL_OFF(nic_stats.rx_code_err)},
	{"rx_oversize_err", QL_SIZEOF(nic_stats.rx_oversize_err),
					QL_OFF(nic_stats.rx_oversize_err)},
	{"rx_undersize_err", QL_SIZEOF(nic_stats.rx_undersize_err),
					QL_OFF(nic_stats.rx_undersize_err)},
	{"rx_preamble_err", QL_SIZEOF(nic_stats.rx_preamble_err),
					QL_OFF(nic_stats.rx_preamble_err)},
	{"rx_frame_len_err", QL_SIZEOF(nic_stats.rx_frame_len_err),
					QL_OFF(nic_stats.rx_frame_len_err)},
	{"rx_crc_err", QL_SIZEOF(nic_stats.rx_crc_err),
					QL_OFF(nic_stats.rx_crc_err)},
	{"rx_err_count", QL_SIZEOF(nic_stats.rx_err_count),
					QL_OFF(nic_stats.rx_err_count)},
	{"tx_cbfc_pause_frames0", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames0),
				QL_OFF(nic_stats.tx_cbfc_pause_frames0)},
	{"tx_cbfc_pause_frames1", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames1),
				QL_OFF(nic_stats.tx_cbfc_pause_frames1)},
	{"tx_cbfc_pause_frames2", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames2),
				QL_OFF(nic_stats.tx_cbfc_pause_frames2)},
	{"tx_cbfc_pause_frames3", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames3),
				QL_OFF(nic_stats.tx_cbfc_pause_frames3)},
	{"tx_cbfc_pause_frames4", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames4),
				QL_OFF(nic_stats.tx_cbfc_pause_frames4)},
	{"tx_cbfc_pause_frames5", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames5),
				QL_OFF(nic_stats.tx_cbfc_pause_frames5)},
	{"tx_cbfc_pause_frames6", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames6),
				QL_OFF(nic_stats.tx_cbfc_pause_frames6)},
	{"tx_cbfc_pause_frames7", QL_SIZEOF(nic_stats.tx_cbfc_pause_frames7),
				QL_OFF(nic_stats.tx_cbfc_pause_frames7)},
	{"rx_cbfc_pause_frames0", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames0),
				QL_OFF(nic_stats.rx_cbfc_pause_frames0)},
	{"rx_cbfc_pause_frames1", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames1),
				QL_OFF(nic_stats.rx_cbfc_pause_frames1)},
	{"rx_cbfc_pause_frames2", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames2),
				QL_OFF(nic_stats.rx_cbfc_pause_frames2)},
	{"rx_cbfc_pause_frames3", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames3),
				QL_OFF(nic_stats.rx_cbfc_pause_frames3)},
	{"rx_cbfc_pause_frames4", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames4),
				QL_OFF(nic_stats.rx_cbfc_pause_frames4)},
	{"rx_cbfc_pause_frames5", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames5),
				QL_OFF(nic_stats.rx_cbfc_pause_frames5)},
	{"rx_cbfc_pause_frames6", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames6),
				QL_OFF(nic_stats.rx_cbfc_pause_frames6)},
	{"rx_cbfc_pause_frames7", QL_SIZEOF(nic_stats.rx_cbfc_pause_frames7),
				QL_OFF(nic_stats.rx_cbfc_pause_frames7)},
	{"rx_nic_fifo_drop", QL_SIZEOF(nic_stats.rx_nic_fifo_drop),
					QL_OFF(nic_stats.rx_nic_fifo_drop)},
};

<<<<<<< HEAD
static const char qlge_gstrings_test[][ETH_GSTRING_LEN] = {
	"Loopback test  (offline)"
};

#define QLGE_TEST_LEN (sizeof(qlge_gstrings_test) / ETH_GSTRING_LEN)
#define QLGE_STATS_LEN ARRAY_SIZE(qlge_gstrings_stats)
#define QLGE_RCV_MAC_ERR_STATS	7

static int qlge_update_ring_coalescing(struct qlge_adapter *qdev)
=======
static const char ql_gstrings_test[][ETH_GSTRING_LEN] = {
	"Loopback test  (offline)"
};

#define QLGE_TEST_LEN (sizeof(ql_gstrings_test) / ETH_GSTRING_LEN)
#define QLGE_STATS_LEN ARRAY_SIZE(ql_gstrings_stats)
#define QLGE_RCV_MAC_ERR_STATS	7

static int ql_update_ring_coalescing(struct ql_adapter *qdev)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	int i, status = 0;
	struct rx_ring *rx_ring;
	struct cqicb *cqicb;

	if (!netif_running(qdev->ndev))
		return status;

	/* Skip the default queue, and update the outbound handler
	 * queues if they changed.
	 */
	cqicb = (struct cqicb *)&qdev->rx_ring[qdev->rss_ring_count];
	if (le16_to_cpu(cqicb->irq_delay) != qdev->tx_coalesce_usecs ||
	    le16_to_cpu(cqicb->pkt_delay) != qdev->tx_max_coalesced_frames) {
		for (i = qdev->rss_ring_count; i < qdev->rx_ring_count; i++) {
			rx_ring = &qdev->rx_ring[i];
			cqicb = (struct cqicb *)rx_ring;
			cqicb->irq_delay = cpu_to_le16(qdev->tx_coalesce_usecs);
			cqicb->pkt_delay =
<<<<<<< HEAD
				cpu_to_le16(qdev->tx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = qlge_write_cfg(qdev, cqicb, sizeof(*cqicb),
						CFG_LCQ, rx_ring->cq_id);
=======
			    cpu_to_le16(qdev->tx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = ql_write_cfg(qdev, cqicb, sizeof(*cqicb),
					      CFG_LCQ, rx_ring->cq_id);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			if (status) {
				netif_err(qdev, ifup, qdev->ndev,
					  "Failed to load CQICB.\n");
				goto exit;
			}
		}
	}

	/* Update the inbound (RSS) handler queues if they changed. */
	cqicb = (struct cqicb *)&qdev->rx_ring[0];
	if (le16_to_cpu(cqicb->irq_delay) != qdev->rx_coalesce_usecs ||
	    le16_to_cpu(cqicb->pkt_delay) != qdev->rx_max_coalesced_frames) {
		for (i = 0; i < qdev->rss_ring_count; i++, rx_ring++) {
			rx_ring = &qdev->rx_ring[i];
			cqicb = (struct cqicb *)rx_ring;
			cqicb->irq_delay = cpu_to_le16(qdev->rx_coalesce_usecs);
			cqicb->pkt_delay =
<<<<<<< HEAD
				cpu_to_le16(qdev->rx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = qlge_write_cfg(qdev, cqicb, sizeof(*cqicb),
						CFG_LCQ, rx_ring->cq_id);
=======
			    cpu_to_le16(qdev->rx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = ql_write_cfg(qdev, cqicb, sizeof(*cqicb),
					      CFG_LCQ, rx_ring->cq_id);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			if (status) {
				netif_err(qdev, ifup, qdev->ndev,
					  "Failed to load CQICB.\n");
				goto exit;
			}
		}
	}
exit:
	return status;
}

<<<<<<< HEAD
static void qlge_update_stats(struct qlge_adapter *qdev)
=======
static void ql_update_stats(struct ql_adapter *qdev)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	u32 i;
	u64 data;
	u64 *iter = &qdev->nic_stats.tx_pkts;

	spin_lock(&qdev->stats_lock);
<<<<<<< HEAD
	if (qlge_sem_spinlock(qdev, qdev->xg_sem_mask)) {
=======
	if (ql_sem_spinlock(qdev, qdev->xg_sem_mask)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		netif_err(qdev, drv, qdev->ndev,
			  "Couldn't get xgmac sem.\n");
		goto quit;
	}
	/*
	 * Get TX statistics.
	 */
	for (i = 0x200; i < 0x280; i += 8) {
<<<<<<< HEAD
		if (qlge_read_xgmac_reg64(qdev, i, &data)) {
=======
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else {
			*iter = data;
		}
		iter++;
	}

	/*
	 * Get RX statistics.
	 */
	for (i = 0x300; i < 0x3d0; i += 8) {
<<<<<<< HEAD
		if (qlge_read_xgmac_reg64(qdev, i, &data)) {
=======
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else {
			*iter = data;
		}
		iter++;
	}

	/* Update receive mac error statistics */
	iter += QLGE_RCV_MAC_ERR_STATS;

	/*
	 * Get Per-priority TX pause frame counter statistics.
	 */
	for (i = 0x500; i < 0x540; i += 8) {
<<<<<<< HEAD
		if (qlge_read_xgmac_reg64(qdev, i, &data)) {
=======
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else {
			*iter = data;
		}
		iter++;
	}

	/*
	 * Get Per-priority RX pause frame counter statistics.
	 */
	for (i = 0x568; i < 0x5a8; i += 8) {
<<<<<<< HEAD
		if (qlge_read_xgmac_reg64(qdev, i, &data)) {
=======
		if (ql_read_xgmac_reg64(qdev, i, &data)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			netif_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			goto end;
		} else {
			*iter = data;
		}
		iter++;
	}

	/*
	 * Get RX NIC FIFO DROP statistics.
	 */
<<<<<<< HEAD
	if (qlge_read_xgmac_reg64(qdev, 0x5b8, &data)) {
=======
	if (ql_read_xgmac_reg64(qdev, 0x5b8, &data)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		netif_err(qdev, drv, qdev->ndev,
			  "Error reading status register 0x%.04x.\n", i);
		goto end;
	} else {
		*iter = data;
	}
end:
<<<<<<< HEAD
	qlge_sem_unlock(qdev, qdev->xg_sem_mask);
quit:
	spin_unlock(&qdev->stats_lock);
}

static void qlge_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
=======
	ql_sem_unlock(qdev, qdev->xg_sem_mask);
quit:
	spin_unlock(&qdev->stats_lock);

	QL_DUMP_STAT(qdev);
}

static void ql_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	int index;

	switch (stringset) {
	case ETH_SS_TEST:
<<<<<<< HEAD
		memcpy(buf, *qlge_gstrings_test, QLGE_TEST_LEN * ETH_GSTRING_LEN);
=======
		memcpy(buf, *ql_gstrings_test, QLGE_TEST_LEN * ETH_GSTRING_LEN);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		break;
	case ETH_SS_STATS:
		for (index = 0; index < QLGE_STATS_LEN; index++) {
			memcpy(buf + index * ETH_GSTRING_LEN,
<<<<<<< HEAD
			       qlge_gstrings_stats[index].stat_string,
=======
			       ql_gstrings_stats[index].stat_string,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			       ETH_GSTRING_LEN);
		}
		break;
	}
}

<<<<<<< HEAD
static int qlge_get_sset_count(struct net_device *dev, int sset)
=======
static int ql_get_sset_count(struct net_device *dev, int sset)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	switch (sset) {
	case ETH_SS_TEST:
		return QLGE_TEST_LEN;
	case ETH_SS_STATS:
		return QLGE_STATS_LEN;
	default:
		return -EOPNOTSUPP;
	}
}

static void
<<<<<<< HEAD
qlge_get_ethtool_stats(struct net_device *ndev,
		       struct ethtool_stats *stats, u64 *data)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
	int index, length;

	length = QLGE_STATS_LEN;
	qlge_update_stats(qdev);

	for (index = 0; index < length; index++) {
		char *p = (char *)qdev +
			qlge_gstrings_stats[index].stat_offset;
		*data++ = (qlge_gstrings_stats[index].sizeof_stat ==
			   sizeof(u64)) ? *(u64 *)p : (*(u32 *)p);
	}
}

static int qlge_get_link_ksettings(struct net_device *ndev,
				   struct ethtool_link_ksettings *ecmd)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
ql_get_ethtool_stats(struct net_device *ndev,
		     struct ethtool_stats *stats, u64 *data)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	int index, length;

	length = QLGE_STATS_LEN;
	ql_update_stats(qdev);

	for (index = 0; index < length; index++) {
		char *p = (char *)qdev +
			ql_gstrings_stats[index].stat_offset;
		*data++ = (ql_gstrings_stats[index].sizeof_stat ==
			sizeof(u64)) ? *(u64 *)p : (*(u32 *)p);
	}
}

static int ql_get_link_ksettings(struct net_device *ndev,
				 struct ethtool_link_ksettings *ecmd)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	u32 supported, advertising;

	supported = SUPPORTED_10000baseT_Full;
	advertising = ADVERTISED_10000baseT_Full;

	if ((qdev->link_status & STS_LINK_TYPE_MASK) ==
<<<<<<< HEAD
	    STS_LINK_TYPE_10GBASET) {
=======
				STS_LINK_TYPE_10GBASET) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		supported |= (SUPPORTED_TP | SUPPORTED_Autoneg);
		advertising |= (ADVERTISED_TP | ADVERTISED_Autoneg);
		ecmd->base.port = PORT_TP;
		ecmd->base.autoneg = AUTONEG_ENABLE;
	} else {
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_FIBRE;
	}

	ecmd->base.speed = SPEED_10000;
	ecmd->base.duplex = DUPLEX_FULL;

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	return 0;
}

<<<<<<< HEAD
static void qlge_get_drvinfo(struct net_device *ndev,
			     struct ethtool_drvinfo *drvinfo)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);

	strscpy(drvinfo->driver, qlge_driver_name, sizeof(drvinfo->driver));
	strscpy(drvinfo->version, qlge_driver_version,
=======
static void ql_get_drvinfo(struct net_device *ndev,
			   struct ethtool_drvinfo *drvinfo)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	strlcpy(drvinfo->driver, qlge_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, qlge_driver_version,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		sizeof(drvinfo->version));
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		 "v%d.%d.%d",
		 (qdev->fw_rev_id & 0x00ff0000) >> 16,
		 (qdev->fw_rev_id & 0x0000ff00) >> 8,
		 (qdev->fw_rev_id & 0x000000ff));
<<<<<<< HEAD
	strscpy(drvinfo->bus_info, pci_name(qdev->pdev),
		sizeof(drvinfo->bus_info));
}

static void qlge_get_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
	strlcpy(drvinfo->bus_info, pci_name(qdev->pdev),
		sizeof(drvinfo->bus_info));
}

static void ql_get_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	unsigned short ssys_dev = qdev->pdev->subsystem_device;

	/* WOL is only supported for mezz card. */
	if (ssys_dev == QLGE_MEZZ_SSYS_ID_068 ||
	    ssys_dev == QLGE_MEZZ_SSYS_ID_180) {
		wol->supported = WAKE_MAGIC;
		wol->wolopts = qdev->wol;
	}
}

<<<<<<< HEAD
static int qlge_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
static int ql_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	unsigned short ssys_dev = qdev->pdev->subsystem_device;

	/* WOL is only supported for mezz card. */
	if (ssys_dev != QLGE_MEZZ_SSYS_ID_068 &&
	    ssys_dev != QLGE_MEZZ_SSYS_ID_180) {
		netif_info(qdev, drv, qdev->ndev,
			   "WOL is only supported for mezz card\n");
		return -EOPNOTSUPP;
	}
	if (wol->wolopts & ~WAKE_MAGIC)
		return -EINVAL;
	qdev->wol = wol->wolopts;

	netif_info(qdev, drv, qdev->ndev, "Set wol option 0x%x\n", qdev->wol);
	return 0;
}

<<<<<<< HEAD
static int qlge_set_phys_id(struct net_device *ndev,
			    enum ethtool_phys_id_state state)

{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
static int ql_set_phys_id(struct net_device *ndev,
			  enum ethtool_phys_id_state state)

{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		/* Save the current LED settings */
<<<<<<< HEAD
		if (qlge_mb_get_led_cfg(qdev))
			return -EIO;

		/* Start blinking */
		qlge_mb_set_led_cfg(qdev, QL_LED_BLINK);
=======
		if (ql_mb_get_led_cfg(qdev))
			return -EIO;

		/* Start blinking */
		ql_mb_set_led_cfg(qdev, QL_LED_BLINK);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		return 0;

	case ETHTOOL_ID_INACTIVE:
		/* Restore LED settings */
<<<<<<< HEAD
		if (qlge_mb_set_led_cfg(qdev, qdev->led_config))
=======
		if (ql_mb_set_led_cfg(qdev, qdev->led_config))
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			return -EIO;
		return 0;

	default:
		return -EINVAL;
	}
}

<<<<<<< HEAD
static int qlge_start_loopback(struct qlge_adapter *qdev)
=======
static int ql_start_loopback(struct ql_adapter *qdev)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	if (netif_carrier_ok(qdev->ndev)) {
		set_bit(QL_LB_LINK_UP, &qdev->flags);
		netif_carrier_off(qdev->ndev);
	} else {
		clear_bit(QL_LB_LINK_UP, &qdev->flags);
	}
	qdev->link_config |= CFG_LOOPBACK_PCS;
<<<<<<< HEAD
	return qlge_mb_set_port_cfg(qdev);
}

static void qlge_stop_loopback(struct qlge_adapter *qdev)
{
	qdev->link_config &= ~CFG_LOOPBACK_PCS;
	qlge_mb_set_port_cfg(qdev);
=======
	return ql_mb_set_port_cfg(qdev);
}

static void ql_stop_loopback(struct ql_adapter *qdev)
{
	qdev->link_config &= ~CFG_LOOPBACK_PCS;
	ql_mb_set_port_cfg(qdev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (test_bit(QL_LB_LINK_UP, &qdev->flags)) {
		netif_carrier_on(qdev->ndev);
		clear_bit(QL_LB_LINK_UP, &qdev->flags);
	}
}

<<<<<<< HEAD
static void qlge_create_lb_frame(struct sk_buff *skb,
				 unsigned int frame_size)
=======
static void ql_create_lb_frame(struct sk_buff *skb,
			       unsigned int frame_size)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	memset(skb->data, 0xFF, frame_size);
	frame_size &= ~1;
	memset(&skb->data[frame_size / 2], 0xAA, frame_size / 2 - 1);
	skb->data[frame_size / 2 + 10] = (unsigned char)0xBE;
	skb->data[frame_size / 2 + 12] = (unsigned char)0xAF;
}

<<<<<<< HEAD
void qlge_check_lb_frame(struct qlge_adapter *qdev,
			 struct sk_buff *skb)
=======
void ql_check_lb_frame(struct ql_adapter *qdev,
		       struct sk_buff *skb)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	unsigned int frame_size = skb->len;

	if ((*(skb->data + 3) == 0xFF) &&
	    (*(skb->data + frame_size / 2 + 10) == 0xBE) &&
	    (*(skb->data + frame_size / 2 + 12) == 0xAF)) {
		atomic_dec(&qdev->lb_count);
		return;
	}
}

<<<<<<< HEAD
static int qlge_run_loopback_test(struct qlge_adapter *qdev)
=======
static int ql_run_loopback_test(struct ql_adapter *qdev)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	int i;
	netdev_tx_t rc;
	struct sk_buff *skb;
	unsigned int size = SMALL_BUF_MAP_SIZE;

	for (i = 0; i < 64; i++) {
		skb = netdev_alloc_skb(qdev->ndev, size);
		if (!skb)
			return -ENOMEM;

		skb->queue_mapping = 0;
		skb_put(skb, size);
<<<<<<< HEAD
		qlge_create_lb_frame(skb, size);
		rc = qlge_lb_send(skb, qdev->ndev);
=======
		ql_create_lb_frame(skb, size);
		rc = ql_lb_send(skb, qdev->ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		if (rc != NETDEV_TX_OK)
			return -EPIPE;
		atomic_inc(&qdev->lb_count);
	}
	/* Give queue time to settle before testing results. */
	msleep(2);
<<<<<<< HEAD
	qlge_clean_lb_rx_ring(&qdev->rx_ring[0], 128);
	return atomic_read(&qdev->lb_count) ? -EIO : 0;
}

static int qlge_loopback_test(struct qlge_adapter *qdev, u64 *data)
{
	*data = qlge_start_loopback(qdev);
	if (*data)
		goto out;
	*data = qlge_run_loopback_test(qdev);
out:
	qlge_stop_loopback(qdev);
	return *data;
}

static void qlge_self_test(struct net_device *ndev,
			   struct ethtool_test *eth_test, u64 *data)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
	ql_clean_lb_rx_ring(&qdev->rx_ring[0], 128);
	return atomic_read(&qdev->lb_count) ? -EIO : 0;
}

static int ql_loopback_test(struct ql_adapter *qdev, u64 *data)
{
	*data = ql_start_loopback(qdev);
	if (*data)
		goto out;
	*data = ql_run_loopback_test(qdev);
out:
	ql_stop_loopback(qdev);
	return *data;
}

static void ql_self_test(struct net_device *ndev,
			 struct ethtool_test *eth_test, u64 *data)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	memset(data, 0, sizeof(u64) * QLGE_TEST_LEN);

	if (netif_running(ndev)) {
		set_bit(QL_SELFTEST, &qdev->flags);
		if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
			/* Offline tests */
<<<<<<< HEAD
			if (qlge_loopback_test(qdev, &data[0]))
=======
			if (ql_loopback_test(qdev, &data[0]))
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
				eth_test->flags |= ETH_TEST_FL_FAILED;

		} else {
			/* Online tests */
			data[0] = 0;
		}
		clear_bit(QL_SELFTEST, &qdev->flags);
		/* Give link time to come up after
		 * port configuration changes.
		 */
		msleep_interruptible(4 * 1000);
	} else {
		netif_err(qdev, drv, qdev->ndev,
			  "is down, Loopback test will fail.\n");
		eth_test->flags |= ETH_TEST_FL_FAILED;
	}
}

<<<<<<< HEAD
static int qlge_get_regs_len(struct net_device *ndev)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);

	if (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		return sizeof(struct qlge_mpi_coredump);
	else
		return sizeof(struct qlge_reg_dump);
}

static void qlge_get_regs(struct net_device *ndev,
			  struct ethtool_regs *regs, void *p)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);

	qlge_get_dump(qdev, p);
	if (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		regs->len = sizeof(struct qlge_mpi_coredump);
	else
		regs->len = sizeof(struct qlge_reg_dump);
}

static int qlge_get_coalesce(struct net_device *ndev, struct ethtool_coalesce *c)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
static int ql_get_regs_len(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	if (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		return sizeof(struct ql_mpi_coredump);
	else
		return sizeof(struct ql_reg_dump);
}

static void ql_get_regs(struct net_device *ndev,
			struct ethtool_regs *regs, void *p)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	ql_get_dump(qdev, p);
	qdev->core_is_dumped = 0;
	if (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		regs->len = sizeof(struct ql_mpi_coredump);
	else
		regs->len = sizeof(struct ql_reg_dump);
}

static int ql_get_coalesce(struct net_device *dev, struct ethtool_coalesce *c)
{
	struct ql_adapter *qdev = netdev_priv(dev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	c->rx_coalesce_usecs = qdev->rx_coalesce_usecs;
	c->tx_coalesce_usecs = qdev->tx_coalesce_usecs;

	/* This chip coalesces as follows:
	 * If a packet arrives, hold off interrupts until
	 * cqicb->int_delay expires, but if no other packets arrive don't
	 * wait longer than cqicb->pkt_int_delay. But ethtool doesn't use a
	 * timer to coalesce on a frame basis.  So, we have to take ethtool's
	 * max_coalesced_frames value and convert it to a delay in microseconds.
	 * We do this by using a basic thoughput of 1,000,000 frames per
	 * second @ (1024 bytes).  This means one frame per usec. So it's a
	 * simple one to one ratio.
	 */
	c->rx_max_coalesced_frames = qdev->rx_max_coalesced_frames;
	c->tx_max_coalesced_frames = qdev->tx_max_coalesced_frames;

	return 0;
}

<<<<<<< HEAD
static int qlge_set_coalesce(struct net_device *ndev, struct ethtool_coalesce *c)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
static int ql_set_coalesce(struct net_device *ndev, struct ethtool_coalesce *c)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	/* Validate user parameters. */
	if (c->rx_coalesce_usecs > qdev->rx_ring_size / 2)
		return -EINVAL;
<<<<<<< HEAD
	/* Don't wait more than 10 usec. */
=======
       /* Don't wait more than 10 usec. */
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (c->rx_max_coalesced_frames > MAX_INTER_FRAME_WAIT)
		return -EINVAL;
	if (c->tx_coalesce_usecs > qdev->tx_ring_size / 2)
		return -EINVAL;
	if (c->tx_max_coalesced_frames > MAX_INTER_FRAME_WAIT)
		return -EINVAL;

	/* Verify a change took place before updating the hardware. */
	if (qdev->rx_coalesce_usecs == c->rx_coalesce_usecs &&
	    qdev->tx_coalesce_usecs == c->tx_coalesce_usecs &&
	    qdev->rx_max_coalesced_frames == c->rx_max_coalesced_frames &&
	    qdev->tx_max_coalesced_frames == c->tx_max_coalesced_frames)
		return 0;

	qdev->rx_coalesce_usecs = c->rx_coalesce_usecs;
	qdev->tx_coalesce_usecs = c->tx_coalesce_usecs;
	qdev->rx_max_coalesced_frames = c->rx_max_coalesced_frames;
	qdev->tx_max_coalesced_frames = c->tx_max_coalesced_frames;

<<<<<<< HEAD
	return qlge_update_ring_coalescing(qdev);
}

static void qlge_get_pauseparam(struct net_device *ndev,
				struct ethtool_pauseparam *pause)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);

	qlge_mb_get_port_cfg(qdev);
=======
	return ql_update_ring_coalescing(qdev);
}

static void ql_get_pauseparam(struct net_device *netdev,
			      struct ethtool_pauseparam *pause)
{
	struct ql_adapter *qdev = netdev_priv(netdev);

	ql_mb_get_port_cfg(qdev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (qdev->link_config & CFG_PAUSE_STD) {
		pause->rx_pause = 1;
		pause->tx_pause = 1;
	}
}

<<<<<<< HEAD
static int qlge_set_pauseparam(struct net_device *ndev,
			       struct ethtool_pauseparam *pause)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
static int ql_set_pauseparam(struct net_device *netdev,
			     struct ethtool_pauseparam *pause)
{
	struct ql_adapter *qdev = netdev_priv(netdev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if ((pause->rx_pause) && (pause->tx_pause))
		qdev->link_config |= CFG_PAUSE_STD;
	else if (!pause->rx_pause && !pause->tx_pause)
		qdev->link_config &= ~CFG_PAUSE_STD;
	else
		return -EINVAL;

<<<<<<< HEAD
	return qlge_mb_set_port_cfg(qdev);
}

static u32 qlge_get_msglevel(struct net_device *ndev)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
	return ql_mb_set_port_cfg(qdev);
}

static u32 ql_get_msglevel(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return qdev->msg_enable;
}

<<<<<<< HEAD
static void qlge_set_msglevel(struct net_device *ndev, u32 value)
{
	struct qlge_adapter *qdev = netdev_to_qdev(ndev);
=======
static void ql_set_msglevel(struct net_device *ndev, u32 value)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	qdev->msg_enable = value;
}

const struct ethtool_ops qlge_ethtool_ops = {
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
<<<<<<< HEAD
	.get_drvinfo = qlge_get_drvinfo,
	.get_wol = qlge_get_wol,
	.set_wol = qlge_set_wol,
	.get_regs_len	= qlge_get_regs_len,
	.get_regs = qlge_get_regs,
	.get_msglevel = qlge_get_msglevel,
	.set_msglevel = qlge_set_msglevel,
	.get_link = ethtool_op_get_link,
	.set_phys_id		 = qlge_set_phys_id,
	.self_test		 = qlge_self_test,
	.get_pauseparam		 = qlge_get_pauseparam,
	.set_pauseparam		 = qlge_set_pauseparam,
	.get_coalesce = qlge_get_coalesce,
	.set_coalesce = qlge_set_coalesce,
	.get_sset_count = qlge_get_sset_count,
	.get_strings = qlge_get_strings,
	.get_ethtool_stats = qlge_get_ethtool_stats,
	.get_link_ksettings = qlge_get_link_ksettings,
=======
	.get_drvinfo = ql_get_drvinfo,
	.get_wol = ql_get_wol,
	.set_wol = ql_set_wol,
	.get_regs_len	= ql_get_regs_len,
	.get_regs = ql_get_regs,
	.get_msglevel = ql_get_msglevel,
	.set_msglevel = ql_set_msglevel,
	.get_link = ethtool_op_get_link,
	.set_phys_id		 = ql_set_phys_id,
	.self_test		 = ql_self_test,
	.get_pauseparam		 = ql_get_pauseparam,
	.set_pauseparam		 = ql_set_pauseparam,
	.get_coalesce = ql_get_coalesce,
	.set_coalesce = ql_set_coalesce,
	.get_sset_count = ql_get_sset_count,
	.get_strings = ql_get_strings,
	.get_ethtool_stats = ql_get_ethtool_stats,
	.get_link_ksettings = ql_get_link_ksettings,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

