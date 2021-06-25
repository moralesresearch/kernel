/ {
	images {
<<<<<<< HEAD
		fdt-xilfpga {
=======
		fdt@xilfpga {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "MIPSfpga (xilfpga) Device Tree";
			data = /incbin/("boot/dts/xilfpga/nexys4ddr.dtb");
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
		conf-xilfpga {
			description = "MIPSfpga Linux kernel";
			kernel = "kernel";
			fdt = "fdt-xilfpga";
=======
		conf@xilfpga {
			description = "MIPSfpga Linux kernel";
			kernel = "kernel@0";
			fdt = "fdt@xilfpga";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		};
	};
};
