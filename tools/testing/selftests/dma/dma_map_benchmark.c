// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2020 Hisilicon Limited.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/types.h>

<<<<<<< HEAD
#define NSEC_PER_MSEC	1000000L

#define DMA_MAP_BENCHMARK	_IOWR('d', 1, struct map_benchmark)
#define DMA_MAP_MAX_THREADS	1024
#define DMA_MAP_MAX_SECONDS     300
#define DMA_MAP_MAX_TRANS_DELAY	(10 * NSEC_PER_MSEC)
=======
#define DMA_MAP_BENCHMARK	_IOWR('d', 1, struct map_benchmark)
#define DMA_MAP_MAX_THREADS	1024
#define DMA_MAP_MAX_SECONDS     300
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#define DMA_MAP_BIDIRECTIONAL	0
#define DMA_MAP_TO_DEVICE	1
#define DMA_MAP_FROM_DEVICE	2

static char *directions[] = {
	"BIDIRECTIONAL",
	"TO_DEVICE",
	"FROM_DEVICE",
};

struct map_benchmark {
	__u64 avg_map_100ns; /* average map latency in 100ns */
	__u64 map_stddev; /* standard deviation of map latency */
	__u64 avg_unmap_100ns; /* as above */
	__u64 unmap_stddev;
	__u32 threads; /* how many threads will do map/unmap in parallel */
	__u32 seconds; /* how long the test will last */
	__s32 node; /* which numa node this benchmark will run on */
	__u32 dma_bits; /* DMA addressing capability */
	__u32 dma_dir; /* DMA data direction */
<<<<<<< HEAD
	__u32 dma_trans_ns; /* time for DMA transmission in ns */
	__u8 expansion[80];	/* For future use */
=======
	__u8 expansion[84];	/* For future use */
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

int main(int argc, char **argv)
{
	struct map_benchmark map;
	int fd, opt;
	/* default single thread, run 20 seconds on NUMA_NO_NODE */
	int threads = 1, seconds = 20, node = -1;
	/* default dma mask 32bit, bidirectional DMA */
<<<<<<< HEAD
	int bits = 32, xdelay = 0, dir = DMA_MAP_BIDIRECTIONAL;
=======
	int bits = 32, dir = DMA_MAP_BIDIRECTIONAL;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	int cmd = DMA_MAP_BENCHMARK;
	char *p;

<<<<<<< HEAD
	while ((opt = getopt(argc, argv, "t:s:n:b:d:x:")) != -1) {
=======
	while ((opt = getopt(argc, argv, "t:s:n:b:d:")) != -1) {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		switch (opt) {
		case 't':
			threads = atoi(optarg);
			break;
		case 's':
			seconds = atoi(optarg);
			break;
		case 'n':
			node = atoi(optarg);
			break;
		case 'b':
			bits = atoi(optarg);
			break;
		case 'd':
			dir = atoi(optarg);
			break;
<<<<<<< HEAD
		case 'x':
			xdelay = atoi(optarg);
			break;
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		default:
			return -1;
		}
	}

	if (threads <= 0 || threads > DMA_MAP_MAX_THREADS) {
		fprintf(stderr, "invalid number of threads, must be in 1-%d\n",
			DMA_MAP_MAX_THREADS);
		exit(1);
	}

	if (seconds <= 0 || seconds > DMA_MAP_MAX_SECONDS) {
		fprintf(stderr, "invalid number of seconds, must be in 1-%d\n",
			DMA_MAP_MAX_SECONDS);
		exit(1);
	}

<<<<<<< HEAD
	if (xdelay < 0 || xdelay > DMA_MAP_MAX_TRANS_DELAY) {
		fprintf(stderr, "invalid transmit delay, must be in 0-%ld\n",
			DMA_MAP_MAX_TRANS_DELAY);
		exit(1);
	}

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	/* suppose the mininum DMA zone is 1MB in the world */
	if (bits < 20 || bits > 64) {
		fprintf(stderr, "invalid dma mask bit, must be in 20-64\n");
		exit(1);
	}

	if (dir != DMA_MAP_BIDIRECTIONAL && dir != DMA_MAP_TO_DEVICE &&
			dir != DMA_MAP_FROM_DEVICE) {
		fprintf(stderr, "invalid dma direction\n");
		exit(1);
	}

	fd = open("/sys/kernel/debug/dma_map_benchmark", O_RDWR);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	memset(&map, 0, sizeof(map));
	map.seconds = seconds;
	map.threads = threads;
	map.node = node;
	map.dma_bits = bits;
	map.dma_dir = dir;
<<<<<<< HEAD
	map.dma_trans_ns = xdelay;

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (ioctl(fd, cmd, &map)) {
		perror("ioctl");
		exit(1);
	}

	printf("dma mapping benchmark: threads:%d seconds:%d node:%d dir:%s\n",
			threads, seconds, node, dir[directions]);
	printf("average map latency(us):%.1f standard deviation:%.1f\n",
			map.avg_map_100ns/10.0, map.map_stddev/10.0);
	printf("average unmap latency(us):%.1f standard deviation:%.1f\n",
			map.avg_unmap_100ns/10.0, map.unmap_stddev/10.0);

	return 0;
}
