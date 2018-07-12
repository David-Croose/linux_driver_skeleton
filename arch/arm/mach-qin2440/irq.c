/**
 * TODO
 * �����˸�get_irqnr_and_base�������ҵ��жϺ��ǴӰ���2440�ֲ����ģ����Ĳ���
 * �����˻��д����ж�
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
	 * �����EINT�жϣ���Ҫ���EINT�жϹ���Ĵ���
	 * ����жϻ������жϣ���Ҫ������жϹ���Ĵ���
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
	// uart0��Ȼ���ա������������жϣ��������ﲻ����chain handler�ˣ���Ϊ�һ���
	// �������ж��ﴦ����Щ����
	irq_set_chip_and_handler(28, &qin2440_irq_chip, handle_level_irq);
	set_irq_flags(28, IRQF_VALID);
}
