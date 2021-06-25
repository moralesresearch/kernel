/* SPDX-License-Identifier: (GPL-2.0 OR MIT) */
/ {
	images {
<<<<<<< HEAD
		fdt-luton_pcb091 {
=======
		fdt@luton_pcb091 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MSCC Luton PCB091 Device Tree";
			data = /incbin/("boot/dts/mscc/luton_pcb091.dtb");
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
		pcb091 {
			description = "Luton Linux kernel";
<<<<<<< HEAD
			kernel = "kernel";
			fdt = "fdt-luton_pcb091";
=======
			kernel = "kernel@0";
			fdt = "fdt@luton_pcb091";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		};
	};
};
