/* SPDX-License-Identifier: GPL-2.0 */
#if defined(__i386__) || defined(__x86_64__)
#include "../../../arch/x86/include/uapi/asm/errno.h"
#elif defined(__powerpc__)
#include "../../../arch/powerpc/include/uapi/asm/errno.h"
#elif defined(__sparc__)
#include "../../../arch/sparc/include/uapi/asm/errno.h"
#elif defined(__alpha__)
#include "../../../arch/alpha/include/uapi/asm/errno.h"
#elif defined(__mips__)
#include "../../../arch/mips/include/uapi/asm/errno.h"
<<<<<<< HEAD
=======
#elif defined(__ia64__)
#include "../../../arch/ia64/include/uapi/asm/errno.h"
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#elif defined(__xtensa__)
#include "../../../arch/xtensa/include/uapi/asm/errno.h"
#else
#include <asm-generic/errno.h>
#endif
