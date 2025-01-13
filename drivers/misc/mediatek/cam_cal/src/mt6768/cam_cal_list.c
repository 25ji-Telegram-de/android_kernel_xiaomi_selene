/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
#include <linux/kernel.h>
#include "cam_cal_list.h"
#include "eeprom_i2c_common_driver.h"
#include "eeprom_i2c_custom_driver.h"
#include "kd_imgsensor.h"
#ifdef GC02M1_MIPI_RAW
//extern gc02m1_read_otp_info();
extern unsigned int gc02m1_read_otp_info(struct i2c_client *client,
	unsigned int addr,
	unsigned char *data,
	unsigned int size);
#endif
#ifdef GC02M1_SUNNY_MIPI_RAW
extern unsigned int gc02m1_sunny_read_otp_info(struct i2c_client *client,
	unsigned int addr,
	unsigned char *data,
	unsigned int size);
#endif

#ifdef CONFIG_TARGET_PRODUCT_SELENECOMMON
extern unsigned int gc02m1_read_otp_info(struct i2c_client *client, unsigned int addr, unsigned char *data, unsigned int size);
extern unsigned int ov02b1b_read_otp_info(struct i2c_client *client, unsigned int addr, unsigned char *data, unsigned int size);
#endif

struct stCAM_CAL_LIST_STRUCT g_camCalList[] = {
	/*Below is commom sensor */
#ifdef CONFIG_TARGET_PRODUCT_SELENECOMMON
	{OV50C40_OFILM_MAIN_SENSOR_ID, 0xA2, Common_read_region},
	{S5KJN1_OFILM_MAIN_SENSOR_ID, 0xA2, Common_read_region},
	{OV50C40_QTECH_MAIN_SENSOR_ID, 0xA2, Common_read_region},
	{GC02M1_MACRO_AAC_SENSOR_ID, 0xA4, Common_read_region},
	{GC02M1_MACRO_SY_SENSOR_ID, 0xA4, Common_read_region},
	{IMX355_SUNNY_ULTRA_SENSOR_ID, 0xA0, Common_read_region},
	{IMX355_AAC_ULTRA_SENSOR_ID, 0xA0, Common_read_region},
	{OV8856_OFILM_FRONT_SENSOR_ID, 0xA2, Common_read_region},
	{OV8856_AAC_FRONT_SENSOR_ID, 0xA2, Common_read_region},
	{GC02M1B_SENSOR_ID1, 0xA2, gc02m1_read_otp_info},
	{OV02B1B_OFILM_SENSOR_ID, 0xA2, ov02b1b_read_otp_info},
	{OV50C40_OFILM_MAIN_SENSOR_INDIA_ID, 0xA2, Common_read_region},
	{S5KJN1_OFILM_MAIN_SENSOR_INDIA_ID, 0xA2, Common_read_region},
	{OV50C40_QTECH_MAIN_SENSOR_INDIA_ID, 0xA2, Common_read_region},
	{GC02M1_MACRO_AAC_SENSOR_INDIA_ID, 0xA4, Common_read_region},
	{GC02M1_MACRO_SY_SENSOR_INDIA_ID, 0xA4, Common_read_region},
	{IMX355_SUNNY_ULTRA_SENSOR_INDIA_ID, 0xA0, Common_read_region},
	{IMX355_AAC_ULTRA_SENSOR_INDIA_ID, 0xA0, Common_read_region},
	{OV8856_OFILM_FRONT_SENSOR_INDIA_ID, 0xA2, Common_read_region},
	{OV8856_AAC_FRONT_SENSOR_INDIA_ID, 0xA2, Common_read_region},
	{GC02M1B_SUNNY_SENSOR_INDIA_ID, 0xA2, gc02m1_read_otp_info},
	{OV02B1B_OFILM_SENSOR_INDIA_ID, 0xA2, ov02b1b_read_otp_info},
	{S5KJN1_OFILM_MAIN_SENSOR_CN_ID, 0xA2, Common_read_region},
	{OV50C40_QTECH_MAIN_SENSOR_CN_ID, 0xA2, Common_read_region},
	{IMX355_SUNNY_ULTRA_SENSOR_CN_ID, 0xA0, Common_read_region},
	{IMX355_AAC_ULTRA_SENSOR_CN_ID, 0xA0, Common_read_region},
#endif
	{IMX519_SENSOR_ID, 0xA0, Common_read_region},
	{S5K2T7SP_SENSOR_ID, 0xA4, Common_read_region},
	{IMX338_SENSOR_ID, 0xA0, Common_read_region},
	{S5K4E6_SENSOR_ID, 0xA8, Common_read_region},
	{IMX386_SENSOR_ID, 0xA0, Common_read_region},
	{S5K3M3_SENSOR_ID, 0xA0, Common_read_region},
	{S5K2L7_SENSOR_ID, 0xA0, Common_read_region},
	{IMX398_SENSOR_ID, 0xA0, Common_read_region},
	{IMX350_SENSOR_ID, 0xA0, Common_read_region},
	{IMX318_SENSOR_ID, 0xA0, Common_read_region},
	{IMX386_MONO_SENSOR_ID, 0xA0, Common_read_region},
	/*B+B. No Cal data for main2 OV8856*/
	{S5K2P7_SENSOR_ID, 0xA0, Common_read_region},
	/*  ADD before this line */
	{0, 0, 0}       /*end of list */
};

unsigned int cam_cal_get_sensor_list(
	struct stCAM_CAL_LIST_STRUCT **ppCamcalList)
{
	if (ppCamcalList == NULL)
		return 1;

	*ppCamcalList = &g_camCalList[0];
	return 0;
}


