/**
 * TODO
 * 别忘了改get_irqnr_and_base函数，我的中断号是从按照2440手册来的，它的不是
 * 别忘了还有串口中断
 */


static void qin2440_ack_irq(struct irq_data *d)
{
	unsigned int tmp;
	unsigned int irq = d->irq;
	
	tmp = readl(SRCPND);
	tmp |= (1 << irq);
	writel(tmp, SRCPND);
	
	tmp = readl(INTPND);
	tmp |= (1 << irq);
	writel(tmp, INTPND);
	
	/**
	 * TODO
	 * 如果是EINT中断，还要清除EINT中断挂起寄存器
	 * 如果中断还有子中断，还要清除子中断挂起寄存器
	 */
	if(irq == 28) {
		tmp = readl(SUBSRCPND);
		if(tmp & 0x7) {
			tmp = tmp & 0x7;
		}
	}
}

static void qin2440_mask_irq(struct irq_data *d)
{
	unsigned int tmp;
	unsigned int irq = d->irq;
	
	tmp = readl(INTMSK);
	tmp |= (1 << irq);
	writel(tmp, INTMSK);
}

static void qin2440_unmask_irq(struct irq_data *d)
{
	unsigned int tmp;
	unsigned int irq = d->irq;
	
	tmp = readl(INTMSK);
	tmp &= ~(1 << irq);
	writel(tmp, INTMSK);
}

static struct irq_chip qin2440_irq_chip = {
	.name		= "qin2440 tick",
	.irq_ack	= qin2440_ack_irq,
	.irq_mask	= qin2440_mask_irq,
	.irq_unmask	= qin2440_unmask_irq,
};

void __init qin2440_init_irq(void)
{
	// timer4's irq number=14
	irq_set_chip_and_handler(14, &qin2440_irq_chip, handle_level_irq);
	set_irq_flags(14, IRQF_VALID);
	
	// uart0's irq number=28
	// uart0虽然有收、发、错误子中断，但是这里不设置chain handler了，因为我会在
	// 它的总中断里处理这些东西
	irq_set_chip_and_handler(28, &qin2440_irq_chip, handle_level_irq);
	set_irq_flags(28, IRQF_VALID);
}
