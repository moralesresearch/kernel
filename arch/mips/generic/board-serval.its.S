/* SPDX-License-Identifier: (GPL-2.0 OR MIT) */
/ {
	images {
<<<<<<< HEAD
		fdt-serval_pcb105 {
=======
		fdt@serval_pcb105 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MSCC Serval PCB105 Device Tree";
			data = /incbin/("boot/dts/mscc/serval_pcb105.dtb");
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
		pcb105 {
			description = "Serval Linux kernel";
<<<<<<< HEAD
			kernel = "kernel";
			fdt = "fdt-serval_pcb105";
=======
			kernel = "kernel@0";
			fdt = "fdt@serval_pcb105";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			ramdisk = "ramdisk";
		};
	};
};
