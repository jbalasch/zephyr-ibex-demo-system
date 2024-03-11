/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/irq.h>

/* Register offsets within the UART device register space. */
#define UART_RX_REG 0
#define UART_TX_REG 4
#define UART_STATUS_REG 8

/* Status register bits. */
#define UART_STATUS_RX_EMPTY 1
#define UART_STATUS_TX_FULL 2

#define DT_DRV_COMPAT lowrisc_ibex_uart

struct uart_ibex_config {
	mem_addr_t base;
	uint32_t nco_reg;
};

static int uart_ibex_init(const struct device *dev)
{
	return 0;
}

static int uart_ibex_poll_in(const struct device *dev, unsigned char *c)
{
	const struct uart_ibex_config *cfg = dev->config;

	if (!(sys_read32(cfg->base + UART_STATUS_REG) & UART_STATUS_RX_EMPTY)) {
	    /* Empty RX FIFO */
		return -1;
	}
	*c = sys_read32(cfg->base + UART_RX_REG);
	return 0;
}

static void uart_ibex_poll_out(const struct device *dev, unsigned char c)
{
	const struct uart_ibex_config *cfg = dev->config;

	/* Wait for space in the TX FIFO */
	while (sys_read32(cfg->base + UART_STATUS_REG) &
		UART_STATUS_TX_FULL) {
		;
	}

	sys_write32(c, cfg->base + UART_TX_REG);
}

static const struct uart_driver_api uart_ibex_driver_api = {
	.poll_in = uart_ibex_poll_in,
	.poll_out = uart_ibex_poll_out,
};

#define UART_IBEX_INIT(n) \
	static struct uart_ibex_config uart_ibex_config_##n = \
	{ \
		.base = DT_INST_REG_ADDR(n), \
	}; \
	\
	DEVICE_DT_INST_DEFINE(n, uart_ibex_init, NULL, NULL, \
				&uart_ibex_config_##n, \
				PRE_KERNEL_1, CONFIG_SERIAL_INIT_PRIORITY, \
				&uart_ibex_driver_api);

DT_INST_FOREACH_STATUS_OKAY(UART_IBEX_INIT)
