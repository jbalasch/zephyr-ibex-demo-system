/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/arch/cpu.h>
#include <zephyr/devicetree.h>
#include <zephyr/init.h>

/* Ibex timer registers. */
#define RV_TIMER_BASE (DT_REG_ADDR(DT_NODELABEL(mtimer)))
#define TIMER_MTIME_REG_OFFSET         0x0
#define TIMER_MTIMEH_REG_OFFSET        0x4
#define TIMER_MTIMECMP_REG_OFFSET      0x8
#define TIMER_MTIMECMPH_REG_OFFSET     0xC

static int soc_ibex_init(void)
{
	/* Turn on LEDs */
	sys_write32(0xFFFF, 0x80000000);

	return 0;
}
SYS_INIT(soc_ibex_init, PRE_KERNEL_1, 0);
