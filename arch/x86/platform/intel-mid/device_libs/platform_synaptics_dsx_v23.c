/*
 * platform_synaptics_dsx.c: synaptics_dsx platform data initilization file
 */

#include <linux/input.h>
#include <linux/gpio.h>
#include <linux/lnw_gpio.h>
#include <asm/intel-mid.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <asm/intel_scu_flis.h>

#include "platform_synaptics_dsx_v23.h"
#define TM1940 (1) /* I2C */
#define TM2448 (2) /* I2C */
#define TM2074 (3) /* SPI */
#define TM2780 (4) /* HID/I2C (RMI mode) */
#define SYNAPTICS_MODULE TM2448

/* Synaptics changes for Panda Board */
#if (SYNAPTICS_MODULE == TM2448)
#define SYNAPTICS_I2C_DEVICE
#define DSX_I2C_ADDR 0x20
#define DSX_ATTN_GPIO 62
#define DSX_ATTN_MUX_NAME "ts_int"
#define DSX_POWER_GPIO -1
#define DSX_POWER_MUX_NAME ""
#define DSX_POWER_ON_STATE 1
#define DSX_POWER_DELAY_MS 160
#define DSX_RESET_GPIO -1
#define DSX_RESET_ON_STATE 0
#define DSX_RESET_DELAY_MS 100
#define DSX_RESET_ACTIVE_MS 20
#define DSX_IRQ_ON_STATE 0
#define DSX_IRQ_FLAGS (IRQF_TRIGGER_FALLING | IRQF_ONESHOT)
#define DSX_MAX_Y_FOR_2D 800 /* set to -1 if no virtual buttons */
static unsigned char pwr_reg_name[] = "";
static unsigned char bus_reg_name[] = "";
static unsigned int cap_button_codes[] =
		{};
static unsigned int vir_button_codes[] =
		{};

#elif (SYNAPTICS_MODULE == TM1940)
#define SYNAPTICS_I2C_DEVICE
#define DSX_I2C_ADDR 0x20
#define DSX_ATTN_GPIO 39
#define DSX_ATTN_MUX_NAME "gpmc_ad15.gpio_39"
#define DSX_POWER_GPIO -1
#define DSX_POWER_ON_STATE 1
#define DSX_POWER_DELAY_MS 160
#define DSX_RESET_GPIO -1
#define DSX_RESET_ON_STATE 0
#define DSX_RESET_DELAY_MS 100
#define DSX_RESET_ACTIVE_MS 20
#define DSX_IRQ_ON_STATE 0
#define DSX_IRQ_FLAGS (IRQF_TRIGGER_FALLING | IRQF_ONESHOT)
static unsigned char pwr_reg_name[] = "";
static unsigned char bus_reg_name[] = "";
static unsigned int cap_button_codes[] =
		{KEY_MENU, KEY_HOME, KEY_BACK, KEY_SEARCH};
static unsigned int vir_button_codes[] =
		{};

#elif (SYNAPTICS_MODULE == TM2074)
#define SYNAPTICS_SPI_DEVICE
#define DSX_SPI_BUS 1
#define DSX_SPI_CS 0
#define DSX_SPI_CS_MUX_NAME "mcspi1_cs0"
#define DSX_SPI_MAX_SPEED (8 * 1000 * 1000)
#define DSX_SPI_BYTE_DELAY_US 20
#define DSX_SPI_BLOCK_DELAY_US 20
#define DSX_ATTN_GPIO 39
#define DSX_ATTN_MUX_NAME "gpmc_ad15.gpio_39"
#define DSX_POWER_GPIO 140
#define DSX_POWER_MUX_NAME "mcspi1_cs3.gpio_140"
#define DSX_POWER_ON_STATE 1
#define DSX_POWER_DELAY_MS 160
#define DSX_RESET_GPIO -1
#define DSX_RESET_ON_STATE 0
#define DSX_RESET_DELAY_MS 100
#define DSX_RESET_ACTIVE_MS 20
#define DSX_IRQ_ON_STATE 0
#define DSX_IRQ_FLAGS IRQF_TRIGGER_FALLING
#define DSX_MAX_Y_FOR_2D -1
static unsigned char pwr_reg_name[] = "";
static unsigned char bus_reg_name[] = "";
static unsigned int cap_button_codes[] =
		{};
static unsigned int vir_button_codes[] =
		{};

