#ifndef _DSP_H
#define _DSP_H

#include "dsp_config.h"

/*  */
u8 bypass_parameter[] = {0xC0, 0xFC, 0xF3, 0x3B, 0x23, 0x00, 0x00, 0x04};
u8 enable_parameter[] = {0xC0, 0xFC, 0xF3, 0x3B, 0x23, 0x00, 0x00, 0x00};

// special parameters for disable/enable Noise Supression
u8 TF201_disable_NS[]={
	0xC0,
	0xFC, 0xF3, 0x3B, 0x23, 0x03, 0x00, 0x00,
	0xFC, 0xF3, 0x3B, 0x23, 0x04, 0x00, 0x10
};
u8 TF201_enable_NS[]={
	0xC0,
	0xFC, 0xF3, 0x3B, 0x23, 0x03, 0x00, 0x01,
	0xFC, 0xF3, 0x3B, 0x23, 0x04, 0x23, 0x01
};

/*
 * compiler option
 */
#define FM34_DEBUG			1
/*
 * Debug Utility
 */
#if FM34_DEBUG
#define FM34_INFO(format, arg...)	\
	printk(KERN_INFO "fm34: [%s] " format , __FUNCTION__ , ## arg)
#define FM34_I2C_DATA(array, i)	\
					do {		\
						for (i = 0; i < array[0]+1; i++) \
							FM34_INFO("i2c_data[%d] = 0x%x\n", i, array[i]);	\
					} while(0)
#else
#define FM34_INFO(format, arg...)
#define FM34_I2C_DATA(array, i)
#endif

#define FM34_NOTICE(format, arg...)	\
	printk(KERN_NOTICE "fm34: [%s] " format , __FUNCTION__ , ## arg)

#define FM34_ERR(format, arg...)	\
	printk(KERN_ERR "fm34: [%s] " format , __FUNCTION__ , ## arg)

//-----------------------------------------

#define DRIVER_DESC     		"fm34 driver"
#define CONVERSION_TIME_MS		50

//-----------------------------------------
#define TEGRA_GPIO_PO3		115 // DSP_RST#: RST Audio DSP
#define TEGRA_GPIO_PBB6		222 // DSP_PWDN#: Set Audio DSP to Power Down Mode
#define TEGRA_GPIO_PU5	165
#define TEGRA_GPIO_PA2	2 //DAP2_FS
#define TEGRA_GPIO_PW4	180 //AUDIO_MCLK
#define TEGRA_GPIO_PP3  123 //DAP3_SCLK

struct fm34_chip {
	struct input_dev	*indev;
	struct i2c_client	*client;
	struct attribute_group  attrs;
	struct miscdevice misc_dev;
	int 		        status;
	u8 i2c_data[32];
};

#endif
