/**
 ******************************************************************************
 * @file    main.c
 * @author  - Anthony E.Raterta
 * @version V1.0.0
 * @date    13-September-2024
 * @brief   Application entrypoint for I2C testing
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 mcu-dev
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "driver/src/adxl345.h"
#include "driver/src/utils/utils.h"
#include <stdio.h>

static adxl345_dev dev;
static adxl345_init_param dev_param;
static adxl345_axes_data adxl345_data;
bool stat = true;

int main(void) {
  dev_param.power_mode            = ADXL345_NORMAL_MODE;
  dev_param.odr                   = ADXL345_ODR_1_56HZ;
  dev_param.scale.scale           = ADXL345_SCALE_2G;
  dev_param.resolution.resolution = ADXL345_RES_FULL;

  if (adxl345_setup(&dev, dev_param) == ADXL345_STATUS_SUCCESS) {
    printf("Initialization successful!\r\n");
  } else {
    printf("Initialization Failed, exiting app!\r\n");
    return ADXL345_STATUS_INIT_ERR;
  }

  if (adxl345_online()) {
    printf("ADXL345 Detected!\r\n");
  }

  while (stat) {
    if (adxl345_get_interrupt_status(&dev) != ADXL345_STATUS_SUCCESS) {
      return ADXL345_STATUS_INIT_ERR;
    }
    if (dev.interrupt_status.data_ready) {
      if (adxl345_get_raw_xyz(&dev, &adxl345_data) == ADXL345_STATUS_SUCCESS) {
        adxl345_get_acc_xyz(&dev, &adxl345_data);
      }
      printf("raw X: %d  ", adxl345_data.raw_data.x);
      printf("acc X: %.4f\r\n", adxl345_data.acc_data.x);

      printf("raw Y: %d  ", adxl345_data.raw_data.y);
      printf("acc Y: %.4f\r\n", adxl345_data.acc_data.y);

      printf("raw Z: %d  ", adxl345_data.raw_data.z);
      printf("acc Z: %.4f\r\n", adxl345_data.acc_data.z);

      printf("\r\n");
    }
    // delay_ms(1000);
  }
  return 0;
}
