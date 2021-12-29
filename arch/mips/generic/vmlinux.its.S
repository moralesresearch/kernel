/* SPDX-License-Identifier: GPL-2.0 */
/dts-v1/;

/ {
	description = KERNEL_NAME;
	#address-cells = <ADDR_CELLS>;

	images {
<<<<<<< HEAD
		kernel {
=======
		kernel@0 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = KERNEL_NAME;
			data = /incbin/(VMLINUX_BINARY);
			type = "kernel";
			arch = "mips";
			os = "linux";
			compression = VMLINUX_COMPRESSION;
			load = /bits/ ADDR_BITS <VMLINUX_LOAD_ADDRESS>;
			entry = /bits/ ADDR_BITS <VMLINUX_ENTRY_ADDRESS>;
<<<<<<< HEAD
			hash {
=======
			hash@0 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
				algo = "sha1";
			};
		};
	};

	configurations {
<<<<<<< HEAD
		default = "conf-default";

		conf-default {
			description = "Generic Linux kernel";
			kernel = "kernel";
=======
		default = "conf@default";

		conf@default {
			description = "Generic Linux kernel";
			kernel = "kernel@0";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		};
	};
};
