/**
 * HZ = 1000, CLOCK_TICK_RATE = 25000, LATCH = CLOCK_TICK_RATE / HZ = 25
 * timer4的时基是40uS，要做到1mS中断一次，自动重装载寄存器就应该等于25
 */
#define CLOCK_TICK_RATE    (50000000 / 8 / 250)