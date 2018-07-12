













static void __init qin2440_init_machine(void)
{
	/**
	 * TODO 
	 * 12MHZ的晶振先不写
	 * 机器码的问题要怎么解决？
	 */
	
	qin2440_gpio_init();
	platform_device_register(uart0_device);
	platform_device_register(nand_device);



}

MACHINE_START(QIN, "qin2440")
	.boot_params  = 0x30000000 + 0x100;
	.timer        = &qin2440_tick;
	.map_io       = qin2440_map;
	.init_irq     = qin2440_init_irq;
	.init_machine = qin2440_init_machine;
MACHINE_END

