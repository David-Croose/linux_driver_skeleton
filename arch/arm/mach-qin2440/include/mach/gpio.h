/* ���øģ�����__��ͷ�Ķ��Ǵӿ��������� */
#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep

/* GPIO��ź��жϺŵ�ת��������ֻ����ʱ��ôд */
#define gpio_to_irq(gpio) (gpio)
#define irq_to_gpio(irq)  (irq)