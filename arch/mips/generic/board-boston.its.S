/ {
	images {
<<<<<<< HEAD
		fdt-boston {
=======
		fdt@boston {
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			description = "img,boston Device Tree";
			data = /incbin/("boot/dts/img/boston.dtb");
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
		conf-boston {
			description = "Boston Linux kernel";
			kernel = "kernel";
			fdt = "fdt-boston";
=======
		conf@boston {
			description = "Boston Linux kernel";
			kernel = "kernel@0";
			fdt = "fdt@boston";
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		};
	};
};