#elif (SYNAPTICS_MODULE == TM2780)
#define SYNAPTICS_I2C_DEVICE
#define SYNAPTICS_HID_DEVICE
#define DSX_HID_DEVICE_DESCRIPTOR_ADDR 0x0020
#define DSX_I2C_ADDR 0x2c
#define DSX_ATTN_GPIO 39
#define DSX_ATTN_MUX_NAME "gpmc_ad15.gpio_39"
#define DSX_POWER_GPIO 140
#define DSX_POWER_MUX_NAME "mcspi1_cs3.gpio_140"
#define DSX_POWER_ON_STATE 1
#define DSX_POWER_DELAY_MS 160
#define DSX_RESET_GPIO -1
#define DSX_RESET_ON_STATE 0
#define DSX_RESET_DELAY_MS 100
#define DSX_RESET_ACTIVE_MS 20
#define DSX_IRQ_ON_STATE 0
#define DSX_IRQ_FLAGS (IRQF_TRIGGER_FALLING | IRQF_ONESHOT)
#define DSX_MAX_Y_FOR_2D -1
static unsigned char pwr_reg_name[] = "";
static unsigned char bus_reg_name[] = "";
static unsigned int cap_button_codes[] =
		{};
static unsigned int vir_button_codes[] =
		{};
#endif

static struct synaptics_dsx_button_map cap_button_map = {
	.nbuttons = ARRAY_SIZE(cap_button_codes),
	.map = cap_button_codes,
};

static struct synaptics_dsx_button_map vir_button_map = {
	.nbuttons = ARRAY_SIZE(vir_button_codes) / 5,
	.map = vir_button_codes,
};

static struct synaptics_dsx_board_data dsx_board_data = {
	.irq_gpio = DSX_ATTN_GPIO,
	.irq_on_state = DSX_IRQ_ON_STATE,
	.irq_flags = DSX_IRQ_FLAGS,
	.power_gpio = DSX_POWER_GPIO,
	.power_on_state = DSX_POWER_ON_STATE,
	.power_delay_ms = DSX_POWER_DELAY_MS,
	.reset_gpio = DSX_RESET_GPIO,
	.reset_on_state = DSX_RESET_ON_STATE,
	.reset_delay_ms = DSX_RESET_DELAY_MS,
	.reset_active_ms = DSX_RESET_ACTIVE_MS,
	.max_y_for_2d = DSX_MAX_Y_FOR_2D,
	.pwr_reg_name = pwr_reg_name,
	.bus_reg_name = bus_reg_name,
	.cap_button_map = &cap_button_map,
	.vir_button_map = &vir_button_map,
#ifdef SYNAPTICS_SPI_DEVICE
	.byte_delay_us = DSX_SPI_BYTE_DELAY_US,
	.block_delay_us = DSX_SPI_BLOCK_DELAY_US,
#endif
#ifdef SYNAPTICS_HID_DEVICE
	.device_descriptor_addr = DSX_HID_DEVICE_DESCRIPTOR_ADDR,
#endif
};

#ifdef SYNAPTICS_I2C_DEVICE
static struct i2c_board_info bus0_i2c_devices[] = {
	{
		I2C_BOARD_INFO(I2C_DRIVER_NAME, DSX_I2C_ADDR),
		.platform_data = &dsx_board_data,
	},
};
//static struct spi_board_info spi_devices[] = {};
#endif

#ifdef SYNAPTICS_SPI_DEVICE
static struct spi_board_info spi_devices[] = {
	{
		.modalias = SPI_DRIVER_NAME,
		.bus_num = DSX_SPI_BUS,
		.chip_select = DSX_SPI_CS,
		.mode = SPI_MODE_3,
		.max_speed_hz = DSX_SPI_MAX_SPEED,
		.platform_data = &dsx_board_data,
	},
};
//static struct i2c_board_info bus4_i2c_devices[] = {};
#endif

void get_dsx_platformdata(void *info)
{
	return dsx_board_data;
}

static void synaptics_gpio_init(void)
{
/*
#ifdef DSX_ATTN_MUX_NAME
	omap_mux_init_signal(DSX_ATTN_MUX_NAME, OMAP_PIN_INPUT_PULLUP);
#endif
#ifdef DSX_POWER_MUX_NAME
	omap_mux_init_signal(DSX_POWER_MUX_NAME, OMAP_PIN_OUTPUT);
#endif
#ifdef DSX_RESET_MUX_NAME
	omap_mux_init_signal(DSX_RESET_MUX_NAME, OMAP_PIN_OUTPUT);
#endif
#ifdef SYNAPTICS_SPI_DEVICE
	omap_mux_init_signal(DSX_SPI_CS_MUX_NAME, OMAP_PIN_OUTPUT);
	omap_mux_init_signal("mcspi1_clk", OMAP_PIN_INPUT);
	omap_mux_init_signal("mcspi1_somi", OMAP_PIN_INPUT_PULLUP);
	omap_mux_init_signal("mcspi1_simo", OMAP_PIN_OUTPUT);
#endif
*/
	return;
}
/* End of Synaptics changes for Panda Board */

static int __init synaptics_dsx_i2c_init(void)
{
	int ret;

	ret = i2c_register_board_info(0, &bus0_i2c_devices, 1);
	printk("[%s]i2c_register_board_info : %d \n",__func__ ,ret);

	return ret;
}

module_init(synaptics_dsx_i2c_init);

