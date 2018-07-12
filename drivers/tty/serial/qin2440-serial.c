#define QIN2440_UART_TYPE    10

static void qin2440_uart_tx_char(struct uart_port *port)
{
	struct circ_buf *xmit = port->state->xmit;

	if(port->x_char) {
		
		writeb(port->x_char, port->membase + /* 发送寄存器的相对偏移 */);
		port->x_char = 0;
		port->icount.tx++;
		return;
	}

	while(readb(port->membase + MCFUART_USR) & MCFUART_USR_TXREADY) {
		if(xmit->head == xmit->tail) {
			break;
		}
		writeb(xmit->buf[xmit->tail], port->membase + /* 发送寄存器的相对偏移 */);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE -1);
		port->icount.tx++;
	}

	// 固定格式
	if(uart_circ_chars_pending(xmit) < WAKEUP_CHARS) {
		uart_write_wakeup(port);
	}

	if(xmit->head == xmit->tail) {
		qin2440_uart_stop_tx(port);
	}
}

static void qin2440_uart_rx_char(struct uart_port *port)
{
	unsigned char status, ch, flag;

	while ((status = readb(port->membase + /* 串口中断状态寄存器的相对偏移 */)) & /* 接收中断的bit */) {
		ch = readb(port->membase + /* 串口接收数据寄存器 */);
		flag = TTY_NORMAL;
		port->icount.rx++;

		// 这个大if应该是可以删掉的，除了清除中断标志位的部分
		if(status & MCFUART_USR_RXERR) {
			/* 清除中断标志位 */

			if(status & /* break信号的bit */) {
				port->icount.brk++;
				if(uart_handle_break(port)) {
					continue;
				}
			} else if(status & /* 校验信号的bit */) {
				port->icount.parity++;
			} else if(status & /* 接收溢出的bit */) {
				port->icount.overrun++;
			} else if(status & /* 接收帧中断的bit */) {
				port->icount.frame++;
			}

			status &= port->read_status_mask;

			if(status & MCFUART_USR_RXBREAK) {
				flag = TTY_BREAK;
			} else if(status & MCFUART_USR_RXPARITY) {
				flag = TTY_PARITY;
			} else if(status & MCFUART_USR_RXFRAMING) {
				flag = TTY_FRAME;
			}
		}

		// 固定格式
		if(uart_handle_sysrq_char(port, ch)) {
			continue;
		}
		uart_insert_char(port, status, /* 串口接收溢出bit */, ch, flag);
	}

	tty_flip_buffer_push(port->state->port.tty);
}

static irqreturn_t qin2440_uart_interrupt(int irq, void *data)
{
	struct uart_port *port = data;
	irqreturn_t ret = IRQ_NONE;
	
	spin_lock(&port->lock);
	if(/* 如果是发送中断 */) {
		qin2440_uart_tx_char(port);
		ret = IRQ_HANDLED;
	}
	if(/* 如果是接收中断 */) {
		qin2440_uart_rx_char(port);
		ret = IRQ_HANDLED;
	}
	spin_unlock(&port->lock);
	return ret;
}

static unsigned int qin2440_uart_tx_empty(struct uart_port *port)
{
	return 0;
}

static void qin2440_uart_start_tx(struct uart_port *port)
{

}

static void qin2440_uart_stop_tx(struct uart_port *port)
{

}

static void qin2440_uart_stop_rx(struct uart_port *port)
{

}

static void qin2440_uart_break_ctl(struct uart_port *port, int break_state)
{

}

static int qin2440_uart_startup(struct uart_port *port)
{

}

static void qin2440_uart_shutdown(struct uart_port *port)
{

}

static void qin2440_uart_set_termios(struct uart_port *port, struct ktermios *termios,
									 struct ktermios *old)
{

}

static const char *qin2440_uart_type(struct uart_port *port)
{
	return (port->type == QIN2440_UART_TYPE) ? "QIN2440 UART" : NULL;
}

static void qin2440_uart_config_port(struct uart_port *port, int flags)
{
	if(request_irq(port->irq, qin2440_uart_interrupt, IRQF_DISABLED, "UART", port)) {
		printk(KERN_ERR "uart request_irq failed\n");
	}
}

static struct uart_driver qin2440_uart_driver = {
	.owner       = THIS_MODULE,
	.driver_name = "qin2440 serial",
	.dev_name    = "ttyS",
	.major       = TTY_MAJOR,
	.minor       = 64,
	.nr          = 1,
	.cons        = PXA_CONSOLE,
};

struct uart_ops qin2440_uart_ops = {
	.tx_empty	  = qin2440_uart_tx_empty,
	.set_mctrl	  = NULL,
	.get_mctrl	  = NULL,
	.stop_tx	  = qin2440_uart_stop_tx,
	.start_tx	  = qin2440_uart_start_tx,
	.stop_rx	  = qin2440_uart_stop_rx,
	.enable_ms	  = NULL,
	.break_ctl	  = qin2440_uart_break_ctl,
	.startup	  = qin2440_uart_startup,
	.shutdown	  = qin2440_uart_shutdown,
	.set_termios  = qin2440_uart_set_termios,
	.pm           = NULL,
	.type         = qin2440_uart_type,
	.release_port = NULL,
	.request_port = NULL,
	.config_port  = qin2440_uart_config_port,
	.verify_port  = NULL,
};

static int serial_qin2440_probe(struct platform_device *dev)
{
	struct uart_port *port;
	
	port->line = 0;
	port->type = QIN2440_UART_TYPE;
	port->mapbase = ;
	port->membase = ;
	port->iotype = SERIAL_IO_MEM;
	port->irq = 28;
	port->uartclk = 50000000;
	port->ops = &qin2440_uart_ops;
	port->flags = ASYNC_BOOT_AUTOCONF;
	port->fifosize = 64;

	uart_add_one_port(&qin2440_uart_driver, port);
	platform_set_drvdata(dev, port);

	return 0;
}

static int serial_qin2440_remove(struct platform_device *dev)
{
	struct uart_port *port = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);
	uart_remove_one_port(&qin2440_uart_driver, port);
	return 0;
}

static struct platform_driver serial_qin2440_driver = {
	.probe  = serial_qin2440_probe,
	.remove = __devexit_p(serial_qin2440_remove),

	.driver = {
		.name	= "qin2440_uart0",
		.owner	= THIS_MODULE,
	},
};

int __init serial_qin2440_init(void)
{
	int ret;

	ret = uart_register_driver(&qin2440_uart_driver);
	if(ret != 0) {
		return ret;
	}

	ret = platform_driver_register(&serial_qin2440_driver);
	if(ret != 0) {
		uart_unregister_driver(&qin2440_uart_driver);
	}

	return ret;
}

void __exit serial_qin2440_exit(void)
{
	platform_driver_unregister(&serial_qin2440_driver);
	uart_unregister_driver(&qin2440_uart_driver);
}

module_init(serial_qin2440_init);
module_exit(serial_qin2440_exit);
MODULE_LICENSE("GPL");
