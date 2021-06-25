/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __S390_VDSO_H__
#define __S390_VDSO_H__

#include <vdso/datapage.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
/* Default link address for the vDSO */
#define VDSO64_LBASE	0

#define __VVAR_PAGES	2

<<<<<<< HEAD
=======
=======
/* Default link addresses for the vDSOs */
#define VDSO32_LBASE	0
#define VDSO64_LBASE	0

>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#define VDSO_VERSION_STRING	LINUX_2.6.29

#ifndef __ASSEMBLY__

extern struct vdso_data *vdso_data;

<<<<<<< HEAD
int vdso_getcpu_init(void);
=======
<<<<<<< HEAD
int vdso_getcpu_init(void);
=======
void vdso_getcpu_init(void);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* __ASSEMBLY__ */
#endif /* __S390_VDSO_H__ */
