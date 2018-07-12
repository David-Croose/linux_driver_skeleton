/******************************************************************

	the led

******************************************************************/








/******************************************************************

	the button

******************************************************************/









/******************************************************************

	the uart0

******************************************************************/
static struct resource uart0_resource {
	[0] = {
		.start	= ,
		.end	= ,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= ,
		.end	= ,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device __initdata uart0_device {
	.name = "qin2440_uart0",
	.id = 0,
	.resource = uart0_resource,
	.num_resources = ARRAY_SIZE(uart0_resource),
};



/******************************************************************

	the nand flash

******************************************************************/
static struct resource nand_resource {
	[0] = {
		.start	= ,
		.end	= ,
		.flags	= IORESOURCE_MEM,
	},
};

struct platform_device __initdata nand_device {
	.name = "qin2440_nand",
	.id = 0,
	.resource = nand_resource,
	.num_resources = ARRAY_SIZE(nand_resource),
};