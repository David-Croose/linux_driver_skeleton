

static void s3c2440_timer4_init(unsigned int latch)
{
	
	
}

static void s3c2440_timer4_enable(void)
{
	
	
}



static irqreturn_t qin2440_tick_interrupt(int irq, void *dev_id)
{
	timer_tick();
	return IRQ_HANDLED;
}

static struct irqaction qin2440_tick_irq = {
	.name		= "qin2440 tick",
	.flags		= IRQF_DISABLED | IRQF_TIMER,
	.handler	= qin2440_tick_interrupt,
};



void __init qin2440_tick_init(void)
{
	setup_irq(14, &qin2440_tick_irq);
	s3c2440_timer4_init(LATCH);
	s3c2440_timer4_enable();
}



struct sys_timer qin2440_tick = {
	.init = qin2440_tick_init,
};
