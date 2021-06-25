// SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#include "rxe.h"
#include "rxe_loc.h"

/*
 * lfsr (linear feedback shift register) with period 255
 */
static u8 rxe_get_key(void)
{
	static u32 key = 1;

	key = key << 1;

	key |= (0 != (key & 0x100)) ^ (0 != (key & 0x10))
		^ (0 != (key & 0x80)) ^ (0 != (key & 0x40));

	key &= 0xff;

	return key;
}

<<<<<<< HEAD
int mr_check_range(struct rxe_mr *mr, u64 iova, size_t length)
{
	switch (mr->type) {
	case RXE_MR_TYPE_DMA:
		return 0;

	case RXE_MR_TYPE_MR:
		if (iova < mr->iova || length > mr->length ||
		    iova > mr->iova + mr->length - length)
=======
int mem_check_range(struct rxe_mem *mem, u64 iova, size_t length)
{
	switch (mem->type) {
	case RXE_MEM_TYPE_DMA:
		return 0;

	case RXE_MEM_TYPE_MR:
		if (iova < mem->iova ||
		    length > mem->length ||
		    iova > mem->iova + mem->length - length)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			return -EFAULT;
		return 0;

	default:
		return -EFAULT;
	}
}

#define IB_ACCESS_REMOTE	(IB_ACCESS_REMOTE_READ		\
				| IB_ACCESS_REMOTE_WRITE	\
				| IB_ACCESS_REMOTE_ATOMIC)

<<<<<<< HEAD
static void rxe_mr_init(int access, struct rxe_mr *mr)
{
	u32 lkey = mr->pelem.index << 8 | rxe_get_key();
	u32 rkey = (access & IB_ACCESS_REMOTE) ? lkey : 0;

	mr->ibmr.lkey = lkey;
	mr->ibmr.rkey = rkey;
	mr->state = RXE_MR_STATE_INVALID;
	mr->type = RXE_MR_TYPE_NONE;
	mr->map_shift = ilog2(RXE_BUF_PER_MAP);
}

void rxe_mr_cleanup(struct rxe_pool_entry *arg)
{
	struct rxe_mr *mr = container_of(arg, typeof(*mr), pelem);
	int i;

	ib_umem_release(mr->umem);

	if (mr->map) {
		for (i = 0; i < mr->num_map; i++)
			kfree(mr->map[i]);

		kfree(mr->map);
	}
}

static int rxe_mr_alloc(struct rxe_mr *mr, int num_buf)
{
	int i;
	int num_map;
	struct rxe_map **map = mr->map;

	num_map = (num_buf + RXE_BUF_PER_MAP - 1) / RXE_BUF_PER_MAP;

	mr->map = kmalloc_array(num_map, sizeof(*map), GFP_KERNEL);
	if (!mr->map)
		goto err1;

	for (i = 0; i < num_map; i++) {
		mr->map[i] = kmalloc(sizeof(**map), GFP_KERNEL);
		if (!mr->map[i])
=======
static void rxe_mem_init(int access, struct rxe_mem *mem)
{
	u32 lkey = mem->pelem.index << 8 | rxe_get_key();
	u32 rkey = (access & IB_ACCESS_REMOTE) ? lkey : 0;

	mem->ibmr.lkey		= lkey;
	mem->ibmr.rkey		= rkey;
	mem->state		= RXE_MEM_STATE_INVALID;
	mem->type		= RXE_MEM_TYPE_NONE;
	mem->map_shift		= ilog2(RXE_BUF_PER_MAP);
}

void rxe_mem_cleanup(struct rxe_pool_entry *arg)
{
	struct rxe_mem *mem = container_of(arg, typeof(*mem), pelem);
	int i;

	ib_umem_release(mem->umem);

	if (mem->map) {
		for (i = 0; i < mem->num_map; i++)
			kfree(mem->map[i]);

		kfree(mem->map);
	}
}

static int rxe_mem_alloc(struct rxe_mem *mem, int num_buf)
{
	int i;
	int num_map;
	struct rxe_map **map = mem->map;

	num_map = (num_buf + RXE_BUF_PER_MAP - 1) / RXE_BUF_PER_MAP;

	mem->map = kmalloc_array(num_map, sizeof(*map), GFP_KERNEL);
	if (!mem->map)
		goto err1;

	for (i = 0; i < num_map; i++) {
		mem->map[i] = kmalloc(sizeof(**map), GFP_KERNEL);
		if (!mem->map[i])
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			goto err2;
	}

	BUILD_BUG_ON(!is_power_of_2(RXE_BUF_PER_MAP));

<<<<<<< HEAD
	mr->map_shift = ilog2(RXE_BUF_PER_MAP);
	mr->map_mask = RXE_BUF_PER_MAP - 1;

	mr->num_buf = num_buf;
	mr->num_map = num_map;
	mr->max_buf = num_map * RXE_BUF_PER_MAP;
=======
	mem->map_shift	= ilog2(RXE_BUF_PER_MAP);
	mem->map_mask	= RXE_BUF_PER_MAP - 1;

	mem->num_buf = num_buf;
	mem->num_map = num_map;
	mem->max_buf = num_map * RXE_BUF_PER_MAP;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;

err2:
	for (i--; i >= 0; i--)
<<<<<<< HEAD
		kfree(mr->map[i]);

	kfree(mr->map);
=======
		kfree(mem->map[i]);

	kfree(mem->map);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
err1:
	return -ENOMEM;
}

<<<<<<< HEAD
void rxe_mr_init_dma(struct rxe_pd *pd, int access, struct rxe_mr *mr)
{
	rxe_mr_init(access, mr);

	mr->ibmr.pd = &pd->ibpd;
	mr->access = access;
	mr->state = RXE_MR_STATE_VALID;
	mr->type = RXE_MR_TYPE_DMA;
}

int rxe_mr_init_user(struct rxe_pd *pd, u64 start, u64 length, u64 iova,
		     int access, struct ib_udata *udata, struct rxe_mr *mr)
=======
void rxe_mem_init_dma(struct rxe_pd *pd,
		      int access, struct rxe_mem *mem)
{
	rxe_mem_init(access, mem);

	mem->ibmr.pd		= &pd->ibpd;
	mem->access		= access;
	mem->state		= RXE_MEM_STATE_VALID;
	mem->type		= RXE_MEM_TYPE_DMA;
}

int rxe_mem_init_user(struct rxe_pd *pd, u64 start,
		      u64 length, u64 iova, int access, struct ib_udata *udata,
		      struct rxe_mem *mem)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	struct rxe_map		**map;
	struct rxe_phys_buf	*buf = NULL;
	struct ib_umem		*umem;
	struct sg_page_iter	sg_iter;
	int			num_buf;
	void			*vaddr;
	int err;

	umem = ib_umem_get(pd->ibpd.device, start, length, access);
	if (IS_ERR(umem)) {
		pr_warn("err %d from rxe_umem_get\n",
			(int)PTR_ERR(umem));
		err = -EINVAL;
		goto err1;
	}

<<<<<<< HEAD
	mr->umem = umem;
	num_buf = ib_umem_num_pages(umem);

	rxe_mr_init(access, mr);

	err = rxe_mr_alloc(mr, num_buf);
	if (err) {
		pr_warn("err %d from rxe_mr_alloc\n", err);
=======
	mem->umem = umem;
	num_buf = ib_umem_num_pages(umem);

	rxe_mem_init(access, mem);

	err = rxe_mem_alloc(mem, num_buf);
	if (err) {
		pr_warn("err %d from rxe_mem_alloc\n", err);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		ib_umem_release(umem);
		goto err1;
	}

<<<<<<< HEAD
	mr->page_shift = PAGE_SHIFT;
	mr->page_mask = PAGE_SIZE - 1;

	num_buf			= 0;
	map = mr->map;
=======
	mem->page_shift		= PAGE_SHIFT;
	mem->page_mask = PAGE_SIZE - 1;

	num_buf			= 0;
	map			= mem->map;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (length > 0) {
		buf = map[0]->buf;

		for_each_sg_page(umem->sg_head.sgl, &sg_iter, umem->nmap, 0) {
			if (num_buf >= RXE_BUF_PER_MAP) {
				map++;
				buf = map[0]->buf;
				num_buf = 0;
			}

			vaddr = page_address(sg_page_iter_page(&sg_iter));
			if (!vaddr) {
				pr_warn("null vaddr\n");
				ib_umem_release(umem);
				err = -ENOMEM;
				goto err1;
			}

			buf->addr = (uintptr_t)vaddr;
			buf->size = PAGE_SIZE;
			num_buf++;
			buf++;

		}
	}

<<<<<<< HEAD
	mr->ibmr.pd = &pd->ibpd;
	mr->umem = umem;
	mr->access = access;
	mr->length = length;
	mr->iova = iova;
	mr->va = start;
	mr->offset = ib_umem_offset(umem);
	mr->state = RXE_MR_STATE_VALID;
	mr->type = RXE_MR_TYPE_MR;
=======
	mem->ibmr.pd		= &pd->ibpd;
	mem->umem		= umem;
	mem->access		= access;
	mem->length		= length;
	mem->iova		= iova;
	mem->va			= start;
	mem->offset		= ib_umem_offset(umem);
	mem->state		= RXE_MEM_STATE_VALID;
	mem->type		= RXE_MEM_TYPE_MR;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;

err1:
	return err;
}

<<<<<<< HEAD
int rxe_mr_init_fast(struct rxe_pd *pd, int max_pages, struct rxe_mr *mr)
{
	int err;

	rxe_mr_init(0, mr);

	/* In fastreg, we also set the rkey */
	mr->ibmr.rkey = mr->ibmr.lkey;

	err = rxe_mr_alloc(mr, max_pages);
	if (err)
		goto err1;

	mr->ibmr.pd = &pd->ibpd;
	mr->max_buf = max_pages;
	mr->state = RXE_MR_STATE_FREE;
	mr->type = RXE_MR_TYPE_MR;
=======
int rxe_mem_init_fast(struct rxe_pd *pd,
		      int max_pages, struct rxe_mem *mem)
{
	int err;

	rxe_mem_init(0, mem);

	/* In fastreg, we also set the rkey */
	mem->ibmr.rkey = mem->ibmr.lkey;

	err = rxe_mem_alloc(mem, max_pages);
	if (err)
		goto err1;

	mem->ibmr.pd		= &pd->ibpd;
	mem->max_buf		= max_pages;
	mem->state		= RXE_MEM_STATE_FREE;
	mem->type		= RXE_MEM_TYPE_MR;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;

err1:
	return err;
}

<<<<<<< HEAD
static void lookup_iova(struct rxe_mr *mr, u64 iova, int *m_out, int *n_out,
			size_t *offset_out)
{
	size_t offset = iova - mr->iova + mr->offset;
=======
static void lookup_iova(
	struct rxe_mem	*mem,
	u64			iova,
	int			*m_out,
	int			*n_out,
	size_t			*offset_out)
{
	size_t			offset = iova - mem->iova + mem->offset;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	int			map_index;
	int			buf_index;
	u64			length;

<<<<<<< HEAD
	if (likely(mr->page_shift)) {
		*offset_out = offset & mr->page_mask;
		offset >>= mr->page_shift;
		*n_out = offset & mr->map_mask;
		*m_out = offset >> mr->map_shift;
=======
	if (likely(mem->page_shift)) {
		*offset_out = offset & mem->page_mask;
		offset >>= mem->page_shift;
		*n_out = offset & mem->map_mask;
		*m_out = offset >> mem->map_shift;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	} else {
		map_index = 0;
		buf_index = 0;

<<<<<<< HEAD
		length = mr->map[map_index]->buf[buf_index].size;
=======
		length = mem->map[map_index]->buf[buf_index].size;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		while (offset >= length) {
			offset -= length;
			buf_index++;

			if (buf_index == RXE_BUF_PER_MAP) {
				map_index++;
				buf_index = 0;
			}
<<<<<<< HEAD
			length = mr->map[map_index]->buf[buf_index].size;
=======
			length = mem->map[map_index]->buf[buf_index].size;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		}

		*m_out = map_index;
		*n_out = buf_index;
		*offset_out = offset;
	}
}

<<<<<<< HEAD
void *iova_to_vaddr(struct rxe_mr *mr, u64 iova, int length)
=======
void *iova_to_vaddr(struct rxe_mem *mem, u64 iova, int length)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	size_t offset;
	int m, n;
	void *addr;

<<<<<<< HEAD
	if (mr->state != RXE_MR_STATE_VALID) {
		pr_warn("mr not in valid state\n");
=======
	if (mem->state != RXE_MEM_STATE_VALID) {
		pr_warn("mem not in valid state\n");
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		addr = NULL;
		goto out;
	}

<<<<<<< HEAD
	if (!mr->map) {
=======
	if (!mem->map) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		addr = (void *)(uintptr_t)iova;
		goto out;
	}

<<<<<<< HEAD
	if (mr_check_range(mr, iova, length)) {
=======
	if (mem_check_range(mem, iova, length)) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		pr_warn("range violation\n");
		addr = NULL;
		goto out;
	}

<<<<<<< HEAD
	lookup_iova(mr, iova, &m, &n, &offset);

	if (offset + length > mr->map[m]->buf[n].size) {
=======
	lookup_iova(mem, iova, &m, &n, &offset);

	if (offset + length > mem->map[m]->buf[n].size) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		pr_warn("crosses page boundary\n");
		addr = NULL;
		goto out;
	}

<<<<<<< HEAD
	addr = (void *)(uintptr_t)mr->map[m]->buf[n].addr + offset;
=======
	addr = (void *)(uintptr_t)mem->map[m]->buf[n].addr + offset;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

out:
	return addr;
}

/* copy data from a range (vaddr, vaddr+length-1) to or from
<<<<<<< HEAD
 * a mr object starting at iova. Compute incremental value of
 * crc32 if crcp is not zero. caller must hold a reference to mr
 */
int rxe_mr_copy(struct rxe_mr *mr, u64 iova, void *addr, int length,
		enum copy_direction dir, u32 *crcp)
=======
 * a mem object starting at iova. Compute incremental value of
 * crc32 if crcp is not zero. caller must hold a reference to mem
 */
int rxe_mem_copy(struct rxe_mem *mem, u64 iova, void *addr, int length,
		 enum copy_direction dir, u32 *crcp)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	int			err;
	int			bytes;
	u8			*va;
	struct rxe_map		**map;
	struct rxe_phys_buf	*buf;
	int			m;
	int			i;
	size_t			offset;
	u32			crc = crcp ? (*crcp) : 0;

	if (length == 0)
		return 0;

<<<<<<< HEAD
	if (mr->type == RXE_MR_TYPE_DMA) {
		u8 *src, *dest;

		src = (dir == to_mr_obj) ? addr : ((void *)(uintptr_t)iova);

		dest = (dir == to_mr_obj) ? ((void *)(uintptr_t)iova) : addr;
=======
	if (mem->type == RXE_MEM_TYPE_DMA) {
		u8 *src, *dest;

		src  = (dir == to_mem_obj) ?
			addr : ((void *)(uintptr_t)iova);

		dest = (dir == to_mem_obj) ?
			((void *)(uintptr_t)iova) : addr;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		memcpy(dest, src, length);

		if (crcp)
<<<<<<< HEAD
			*crcp = rxe_crc32(to_rdev(mr->ibmr.device), *crcp, dest,
					  length);
=======
			*crcp = rxe_crc32(to_rdev(mem->ibmr.device),
					*crcp, dest, length);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		return 0;
	}

<<<<<<< HEAD
	WARN_ON_ONCE(!mr->map);

	err = mr_check_range(mr, iova, length);
=======
	WARN_ON_ONCE(!mem->map);

	err = mem_check_range(mem, iova, length);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (err) {
		err = -EFAULT;
		goto err1;
	}

<<<<<<< HEAD
	lookup_iova(mr, iova, &m, &i, &offset);

	map = mr->map + m;
=======
	lookup_iova(mem, iova, &m, &i, &offset);

	map	= mem->map + m;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	buf	= map[0]->buf + i;

	while (length > 0) {
		u8 *src, *dest;

		va	= (u8 *)(uintptr_t)buf->addr + offset;
<<<<<<< HEAD
		src = (dir == to_mr_obj) ? addr : va;
		dest = (dir == to_mr_obj) ? va : addr;
=======
		src  = (dir == to_mem_obj) ? addr : va;
		dest = (dir == to_mem_obj) ? va : addr;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		bytes	= buf->size - offset;

		if (bytes > length)
			bytes = length;

		memcpy(dest, src, bytes);

		if (crcp)
<<<<<<< HEAD
			crc = rxe_crc32(to_rdev(mr->ibmr.device), crc, dest,
					bytes);
=======
			crc = rxe_crc32(to_rdev(mem->ibmr.device),
					crc, dest, bytes);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		length	-= bytes;
		addr	+= bytes;

		offset	= 0;
		buf++;
		i++;

		if (i == RXE_BUF_PER_MAP) {
			i = 0;
			map++;
			buf = map[0]->buf;
		}
	}

	if (crcp)
		*crcp = crc;

	return 0;

err1:
	return err;
}

/* copy data in or out of a wqe, i.e. sg list
 * under the control of a dma descriptor
 */
int copy_data(
	struct rxe_pd		*pd,
	int			access,
	struct rxe_dma_info	*dma,
	void			*addr,
	int			length,
	enum copy_direction	dir,
	u32			*crcp)
{
	int			bytes;
	struct rxe_sge		*sge	= &dma->sge[dma->cur_sge];
	int			offset	= dma->sge_offset;
	int			resid	= dma->resid;
<<<<<<< HEAD
	struct rxe_mr		*mr	= NULL;
=======
	struct rxe_mem		*mem	= NULL;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	u64			iova;
	int			err;

	if (length == 0)
		return 0;

	if (length > resid) {
		err = -EINVAL;
		goto err2;
	}

	if (sge->length && (offset < sge->length)) {
<<<<<<< HEAD
		mr = lookup_mr(pd, access, sge->lkey, lookup_local);
		if (!mr) {
=======
		mem = lookup_mem(pd, access, sge->lkey, lookup_local);
		if (!mem) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			err = -EINVAL;
			goto err1;
		}
	}

	while (length > 0) {
		bytes = length;

		if (offset >= sge->length) {
<<<<<<< HEAD
			if (mr) {
				rxe_drop_ref(mr);
				mr = NULL;
=======
			if (mem) {
				rxe_drop_ref(mem);
				mem = NULL;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			}
			sge++;
			dma->cur_sge++;
			offset = 0;

			if (dma->cur_sge >= dma->num_sge) {
				err = -ENOSPC;
				goto err2;
			}

			if (sge->length) {
<<<<<<< HEAD
				mr = lookup_mr(pd, access, sge->lkey,
					       lookup_local);
				if (!mr) {
=======
				mem = lookup_mem(pd, access, sge->lkey,
						 lookup_local);
				if (!mem) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
					err = -EINVAL;
					goto err1;
				}
			} else {
				continue;
			}
		}

		if (bytes > sge->length - offset)
			bytes = sge->length - offset;

		if (bytes > 0) {
			iova = sge->addr + offset;

<<<<<<< HEAD
			err = rxe_mr_copy(mr, iova, addr, bytes, dir, crcp);
=======
			err = rxe_mem_copy(mem, iova, addr, bytes, dir, crcp);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			if (err)
				goto err2;

			offset	+= bytes;
			resid	-= bytes;
			length	-= bytes;
			addr	+= bytes;
		}
	}

	dma->sge_offset = offset;
	dma->resid	= resid;

<<<<<<< HEAD
	if (mr)
		rxe_drop_ref(mr);
=======
	if (mem)
		rxe_drop_ref(mem);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;

err2:
<<<<<<< HEAD
	if (mr)
		rxe_drop_ref(mr);
=======
	if (mem)
		rxe_drop_ref(mem);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
err1:
	return err;
}

int advance_dma_data(struct rxe_dma_info *dma, unsigned int length)
{
	struct rxe_sge		*sge	= &dma->sge[dma->cur_sge];
	int			offset	= dma->sge_offset;
	int			resid	= dma->resid;

	while (length) {
		unsigned int bytes;

		if (offset >= sge->length) {
			sge++;
			dma->cur_sge++;
			offset = 0;
			if (dma->cur_sge >= dma->num_sge)
				return -ENOSPC;
		}

		bytes = length;

		if (bytes > sge->length - offset)
			bytes = sge->length - offset;

		offset	+= bytes;
		resid	-= bytes;
		length	-= bytes;
	}

	dma->sge_offset = offset;
	dma->resid	= resid;

	return 0;
}

<<<<<<< HEAD
/* (1) find the mr corresponding to lkey/rkey
 *     depending on lookup_type
 * (2) verify that the (qp) pd matches the mr pd
 * (3) verify that the mr can support the requested access
 * (4) verify that mr state is valid
 */
struct rxe_mr *lookup_mr(struct rxe_pd *pd, int access, u32 key,
			 enum lookup_type type)
{
	struct rxe_mr *mr;
	struct rxe_dev *rxe = to_rdev(pd->ibpd.device);
	int index = key >> 8;

	mr = rxe_pool_get_index(&rxe->mr_pool, index);
	if (!mr)
		return NULL;

	if (unlikely((type == lookup_local && mr_lkey(mr) != key) ||
		     (type == lookup_remote && mr_rkey(mr) != key) ||
		     mr_pd(mr) != pd || (access && !(access & mr->access)) ||
		     mr->state != RXE_MR_STATE_VALID)) {
		rxe_drop_ref(mr);
		mr = NULL;
	}

	return mr;
=======
/* (1) find the mem (mr or mw) corresponding to lkey/rkey
 *     depending on lookup_type
 * (2) verify that the (qp) pd matches the mem pd
 * (3) verify that the mem can support the requested access
 * (4) verify that mem state is valid
 */
struct rxe_mem *lookup_mem(struct rxe_pd *pd, int access, u32 key,
			   enum lookup_type type)
{
	struct rxe_mem *mem;
	struct rxe_dev *rxe = to_rdev(pd->ibpd.device);
	int index = key >> 8;

	mem = rxe_pool_get_index(&rxe->mr_pool, index);
	if (!mem)
		return NULL;

	if (unlikely((type == lookup_local && mr_lkey(mem) != key) ||
		     (type == lookup_remote && mr_rkey(mem) != key) ||
		     mr_pd(mem) != pd ||
		     (access && !(access & mem->access)) ||
		     mem->state != RXE_MEM_STATE_VALID)) {
		rxe_drop_ref(mem);
		mem = NULL;
	}

	return mem;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}
