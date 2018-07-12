

static void qin2440_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{

}

static int qin2440_gpio_get(struct gpio_chip *chip, unsigned offset)
{

	retrun 0;
}

static int qin2440_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{

	return 0;
}

static int qin2440_gpio_direction_output(struct gpio_chip *chip, unsigned offset,
					int value)
{

	return 0;
}

static struct gpio_chip qin2440_gpio_chip = {
	.label			  = "qin2440 gpio",
	.direction_input  = qin2440_gpio_direction_input,
	.get			  = qin2440_gpio_get,
	.direction_output = qin2440_gpio_direction_output,
	.set			  = qin2440_gpio_set,
	.base			  = 0,
	.ngpio			  = 1
};

void __init qin2440_gpio_init(void)
{
	gpiochip_add(&qin2440_gpio_chip);
}
