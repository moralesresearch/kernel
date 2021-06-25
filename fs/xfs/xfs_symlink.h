// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2012 Red Hat, Inc. All rights reserved.
 */
#ifndef __XFS_SYMLINK_H
#define __XFS_SYMLINK_H 1

/* Kernel only symlink definitions */

<<<<<<< HEAD
int xfs_symlink(struct user_namespace *mnt_userns, struct xfs_inode *dp,
		struct xfs_name *link_name, const char *target_path,
		umode_t mode, struct xfs_inode **ipp);
=======
int xfs_symlink(struct xfs_inode *dp, struct xfs_name *link_name,
		const char *target_path, umode_t mode, struct xfs_inode **ipp);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
int xfs_readlink_bmap_ilocked(struct xfs_inode *ip, char *link);
int xfs_readlink(struct xfs_inode *ip, char *link);
int xfs_inactive_symlink(struct xfs_inode *ip);

#endif /* __XFS_SYMLINK_H */
