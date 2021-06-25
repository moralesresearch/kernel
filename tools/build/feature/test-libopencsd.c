// SPDX-License-Identifier: GPL-2.0
#include <opencsd/c_api/opencsd_c_api.h>

/*
 * Check OpenCSD library version is sufficient to provide required features
 */
<<<<<<< HEAD
#define OCSD_MIN_VER ((1 << 16) | (0 << 8) | (0))
#if !defined(OCSD_VER_NUM) || (OCSD_VER_NUM < OCSD_MIN_VER)
#error "OpenCSD >= 1.0.0 is required"
=======
#define OCSD_MIN_VER ((0 << 16) | (14 << 8) | (0))
#if !defined(OCSD_VER_NUM) || (OCSD_VER_NUM < OCSD_MIN_VER)
#error "OpenCSD >= 0.14.0 is required"
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif

int main(void)
{
	(void)ocsd_get_version();
	return 0;
}
