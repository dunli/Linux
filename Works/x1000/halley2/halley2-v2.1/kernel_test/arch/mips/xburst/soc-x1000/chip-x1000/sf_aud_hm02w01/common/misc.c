#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>
#include <linux/leds.h>
//#include <linux/tsc.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_gpio.h>
//#include <linux/android_pmem.h>
#include <mach/platform.h>
#include <mach/jzsnd.h>
#include <mach/jzmmc.h>
#include <mach/jzssi.h>
#include <mach/jz_efuse.h>
#include <gpio.h>
#include <linux/jz_dwc.h>
#include <linux/interrupt.h>
//#include <sound/jz-aic.h>
#include "board_base.h"

#ifdef CONFIG_LEDS_GPIO
#include <linux/leds.h>
#endif

#ifdef CONFIG_LEDS_GPIO
static struct gpio_led gpio_leds[] = {
#ifndef CONFIG_LCD_CLASS_DEVICE
        {
                .name = "wifi",
                .gpio = GPIO_PA(1),
                .active_low = true,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
                .retain_state_suspended = true,
                .default_trigger = "default_on",
        },
        {
                .name = "usb",
                .gpio = GPIO_PA(3),
                .active_low = true,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
                .retain_state_suspended = true,
                .default_trigger = "default_on",
        },
#endif
        {
                .name = "aux",
                .gpio = GPIO_PA(0),
                .active_low = true,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
                .retain_state_suspended = true,
                .default_trigger = "default_on",
        },
        {
                .name = "sd-card",
                .gpio = GPIO_PA(2),
                .active_low = true,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
                .retain_state_suspended = true,
                .default_trigger = "default_on",
        },
};

static struct gpio_led_platform_data gpio_led_info = {
        .leds = gpio_leds,
        .num_leds = ARRAY_SIZE(gpio_leds),
};

struct platform_device jz_leds_gpio = {
        .name = "leds-gpio",
        .id = -1,
        .dev = {
                .platform_data  = &gpio_led_info,
        },
};
#endif

#ifdef CONFIG_JZ_EFUSE_V11
struct jz_efuse_platform_data jz_efuse_pdata = {
            /* supply 2.5V to VDDQ */
            .gpio_vddq_en_n = GPIO_EFUSE_VDDQ,
};
#endif

#ifdef CONFIG_JZ_EFUSE_V13
struct jz_efuse_platform_data jz_efuse_pdata = {
	/* supply 2.5V to VDDQ */
	.gpio_vddq_en_n = GPIO_EFUSE_VDDQ,
};
#endif

#if defined(GPIO_USB_ID) && defined(GPIO_USB_ID_LEVEL)
struct jzdwc_pin dwc2_id_pin = {
	    .num = GPIO_USB_ID,
		    .enable_level = GPIO_USB_ID_LEVEL,
};
#endif


#if defined(GPIO_USB_DETE) && defined(GPIO_USB_DETE_LEVEL)
struct jzdwc_pin dwc2_dete_pin = {
	.num = GPIO_USB_DETE,
	.enable_level = GPIO_USB_DETE_LEVEL,
};
#endif


#if defined(GPIO_USB_DRVVBUS) && defined(GPIO_USB_DRVVBUS_LEVEL) && !defined(USB_DWC2_DRVVBUS_FUNCTION_PIN)
struct jzdwc_pin dwc2_drvvbus_pin = {
	    .num = GPIO_USB_DRVVBUS,
		    .enable_level = GPIO_USB_DRVVBUS_LEVEL,
};
#endif
