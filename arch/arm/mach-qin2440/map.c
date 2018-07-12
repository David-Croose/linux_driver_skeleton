static struct map_desc qin2440_iodesc[] = {
	{
		.virtual = 
		.pfn     =
		.length  =
		.type    =
	}, {



	}




};

void __init qin2440_map(void)
{
	iotable_init(qin2440_iodesc, ARRAY_SIZE(qin2440_iodesc));
}