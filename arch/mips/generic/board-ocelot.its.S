/* SPDX-License-Identifier: (GPL-2.0 OR MIT) */
/ {
	images {
<<<<<<< HEAD
		fdt-ocelot_pcb123 {
=======
		fdt@ocelot_pcb123 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MSCC Ocelot PCB123 Device Tree";
			data = /incbin/("boot/dts/mscc/ocelot_pcb123.dtb");
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

<<<<<<< HEAD
		fdt-ocelot_pcb120 {
=======
		fdt@ocelot_pcb120 {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MSCC Ocelot PCB120 Device Tree";
			data = /incbin/("boot/dts/mscc/ocelot_pcb120.dtb");
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
<<<<<<< HEAD
		conf-ocelot_pcb123 {
			description = "Ocelot Linux kernel";
			kernel = "kernel";
			fdt = "fdt-ocelot_pcb123";
		};

		conf-ocelot_pcb120 {
			description = "Ocelot Linux kernel";
			kernel = "kernel";
			fdt = "fdt-ocelot_pcb120";
=======
		conf@ocelot_pcb123 {
			description = "Ocelot Linux kernel";
			kernel = "kernel@0";
			fdt = "fdt@ocelot_pcb123";
		};

		conf@ocelot_pcb120 {
			description = "Ocelot Linux kernel";
			kernel = "kernel@0";
			fdt = "fdt@ocelot_pcb120";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		};
	};
};
