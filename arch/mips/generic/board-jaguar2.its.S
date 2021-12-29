/* SPDX-License-Identifier: (GPL-2.0 OR MIT) */
/ {
	images {
<<<<<<< HEAD
		fdt-jaguar2_pcb110 {
=======
		fdt@jaguar2_pcb110 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MSCC Jaguar2 PCB110 Device Tree";
			data = /incbin/("boot/dts/mscc/jaguar2_pcb110.dtb");
			type = "flat_dt";
			arch = "mips";
			compression = "none";
<<<<<<< HEAD
			hash {
				algo = "sha1";
			};
		};
		fdt-jaguar2_pcb111 {
=======
			hash@0 {
				algo = "sha1";
			};
		};
		fdt@jaguar2_pcb111 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MSCC Jaguar2 PCB111 Device Tree";
			data = /incbin/("boot/dts/mscc/jaguar2_pcb111.dtb");
			type = "flat_dt";
			arch = "mips";
			compression = "none";
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
		pcb110 {
			description = "Jaguar2 Linux kernel";
<<<<<<< HEAD
			kernel = "kernel";
			fdt = "fdt-jaguar2_pcb110";
=======
			kernel = "kernel@0";
			fdt = "fdt@jaguar2_pcb110";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			ramdisk = "ramdisk";
		};
		pcb111 {
			description = "Jaguar2 Linux kernel";
<<<<<<< HEAD
			kernel = "kernel";
			fdt = "fdt-jaguar2_pcb111";
=======
			kernel = "kernel@0";
			fdt = "fdt@jaguar2_pcb111";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			ramdisk = "ramdisk";
		};
	};
};
