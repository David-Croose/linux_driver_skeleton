#ifndef _QIN2440_CLOCK_H_
#define _QIN2440_CLOCK_H_

struct clk {
	struct list_head node;
	const char *name;
	struct clk *parent;

#define QIN2440_SYS_CLK 1
#define QIN2440_PRIPH_CLK 2
	unsigned int type;

	unsigned int id;
	unsigned int rate;
	void (*enable)(unsigned int id);
	void (*disable)(unsigned int id);
};


#endif

