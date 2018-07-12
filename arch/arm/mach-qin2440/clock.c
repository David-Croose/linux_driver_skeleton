
/**
TODO
时钟的驱动应该可以写的更简单，应该只需要两句就够了：
periphral_clock_enable和periphral_clock_disable，把
这两个函数插入到别的驱动里就行了
*/



static LIST_HEAD(clocks);
static DEFINE_SPINLOCK(clk_lock);

static void periphral_clock_enable(unsigned int id)
{

}

static void periphral_clock_disable(unsigned int id)
{

}

static struct clk fclk = {
	.name = "fclk",
	.type = QIN2440_SYS_CLK,
	.rate = 400000000,
};

static struct clk hclk = {
	.name = "hclk",
	.type = QIN2440_SYS_CLK,
	.rate = 100000000,
};

static struct clk pclk = {
	.name = "pclk",
	.type = QIN2440_SYS_CLK,
	.rate = 50000000,
};

static struct clk clk_periph[] = {
	{
		.name    = "uart0_clk",
		.type    = QIN2440_PRIPH_CLK,
		.id      = 10,
		.parent  = &pclk,
		.enable  = periphral_clock_enable,
		.disable = periphral_clock_disable,
	}, {
		.name    = "nand_clk",
		.type    = QIN2440_PRIPH_CLK,
		.id      = 4,
		.parent  = &hclk,
		.enable  = periphral_clock_enable,
		.disable = periphral_clock_disable,
	}, {
		.name    = "timer0_clk",
		.type    = QIN2440_PERPH_CLK,
		.id      = 8,
		.parent  = &pclk,
		.enable  = periphral_clock_enable,
		.disable = periphral_clock_disable,
	}
};

void clock_register(struct clk *clk)
{
	unsigned long flags;

	spin_lock_irqsave(&clk_lock, flags);
	list_add_tail(&clk->node, &clock);
	spin_unlock_irqrestore(&clk_lock, flags);
}

void clock_enable(struct clk *clk)
{
	unsigned long flags;

	spin_lock_irqsave(&clk_lock, flags);
	clk->enable(clk->id);
	spin_unlock_irqrestore(&clk_lock, flags);
	return 0;
}

void clock_disable(struct clk *clk)
{
	unsigned long flags;

	spin_lock_irqsave(&clk_lock, flags);
	clk->disable(clk->id);
	spin_unlock_irqrestore(&clk_lock, flags);
}

struct clk *ckl_get(const char *name)
{
	unsigned long flags;
	struct clk *clk;

	spin_lock_irqsave(&clk_lock, flags);

	list_for_each_entry(clk, &clocks, node) {
		if(strcmp(name, clk->name) == 0) {
			return clk;
		}
	}

	spin_unlock_irqrestore(&clk_lock, flags);
	return NULL;
}

void clk_put(struct clk *clk)
{
	// nothing to do
	return;
}

unsigned int clk_get_rate(struct clk *clk)
{
	unsigned long flags;
	unsigned int rate;

	spin_lock_irqsave(&clk_lock, flags);
	rate = clk->parent->rate;
	spin_unlock_irqrestore(&clk_lock, flags);

	return rate;
}

