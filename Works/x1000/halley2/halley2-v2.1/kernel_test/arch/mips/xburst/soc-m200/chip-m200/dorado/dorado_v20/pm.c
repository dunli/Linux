#include <gpio.h>
__initdata int gpio_ss_table[][2] = {
	{32*0+0,	GSS_INPUT_PULL		},	/* BT_WAKE_HOST */
	{32*0+1,	GSS_INPUT_PULL		},	/* HOST_WAKE_BT */
	{32*0+2,	GSS_OUTPUT_LOW		},	/* BT_REG_EN */
	{32*0+3,	GSS_INPUT_NOPULL	},	/* PMU_IRQ_N */
	{32*0+4,	GSS_INPUT_NOPULL	},	/* MSC0_D4 */
	{32*0+5,	GSS_INPUT_NOPULL	},	/* MSC0_D5 */
	{32*0+6,	GSS_INPUT_NOPULL	},	/* MSC0_D6 */
	{32*0+7,	GSS_INPUT_NOPULL	},	/* MSC0_D7 */
	{32*0+8,	GSS_OUTPUT_LOW		},	/* WL_REG_EN */
	{32*0+9,	GSS_INPUT_NOPULL		},	/* WL_WAKE_HOST */
	{32*0+10,	GSS_INPUT_NOPULL		},	/* HOST_WAKE_WL */
	{32*0+11,	GSS_INPUT_NOPULL	},	/* HOST_WAKE_NFC */
	{32*0+12,	GSS_OUTPUT_LOW		},	/* SHUTDOWN_N */
	{32*0+13,	GSS_INPUT_NOPULL	},	/* USB_ID */
	{32*0+14,	GSS_INPUT_NOPULL	},	/* USB_DETE */
	{32*0+15,	GSS_INPUT_NOPULL	},	/* SENSOR_INT */
	{32*0+18,	GSS_INPUT_PULL		},	/* MSC0_CLK */
	{32*0+19,	GSS_INPUT_NOPULL	},	/* MSC0_CMD */
	{32*0+20,	GSS_INPUT_NOPULL	},	/* MSC0_D0 */
	{32*0+21,	GSS_INPUT_NOPULL	},	/* MSC0_D1 */
	{32*0+22,	GSS_INPUT_NOPULL	},	/* MSC0_D2 */
	{32*0+23,	GSS_INPUT_NOPULL	},	/* MSC0_D3 */
	{32*0+29,	GSS_INPUT_NOPULL	},	/* MSC_RST_N */
	{32*1+0,	GSS_INPUT_PULL	},	/* LCD_INT */
	{32*1+1,	GSS_IGNORE	},	/* SLEEP */
	{32*1+7,	GSS_INPUT_PULL	},	/* ISP_SDA */
	{32*1+8,	GSS_INPUT_PULL	},	/* ISP_SCK */
	{32*2+2,	GSS_INPUT_PULL		},	/* LCD_B2 */
	{32*2+3,	GSS_INPUT_PULL		},	/* LCD_B3 */
	{32*2+4,	GSS_INPUT_PULL		},	/* LCD_B4 */
	{32*2+5,	GSS_INPUT_PULL		},	/* LCD_B5 */
	{32*2+6,	GSS_INPUT_PULL		},	/* LCD_B6 */
	{32*2+7,	GSS_INPUT_PULL		},	/* LCD_B7 */
	{32*2+8,	GSS_INPUT_PULL		},	/* LCD_PCLK */
	{32*2+9,	GSS_INPUT_PULL		},	/* LCD_DE */
	{32*2+12,	GSS_INPUT_PULL		},	/* LCD_G2 */
	{32*2+13,	GSS_INPUT_PULL		},	/* LCD_G3 */
	{32*2+14,	GSS_INPUT_PULL		},	/* LCD_G4 */
	{32*2+15,	GSS_INPUT_PULL		},	/* LCD_G5 */
	{32*2+16,	GSS_INPUT_PULL		},	/* LCD_G6 */
	{32*2+17,	GSS_INPUT_PULL		},	/* LCD_G7 */
	{32*2+18,	GSS_INPUT_PULL		},	/* LCD_HSYN */
	{32*2+19,	GSS_INPUT_PULL		},	/* LCD_VSYN */
	{32*2+22,	GSS_INPUT_PULL		},	/* LCD_R2 */
	{32*2+23,	GSS_INPUT_PULL		},	/* LCD_R3 */
	{32*2+24,	GSS_INPUT_PULL		},	/* LCD_R4 */
	{32*2+25,	GSS_INPUT_PULL		},	/* LCD_RR5 */
	{32*2+26,	GSS_INPUT_PULL		},	/* LCD_RR6 */
	{32*2+27,	GSS_INPUT_PULL		},	/* LCD_RR7 */
	{32*3+14,	GSS_INPUT_NOPULL	},	/* CLK32K */
	{32*3+17,	GSS_INPUT_PULL		},	/* LCD_DISP_N */
	{32*3+18,	GSS_INPUT_NOPULL	},	/* BOOT_SEL1 */
	{32*3+19,	GSS_INPUT_PULL		},	/* LCD_RESET_N */
	{32*3+26,	GSS_IGNORE		},	/* UART1_TXD */
	{32*3+27,	GSS_INPUT_PULL		},	/* CIM_RST */
	{32*3+28,	GSS_INPUT_PULL	},	/* SSI_CLK */
	{32*3+29,	GSS_IGNORE		},	/* UART1_RXD */
	{32*3+30,	GSS_INPUT_NOPULL	},	/* SMB0_SDA */
	{32*3+31,	GSS_INPUT_NOPULL	},	/* SMB0_CLK */
	{32*4+0,	GSS_INPUT_PULL	},	/* SSI_DO */
	{32*4+1,	GSS_INPUT_PULL	},	/* LCD_PWM */
	{32*4+2,	GSS_INPUT_PULL	},	/* CIM_MCLK */
	{32*4+3,	GSS_INPUT_PULL	},	/* SSI_DI */
	{32*4+10,	GSS_OUTPUT_LOW		},	/* DRVVBUS */
	{32*4+20,	GSS_INPUT_NOPULL		},	/* SDIO_D0_WIFI */
	{32*4+21,	GSS_INPUT_NOPULL		},	/* SDIO_D1_WIFI */
	{32*4+22,	GSS_INPUT_NOPULL		},	/* SDIO_D2_WIFI */
	{32*4+23,	GSS_INPUT_NOPULL		},	/* SDIO_D3_WIFI */
	{32*4+28,	GSS_INPUT_NOPULL		},	/* SDIO_CLK_WIFI */
	{32*4+29,	GSS_INPUT_NOPULL		},	/* SDIO_CMD_WIFI */
	{32*4+30,	GSS_IGNORE		},	/* SMB1_SDA */
	{32*4+31,	GSS_IGNORE		},	/* SMB1_SCK */
	{32*5+0,	GSS_INPUT_NOPULL		},	/* BT_UART0_RXD */
	{32*5+1,	GSS_INPUT_NOPULL		},	/* BT_UART0_CTS */
	{32*5+2,	GSS_INPUT_NOPULL		},	/* BT_UART0_RTS */
	{32*5+3,	GSS_INPUT_NOPULL		},	/* BT_UART0_TXD */
	{32*5+6,	GSS_INPUT_NOPULL		},	/* DMIC_CLK */
	{32*5+7,	GSS_INPUT_NOPULL		},	/* DMIC_DOUT1 */
	{32*5+12,	GSS_INPUT_NOPULL		},	/* BT_PCM_DO */
	{32*5+13,	GSS_INPUT_NOPULL		},	/* BT_PCM_CLK */
	{32*5+14,	GSS_INPUT_NOPULL		},	/* BT_PCM_SYN */
	{32*5+15,	GSS_INPUT_NOPULL		},	/* BT_PCM_DI */
	{GSS_TABLET_END	,GSS_TABLET_END	}
};
