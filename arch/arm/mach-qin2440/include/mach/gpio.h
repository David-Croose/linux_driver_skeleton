/* 不用改，后面__开头的都是从库里面来的 */
#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep

/* GPIO编号和中断号的转换，这里只是暂时这么写 */
#define gpio_to_irq(gpio) (gpio)
#define irq_to_gpio(irq)  (irq)